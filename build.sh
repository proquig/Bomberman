#!/usr/bin/env sh

mkdir -p build
cd build
cmake ..
make
mv Bomberman ..
mv ../lib/* ..
