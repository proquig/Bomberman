#!/usr/bin/env sh

rm Bomberman
mkdir -p build
cd build
cmake ..
make
mv Bomberman ..
cd -
./Bomberman
