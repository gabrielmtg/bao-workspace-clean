#!/usr/bin/env bash
# =============================================================================
# env.bash — Environment setup for Bao Hypervisor project
#
# Works in two modes:
#   1) Docker:  Toolchain is in PATH (installed in /opt/toolchain)
#   2) Native:  Toolchain is in etc/arm-gnu-toolchain/ (local install)
#
# Usage:
#   VM_INDEX=0 source ./env.bash
# =============================================================================

current_path=$(realpath .)
bao_folder="bao-demos"

# ── Toolchain detection ──────────────────────────────────────────────────────
# If running inside Docker, the toolchain is in PATH.
# If running natively, check for a local toolchain folder.
if command -v aarch64-none-elf-gcc &>/dev/null; then
  # Toolchain in PATH (Docker or system-installed)
  export CROSS_COMPILE="aarch64-none-elf-"
elif [ -d "etc/arm-gnu-toolchain" ]; then
  # Local toolchain folder
  export CROSS_COMPILE="$current_path/etc/arm-gnu-toolchain/bin/aarch64-none-elf-"
else
  echo "ERROR: AArch64 toolchain not found."
  echo "  Either install it to PATH or place it in etc/arm-gnu-toolchain/"
  echo "  Or use: ./build.sh (Docker-based build)"
  return 2>/dev/null || exit 1
fi

# ── Sanity check ─────────────────────────────────────────────────────────────
if [ ! -d "$bao_folder" ]; then
  echo "'$bao_folder' not found. Are you in the correct folder?"
  return 2>/dev/null || exit 1
fi

# ── Platform config ──────────────────────────────────────────────────────────
export PLATFORM=${PLATFORM:-rpi4}
export DEMO=${DEMO:-linux+freertos}
export ARCH=${ARCH:-aarch64}
export PYTHONPATH=/usr

# ── Working directories ─────────────────────────────────────────────────────
export BAO_DEMOS="$current_path"/"$bao_folder"
export BAO_DEMOS_WRKDIR=$BAO_DEMOS/wrkdir
export BAO_DEMOS_WRKDIR_SRC=$BAO_DEMOS_WRKDIR/srcs
export BAO_DEMOS_WRKDIR_BIN=$BAO_DEMOS_WRKDIR/bin
export BAO_DEMOS_WRKDIR_PLAT=$BAO_DEMOS_WRKDIR/imgs/$PLATFORM
export BAO_DEMOS_WRKDIR_IMGS=$BAO_DEMOS_WRKDIR_PLAT/$DEMO

# ── FreeRTOS VM ──────────────────────────────────────────────────────────────
if [ -z "$VM_INDEX" ]; then
  echo "Warning: VM_INDEX is not defined." >&2
fi

export BAO_DEMOS_FREERTOS=$BAO_DEMOS_WRKDIR_SRC/VMs/vm_$VM_INDEX/
export FREERTOS_PARAMS="STD_ADDR_SPACE=y"

# ── Linux VM (Buildroot) ────────────────────────────────────────────────────
export BAO_DEMOS_LINUX=$BAO_DEMOS/guests/linux
export BAO_DEMOS_LINUX_REPO=https://github.com/torvalds/linux.git
export BAO_DEMOS_LINUX_VERSION=v6.1
export BAO_DEMOS_LINUX_SRC=$BAO_DEMOS_WRKDIR_SRC/linux-$BAO_DEMOS_LINUX_VERSION

export BAO_DEMOS_LINUX_CFG_FRAG=$(ls $BAO_DEMOS_LINUX/configs/base.config\
    $BAO_DEMOS_LINUX/configs/$ARCH.config\
    $BAO_DEMOS_LINUX/configs/$PLATFORM.config 2> /dev/null)

export BAO_DEMOS_BUILDROOT=$BAO_DEMOS_WRKDIR_SRC/\
buildroot-$ARCH-$BAO_DEMOS_LINUX_VERSION
export BAO_DEMOS_BUILDROOT_DEFCFG=$BAO_DEMOS_LINUX/buildroot/$ARCH.config
export LINUX_OVERRIDE_SRCDIR=$BAO_DEMOS_LINUX_SRC

export BAO_DEMO_LINUX_VM=linux

# ── Bao hypervisor ───────────────────────────────────────────────────────────
export BAO_DEMOS_BAO=$BAO_DEMOS_WRKDIR_SRC/bao

# ── Firmware (U-Boot, ATF) ───────────────────────────────────────────────────
export BAO_DEMOS_FW=$BAO_DEMOS_WRKDIR_PLAT/firmware
export BAO_DEMOS_UBOOT=$BAO_DEMOS_WRKDIR_SRC/u-boot
export BAO_DEMOS_ATF=$BAO_DEMOS_WRKDIR_SRC/arm-trusted-firmware

# ── SD Card (native only) ───────────────────────────────────────────────────
export BAO_DEMOS_SDCARD_DEV=${BAO_DEMOS_SDCARD_DEV:-/dev/sda}
export BAO_DEMOS_SDCARD=${BAO_DEMOS_SDCARD:-/media/$USER/BOOT/}

# ── Convenience aliases ─────────────────────────────────────────────────────
export VM=$BAO_DEMOS/wrkdir/srcs/VMs/vm_
export BAO_CORE=$BAO_DEMOS_WRKDIR_SRC/bao/src/core
