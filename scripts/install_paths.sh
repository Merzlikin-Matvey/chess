#!/bin/bash

# Проверяем, установлена ли переменная окружения
if [ -n "$CHESS_ENGINE_RESOURCE_PATH" ]
then
    # Если переменная установлена, удаляем ее из .bashrc
    grep -v 'export CHESS_ENGINE_RESOURCE_PATH' ~/.bashrc > temp && mv temp ~/.bashrc
    echo "Removed CHESS_ENGINE_RESOURCE_PATH"
fi

# Если был передан аргумент, устанавливаем новое значение переменной
if [ -n "$1" ]
then
    echo "export CHESS_ENGINE_RESOURCE_PATH=\"$1\"" >> ~/.bashrc
    source ~/.bashrc

    if [ -z "$CHESS_ENGINE_RESOURCE_PATH" ]
    then
        echo "Failed to set CHESS_ENGINE_RESOURCE_PATH"
        exit 1
    fi
fi