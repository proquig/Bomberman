#!/usr/bin/env sh

mkdir -p build
cd build
cmake -DCMAKE_BUILD_TYPE=Debug  ..
make && ./Bomberman
