#!/bin/bash
set -e

echo "Building Project..."

mkdir -p build
cd build

cmake .. \
  -DCMAKE_BUILD_TYPE=Debug

cmake --build .

echo "Build complete"

# Remember to run the following command to make this script executable:
# chmod +x build.sh
