#!/bin/bash
# Build script para babyphone (piloto Qt)
set -e

cd "$(dirname "$0")"

if [ ! -d build ]; then
    mkdir build
fi

cd build
cmake ..
make -j$(nproc)

echo "Build concluído. Executável: ./babyphone"
