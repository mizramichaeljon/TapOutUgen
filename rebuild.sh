#!/bin/bash
set -e

echo "Cleaning previous build..."
rm -rf build

echo "Creating build directory..."
mkdir build
cd build

echo "Running CMake configuration..."
cmake .. \
  -DSC_PATH=/Users/mjmizra/Documents/GitHub/supercollider-source \
  -DSHARED_RINGBUFFER_PATH=/Users/mjmizra/Documents/GitHub/shared-ringbuffer

echo "Compiling plugin..."
cmake --build .

echo "✅ Build complete."