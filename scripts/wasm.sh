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

src_files=$(find $src_dir -name "*.cpp" -not -path "$src_dir/wasm/*")
wasm_files=$(find $src_dir/wasm -name "*.cpp")

echo "Source files: $src_files"
echo "WASM files: $wasm_files"

output_dir="./wasm"
output_file="chess_lib"

if [ ! -d $output_dir ]
then
    mkdir $output_dir
else
    rm -rf $output_dir/*
fi



echo "Compiling..."
emcc $src_files $wasm_files -I $include_dir -std=c++23 -O3 -s EXPORT_ALL=1 -fconstexpr-steps=2147483647 -o $output_dir/$output_file.js -s EXPORTED_RUNTIME_METHODS='["cwrap"]'
echo "Done!"