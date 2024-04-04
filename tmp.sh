#!/bin/bash

if [ -d build ]; then
  rm -rf build
fi

mkdir build
cd build
cmake -D CHESS_ENGINE_EXAMPLES=on ..
make install
cd example
./chess-engine-example