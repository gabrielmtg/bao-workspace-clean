#!/usr/bin/env bash

# Exit immediately if a command exits with a non-zero status.
set -e

# --- Environment Setup ---
# Source the environment file to load necessary variables.
VM_INDEX=NULL source env.bash

# Define file and directory paths for clarity.
SOURCE_FILE="$BAO_DEMOS_WRKDIR_IMGS/bao.bin"
DESTINATION_DIR="$BAO_DEMOS_SDCARD"

# --- Main Logic ---
# 1. Check if the source file exists.
if [ ! -f "$SOURCE_FILE" ]; then
    echo "❌ Error: Source file not found at '$SOURCE_FILE'"
    exit 1
fi

# 2. Check if the destination directory exists.
if [ ! -d "$DESTINATION_DIR" ]; then
    echo "❌ Error: Destination directory not found at '$DESTINATION_DIR'"
    echo "   Please ensure the SD card is mounted correctly."
    exit 1
fi

# 3. Copy the file.
echo "⚙️  Copying '$SOURCE_FILE' to '$DESTINATION_DIR'..."
cp -v "$SOURCE_FILE" "$DESTINATION_DIR"

# 4. Flush file system buffers to the SD card to prevent corruption.
echo "🔄 Syncing data with the SD card..."
sync

# 5. If the script reaches this point, the copy was successful.
echo "✅ Finished. Safe to eject!"
