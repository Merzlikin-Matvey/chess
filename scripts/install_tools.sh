#!/bin/bash

# Установим необходимые пакеты
if ! command -v unzip &> /dev/null
then
    echo "Установка unzip"
    sudo apt-get install unzip
    if [ $? -eq 0 ]; then
        echo "Установка unzip прошла успешно"
    else
        echo "Ошибка при установке unzip"
        exit 1
    fi
fi

if ! command -v jq &> /dev/null
then
    echo "Установка jq"
    sudo apt-get install jq
    if [ $? -eq 0 ]; then
        echo "Установка jq прошла успешно"
    else
        echo "Ошибка при установке jq"
        exit 1
    fi
fi