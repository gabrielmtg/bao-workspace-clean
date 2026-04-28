# =============================================================================
# Dockerfile: Bao Hypervisor Build Environment
# Target: Raspberry Pi 4 (ARMv8/AArch64)
# =============================================================================

FROM ubuntu:22.04

ARG DEBIAN_FRONTEND=noninteractive
ARG TOOLCHAIN_VERSION=13.3.rel1
ARG TOOLCHAIN_ARCHIVE=arm-gnu-toolchain-${TOOLCHAIN_VERSION}-x86_64-aarch64-none-elf.tar.xz
ARG TOOLCHAIN_URL=https://developer.arm.com/-/media/Files/downloads/gnu/${TOOLCHAIN_VERSION}/binrel/${TOOLCHAIN_ARCHIVE}

# ── System packages ──────────────────────────────────────────────────────────
RUN apt-get update && apt-get install -y --no-install-recommends \
    build-essential gcc g++ make \
    bc bison flex libssl-dev libncurses-dev \
    cpio unzip rsync file patch perl sed gawk \
    libelf-dev \
    swig python3-dev python3-setuptools \
    device-tree-compiler libfdt-dev \
    python3 python3-pip \
    git wget xz-utils ca-certificates \
    gettext-base \
    && rm -rf /var/lib/apt/lists/*

# ── ARM AArch64 bare-metal toolchain ─────────────────────────────────────────
RUN mkdir -p /opt/toolchain && \
    wget -q --show-progress -O /tmp/${TOOLCHAIN_ARCHIVE} ${TOOLCHAIN_URL} && \
    tar -xJf /tmp/${TOOLCHAIN_ARCHIVE} -C /opt/toolchain --strip-components=1 && \
    rm /tmp/${TOOLCHAIN_ARCHIVE}

ENV PATH="/opt/toolchain/bin:${PATH}"

WORKDIR /workspace
SHELL ["/bin/bash", "-c"]
RUN aarch64-none-elf-gcc --version | head -1
CMD ["/bin/bash"]
