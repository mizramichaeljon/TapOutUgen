#!/bin/bash
set -e

# Set these once before building
SC_PATH="$HOME/" # Path to SuperCollider build
SHARED_RINGBUFFER_PATH="$HOME/" # Path to shared-ringbuffer root

echo "Cleaning..."
rm -rf build

echo "Building..."
mkdir build && cd build
cmake .. -DSC_PATH="$SC_PATH" -DSHARED_RINGBUFFER_PATH="$SHARED_RINGBUFFER_PATH"
cmake --build .

echo "✅ Done. Plugin is in build/Plugins"
