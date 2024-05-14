#!/bin/bash

if [ -n "$CHESS_LIB_PATH" ]
then
    grep -v 'export CHESS_LIB_PATH' ~/.bashrc > temp && mv temp ~/.bashrc
    grep -v 'export PATH' ~/.bashrc > temp && mv temp ~/.bashrc
fi

if [ -n "$1" ]
then
    export CHESS_LIB_PATH="$1"
    echo "export CHESS_LIB_PATH=\"$1\"" >> ~/.bashrc
    echo "export PATH=\$PATH:\$CHESS_LIB_PATH/lib" >> ~/.bashrc

    if [ -z "$CHESS_LIB_PATH" ]
    then
        echo "Failed to set CHESS_LIB_PATH"
        exit 1
    fi
fi