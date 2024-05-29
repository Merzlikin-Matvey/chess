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

all_files=$(find $src_dir -name "*.cpp")
src_files=$(echo "$all_files" | grep -v "$src_dir/wasm")
wasm_files=$(echo "$all_files" | grep "$src_dir/wasm")
header_files=$(find $include_dir -name "*.hpp")

echo "Source files: $src_files"
echo "WASM files: $wasm_files"
echo "Header files: $header_files"

output_dir="./wasm"
output_file="chess_lib"

if [ ! -d $output_dir ]
then
    mkdir $output_dir
else
    rm -rf $output_dir/*
fi

echo "Compile as a side module? [Y/n] "
read answer

if [ "$answer" = "Y" ] || [ "$answer" = "y" ]; then
    echo "Compiling as a side module..."
    emcc $src_files -I $include_dir -std=c++23 -s EXPORT_ALL=1 -fconstexpr-steps=2147483647 -s SIDE_MODULE=1 -o $output_dir/$output_file.js
else
    echo "Compiling as a main module..."
    emcc $all_files -I $include_dir -std=c++23 -s EXPORT_ALL=1 -fconstexpr-steps=2147483647 -o $output_dir/$output_file.js -s EXTRA_EXPORTED_RUNTIME_METHODS='[cwrap]'
fi