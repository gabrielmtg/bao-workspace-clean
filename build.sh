#!/usr/bin/env bash
# =============================================================================
# build.sh — Portable build script for the Bao Hypervisor project
#
# Builds the entire project inside a Docker container for full portability.
#
# Usage:
#   ./build.sh              # Full build + copy to SD card
#   ./build.sh vms          # Build only VMs (vm_0 through vm_3)
#   ./build.sh vm 0         # Build only vm_0
#   ./build.sh vm 3         # Build only vm_3 (Linux — slow first time)
#   ./build.sh bao          # Build only the Bao hypervisor
#   ./build.sh copy         # Copy bao.bin to SD card (no build)
#   ./build.sh clean        # Clean all build artifacts
#   ./build.sh shell        # Open interactive shell inside the container
#
# Output:
#   bao-demos/wrkdir/imgs/rpi4/linux+freertos/bao.bin
# =============================================================================
set -euo pipefail

IMAGE_NAME="bao-build-env"
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m'

info()  { echo -e "${BLUE}[INFO]${NC}  $*"; }
ok()    { echo -e "${GREEN}[OK]${NC}    $*"; }
warn()  { echo -e "${YELLOW}[WARN]${NC}  $*"; }
error() { echo -e "${RED}[ERROR]${NC} $*" >&2; }

ensure_image() {
    if ! docker image inspect "$IMAGE_NAME" &>/dev/null; then
        info "Docker image '$IMAGE_NAME' not found. Building..."
        docker build -t "$IMAGE_NAME" "$SCRIPT_DIR"
        ok "Docker image built successfully."
    else
        info "Using existing Docker image '$IMAGE_NAME'."
    fi
}

run_in_container() {
    local cmd="$*"
    docker run --rm \
        -v "${SCRIPT_DIR}":/workspace \
        -w /workspace \
        -e "PLATFORM=rpi4" \
        -e "DEMO=linux+freertos" \
        -e "ARCH=aarch64" \
        "$IMAGE_NAME" \
        bash -c "$cmd"
}

build_vm() {
    local vm_index="$1"
    info "Building VM ${vm_index}..."
    run_in_container "source env.bash && ./scripts/util/build_vm.sh ${vm_index}"
    ok "VM ${vm_index} built."
}

build_all_vms() {
    info "Building all VMs (0-3)..."
    run_in_container "source env.bash && ./scripts/util/build_vm.sh all"
    ok "All VMs built."
}

build_bao() {
    info "Building Bao hypervisor..."
    run_in_container "source env.bash && ./scripts/util/build_bao.sh"
    ok "Bao hypervisor built."
    local bao_bin="${SCRIPT_DIR}/bao-demos/wrkdir/imgs/rpi4/linux+freertos/bao.bin"
    if [[ -f "$bao_bin" ]]; then
        ok "Output: bao-demos/wrkdir/imgs/rpi4/linux+freertos/bao.bin ($(du -h "$bao_bin" | cut -f1))"
    fi
}

build_all() {
    build_all_vms
    build_bao
}

copy_to_sdcard() {
    local bao_bin="${SCRIPT_DIR}/bao-demos/wrkdir/imgs/rpi4/linux+freertos/bao.bin"
    local real_user="${SUDO_USER:-$USER}"
    local sdcard="/media/${real_user}/BOOT/"

    # Allow override via environment variable
    sdcard="${BAO_DEMOS_SDCARD:-$sdcard}"

    info "Copying bao.bin to SD card at '${sdcard}'..."

    if [[ ! -f "$bao_bin" ]]; then
        error "bao.bin not found at '$bao_bin'. Build first with: ./build.sh"
        exit 1
    fi

    if [[ ! -d "$sdcard" ]]; then
        error "SD card not found at '$sdcard'"
        error "Make sure the SD card is mounted."
        error "Or set BAO_DEMOS_SDCARD: BAO_DEMOS_SDCARD=/path/to/mount ./build.sh copy"
        exit 1
    fi

    cp -v "$bao_bin" "$sdcard"
    sync
    ok "bao.bin copied to '$sdcard'. Safe to eject!"
}

deploy() {
    build_all
    copy_to_sdcard
}

do_clean() {
    info "Cleaning all build artifacts..."
    run_in_container "source env.bash && ./scripts/util/clean.sh" || true
    ok "Clean complete."
}

open_shell() {
    info "Opening interactive shell in build container..."
    docker run --rm -it \
        -v "${SCRIPT_DIR}":/workspace \
        -w /workspace \
        -e "PLATFORM=rpi4" \
        -e "DEMO=linux+freertos" \
        -e "ARCH=aarch64" \
        "$IMAGE_NAME" \
        bash
}

usage() {
    echo "Usage: $0 [command] [args]"
    echo ""
    echo "Commands:"
    echo "  (none)         Full build (Docker) + copy to SD card"
    echo "  vms            Build all VMs (0-3)"
    echo "  vm <N>         Build a specific VM (0-3)"
    echo "  bao            Build only the Bao hypervisor"
    echo "  copy           Copy bao.bin to SD card (skip build)"
    echo "  clean          Clean all build artifacts"
    echo "  shell          Open interactive shell in the container"
    echo "  help           Show this help message"
}

main() {
    local cmd="${1:-all}"

    # 'copy' runs on the host — no Docker needed
    if [[ "$cmd" == "copy" ]]; then
        copy_to_sdcard
        return
    fi

    ensure_image
    case "$cmd" in
        all)   deploy ;;
        vms)   build_all_vms ;;
        vm)    build_vm "${2:?ERROR: VM index required (0-3)}" ;;
        bao)   build_bao ;;
        clean) do_clean ;;
        shell) open_shell ;;
        help|--help|-h) usage ;;
        *)     error "Unknown command: $cmd"; usage; exit 1 ;;
    esac
}

main "$@"
