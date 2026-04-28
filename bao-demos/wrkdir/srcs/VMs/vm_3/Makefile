NAME:=vm_3
ROOT_DIR:=$(realpath .)

.DEFAULT_GOAL := all

wrkdir_demo_imgs := $(ROOT_DIR)/build/$(PLATFORM)
TARGET := $(wrkdir_demo_imgs)/$(NAME).bin

wrkdir_src := $(ROOT_DIR)
bao_demos ?= $(BAO_DEMOS)

include $(BAO_DEMOS)/guests/linux/make.mk

BUILDROOT_DIR := $(buildroot_src)
CC_ARM := $(BUILDROOT_DIR)/output/host/bin/aarch64-buildroot-linux-uclibc-gcc
CUSTOM_OVERLAY := $(wrkdir_src)/custom_overlay
OVERLAY_DIR := $(CUSTOM_OVERLAY)/root

SPECTRE_SRC := $(wrkdir_src)/attacks/spectre/src/spectre_attack.c
ARMAGEDDON_SRC := $(wrkdir_src)/attacks/armageddon/src/armageddon.c
MELTDOWN_SRC := $(wrkdir_src)/attacks/meltdown/src/meltdown.c
ZOMBIELOAD_SRC := $(wrkdir_src)/attacks/zombieload/src/zombieload.c

# --- Fontes dos benchmarks (para cenário 7: benchmarks no core 3) ---
BENCH_ROOT := $(ROOT_DIR)/../../benchmarks
BENCH_MAIN_SRC := $(OVERLAY_DIR)/main_benchmark.c
BENCH_WRAPPER_SRC := $(BENCH_ROOT)/wrappers/src/benchmarks_wrappers.c
BENCH_C_SRCS := $(BENCH_ROOT)/bandwidth/src/bandwidth.c \
                $(BENCH_ROOT)/dijkstra/src/dijkstra.c \
                $(BENCH_ROOT)/disparity/src/computeSAD.c \
                $(BENCH_ROOT)/disparity/src/correlateSAD_2D.c \
                $(BENCH_ROOT)/disparity/src/disparity.c \
                $(BENCH_ROOT)/disparity/src/finalSAD.c \
                $(BENCH_ROOT)/disparity/src/findDisparity.c \
                $(BENCH_ROOT)/disparity/src/getDisparity.c \
                $(BENCH_ROOT)/disparity/src/integralImage2D2D.c \
                $(BENCH_ROOT)/disparity/src/padarray2.c \
                $(BENCH_ROOT)/disparity/src/padarray4.c \
                $(BENCH_ROOT)/fft/src/driver.c \
                $(BENCH_ROOT)/fft/src/fft.c \
                $(BENCH_ROOT)/mser/src/mser.c \
                $(BENCH_ROOT)/qsort/src/qsort.c \
                $(BENCH_ROOT)/sha/src/sha.c \
                $(BENCH_ROOT)/sha/src/sha_driver.c \
                $(BENCH_ROOT)/sorting/src/sorting.c

BENCH_INC_DIRS := -I$(BENCH_ROOT)/wrappers/inc \
                  -I$(BENCH_ROOT)/bandwidth/inc \
                  -I$(BENCH_ROOT)/dijkstra/inc \
                  -I$(BENCH_ROOT)/disparity/inc \
                  -I$(BENCH_ROOT)/fft/inc \
                  -I$(BENCH_ROOT)/mser/inc \
                  -I$(BENCH_ROOT)/qsort/inc \
                  -I$(BENCH_ROOT)/sha/inc \
                  -I$(BENCH_ROOT)/sorting/inc

CUSTOM_APPS := $(OVERLAY_DIR)/spectre \
               $(OVERLAY_DIR)/armageddon \
               $(OVERLAY_DIR)/meltdown \
               $(OVERLAY_DIR)/zombieload \
               $(OVERLAY_DIR)/benchmark


$(BUILDROOT_DIR)/output/host/bin/aarch64-buildroot-linux-uclibc-gcc: | $(BUILDROOT_DIR) $(linux_src)
	@echo ">> Buildroot toolchain nao encontrado. Buildando buildroot (pode demorar)..."
	$(MAKE) -C $(BUILDROOT_DIR) defconfig BR2_DEFCONFIG=$(buildroot_defcfg)
	$(MAKE) -C $(BUILDROOT_DIR)

