#!/bin/bash

if [ -z "$1" ]
then
    echo "Not enough arguments"
    exit 1
fi

resource_path="$1"

grep -v 'export CHESS_ENGINE_RESOURCE_PATH' ~/.bashrc > temp && mv temp ~/.bashrc

echo "export CHESS_ENGINE_RESOURCE_PATH=\"$resource_path\"" >> ~/.bashrc

source ~/.bashrc

if [ -z "$CHESS_ENGINE_RESOURCE_PATH" ]
then
    echo "Failed to set CHESS_ENGINE_RESOURCE_PATH"
    exit 1
fi