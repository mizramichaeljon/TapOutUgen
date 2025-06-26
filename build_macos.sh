#!/bin/bash
set -e
echo "Cleaning..."
rm -rf build
echo "Building..."
mkdir build && cd build
cmake .. -DSC_PATH=/path/to/supercollider -DSHARED_RINGBUFFER_PATH=/path/to/shared-ringbuffer
cmake --build .
echo "Done. Plugin is in build/Plugins/"