# --- Regras de compilação dos ataques ---
# Dependem do compilador do buildroot (order-only para nao forcar rebuild)

$(OVERLAY_DIR)/spectre: $(SPECTRE_SRC) | $(CC_ARM)
	@echo ">> Compilando Ataque Spectre..."
	$(CC_ARM) -O2 $< -o $@

$(OVERLAY_DIR)/armageddon: $(ARMAGEDDON_SRC) | $(CC_ARM)
	@echo ">> Compilando Ataque Armageddon..."
	$(CC_ARM) -O2 $< -o $@

$(OVERLAY_DIR)/meltdown: $(MELTDOWN_SRC) | $(CC_ARM)
	@echo ">> Compilando Ataque Meltdown..."
	$(CC_ARM) -O2 $< -o $@

$(OVERLAY_DIR)/zombieload: $(ZOMBIELOAD_SRC) | $(CC_ARM)
	@echo ">> Compilando Ataque ZombieLoad..."
	$(CC_ARM) -O2 $< -o $@

# --- Regra de compilação do benchmark para Linux ---
$(OVERLAY_DIR)/benchmark: $(BENCH_MAIN_SRC) $(BENCH_WRAPPER_SRC) $(BENCH_C_SRCS) | $(CC_ARM)
	@echo ">> Compilando Benchmark para Linux (VM3)..."
	$(CC_ARM) -O2 $(BENCH_INC_DIRS) $(BENCH_MAIN_SRC) $(BENCH_WRAPPER_SRC) $(BENCH_C_SRCS) -o $@ -lm

# --- Regra do attack_mode.cfg ---
# Lê o SCENARIO de regulation.h e escreve o modo no overlay
REGULATION_H := $(ROOT_DIR)/../../guest_common/inc/regulation.h
ATTACK_MODE_CFG := $(OVERLAY_DIR)/attack_mode.cfg

$(ATTACK_MODE_CFG): $(REGULATION_H)
	@SCENARIO=$$(grep -oP '^\s*#define\s+SCENARIO\s+\K[0-9]+' $(REGULATION_H)); \
	if [ "$$SCENARIO" = "8" ]; then \
		echo "meltdown_only" > $@; \
		echo ">> attack_mode.cfg: meltdown_only (cenário 8)"; \
	elif [ "$$SCENARIO" = "7" ]; then \
		echo "with_bench" > $@; \
		echo ">> attack_mode.cfg: with_bench (cenário 7)"; \
	else \
		echo "no_idle" > $@; \
		echo ">> attack_mode.cfg: no_idle (cenário $$SCENARIO)"; \
	fi

# --- Regra do RootFS ---

$(BUILDROOT_DIR)/output/images/rootfs.cpio: $(CUSTOM_APPS) $(ATTACK_MODE_CFG) | $(BUILDROOT_DIR)
	@echo ">> Repacotando o sistema de arquivos do Linux com os ataques..."
	$(MAKE) -C $(BUILDROOT_DIR) BR2_ROOTFS_OVERLAY="$(CUSTOM_OVERLAY)"

# O make.mk espera rootfs.cpio.gz, mas o buildroot gera rootfs.cpio sem compressao.
# Gera o .gz a partir do .cpio.
$(BUILDROOT_DIR)/output/images/rootfs.cpio.gz: $(BUILDROOT_DIR)/output/images/rootfs.cpio
	@echo ">> Comprimindo rootfs.cpio -> rootfs.cpio.gz..."
	gzip -k -f $<

all: $(CUSTOM_APPS) $(ATTACK_MODE_CFG) $(BUILDROOT_DIR)/output/images/rootfs.cpio $(TARGET)

VM3_DTS := $(BAO_DEMOS)/demos/linux+freertos/devicetrees/$(PLATFORM)/linux.dts

$(eval $(call build-linux, $(TARGET), $(VM3_DTS)))

clean:
	rm -f $(TARGET)
	rm -f $(wrkdir_demo_imgs)/*.dtb
	rm -f $(OVERLAY_DIR)/benchmark