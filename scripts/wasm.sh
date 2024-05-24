#!/bin/bash

echo "Building WebAssembly..."

export PATH=$PATH:/root/emsdk/upstream/bin

current_dir=$(pwd)

cd /root/emsdk
source ./emsdk_env.sh > /dev/null 2>&1

cd $current_dir/..
project_root_dir=$(pwd)

src_dir="./src"
include_dir="./include"

src_files=$(find $src_dir -name "*.cpp")
header_files=$(find $include_dir -name "*.hpp")

echo "Source files: $src_files"
echo "Header files: $header_files"

output_dir="./wasm"
output_file="chess_lib.wasm"

if [ ! -d $output_dir ]
then
    mkdir $output_dir
else
    rm -rf $output_dir/*
fi

emcc $src_files -I $include_dir -o $output_dir/$output_file -s WASM=1 -s ALLOW_MEMORY_GROWTH=1 -std=c++23 -O3 -fconstexpr-steps=2147483647 -s SIDE_MODULE=1