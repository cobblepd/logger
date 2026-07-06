#!/usr/bin/env bash
set -euo pipefail

image_name="logger-valgrind"
build_dir="build-linux"

docker build -f Dockerfile.valgrind -t "$image_name" .

docker run --rm \
  -v "$PWD:/work" \
  -w /work \
  "$image_name" \
  bash -lc "cmake -S . -B $build_dir -G Ninja -DCMAKE_BUILD_TYPE=Debug && cmake --build $build_dir && valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$build_dir/logger"
