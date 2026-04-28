# Bao Hypervisor — MemGuard + FreeRTOS Research Platform (RPi4)

Security research environment using the **Bao Hypervisor** on **Raspberry Pi 4 (ARMv8)**
for microarchitectural attack detection via PMU monitoring and bare-metal neural inference.

## Architecture

| Core | VM | Role |
|------|----|------|
| 0 | VM0 (Baremetal) | PMU Monitor + MLP Detector |
| 1 | VM1 (FreeRTOS) | Victim — Benchmark suite |
| 2 | VM2 (FreeRTOS) | Victim — Benchmark suite |
| 3 | VM3 (Buildroot Linux) | Attacker — Side-channel attacks |

## Quick Start (Docker — Recommended)

```bash
# Full build (first run clones Linux + Buildroot — takes ~30 min)
./build.sh

# Build specific components
./build.sh vm 0          # Build VM0 only
./build.sh bao           # Build Bao hypervisor only
./build.sh shell         # Interactive shell in build container
```

**Prerequisites:** Docker (or Podman). No native toolchains needed.

## Native Build

```bash
# 1. Install toolchain to etc/arm-gnu-toolchain/ or system PATH
# 2. Install deps: build-essential, dtc, python3, bc, flex, bison, libssl-dev...
VM_INDEX=0 source ./env.bash
make vms    # Build all VMs
make bao    # Build Bao hypervisor
make copy   # Copy bao.bin to SD card
```

## Output

After a successful build:
```
bao-demos/wrkdir/imgs/rpi4/linux+freertos/bao.bin
```

Flash `bao.bin` to the SD card's BOOT partition alongside the RPi4 firmware files.

## Project Structure

```
├── Dockerfile              # Build environment container
├── build.sh                # Docker-orchestrated build script
├── env.bash                # Environment variables (Docker + native)
├── Makefile                # Top-level build orchestrator
├── scripts/                # Build and utility scripts
├── data/
│   └── process_all.py      # PMU log parser (CSV extraction)
└── bao-demos/
    ├── demos/              # Scenario configs + devicetrees
    ├── guests/             # Linux/FreeRTOS guest configs
    ├── platforms/           # Platform-specific (RPi4)
    └── wrkdir/srcs/
        ├── bao/            # Bao hypervisor (modified: detector.c, pmu.c, regulator.c)
        ├── VMs/vm_{0..3}/  # VM sources (FreeRTOS + Linux)
        ├── benchmarks/     # 8 benchmark suite (bandwidth, SHA, FFT, etc.)
        ├── guest_common/   # Shared code across VMs
        ├── pmu_monitor/    # PMU monitoring library
        ├── neural_network/ # MLP inference engine
        └── fann/           # FANN library
```

## Data Pipeline

1. Collect PMU samples via UART (minicom/screen → `data/*.txt`)
2. Parse raw logs: `python3 data/process_all.py`
3. Train models off-board (Python/scikit-learn)
4. Port weights to `model_weights.h` in hypervisor
