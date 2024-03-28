#!/bin/bash

if [ -d "build" ]; then
    echo "Удаление существующей директории build"
    rm -rf build

    if [ $? -eq 0 ]; then
        echo "Удаление директории build прошло успешно"
    else
        echo "Ошибка при удалении директории build"
        exit 1
    fi
fi

# Создание новой директории
mkdir build

# shellcheck disable=SC2164
cd build

cmake ..
make