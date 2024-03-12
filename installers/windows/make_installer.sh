#!/bin/bash

# Проверяем, установлен ли NSIS
if ! command -v makensis &> /dev/null
then
    echo "Установка NSIS"
    sudo apt-get update
    sudo apt-get install nsis
    if [ $? -eq 0 ]; then
        echo "Установка NSIS прошла успешно"
    else
        echo "Ошибка при установке NSIS"
        exit 1
    fi
fi

echo "Введите абсолютный путь к директории, где находятся стандартные DLL:"
read dll_path

target_path="files/"

# Массив с названиями DLL
stl_dlls=("libstdc++-6.dll" "libgcc_s_seh-1.dll" "libatomic-1.dll" "libgomp-1.dll" "libssp-0.dll" "libwinpthread-1.dll")

# Массив с названиями файлов, которые нужно перенести из cmake-build-release
files_to_copy=(
"../../cmake-build-release/Main_executable.exe"
"../../cmake-build-release/engine/libEngine_executable.dll"
"../../default_positions.json"
)

# Массив с папками, которые надо создать
folders_to_create=(
"saves"
)

# Если files уже существует, то удалим ее
if [ -d "files" ]; then
    echo "Удаление существующей директории files"
    rm -rf files

    if [ $? -eq 0 ]; then
        echo "Удаление директории files прошло успешно"
    else
        echo "Ошибка при удалении директории files"
        exit 1
    fi
fi

# Если файл Chess_installer существует, то удалим его
if [ -f "Chess_installer.exe" ]; then
    echo "Удаление существующего файла Chess_installer.exe"
    rm Chess_installer.exe

    if [ $? -eq 0 ]; then
        echo "Удаление файла Chess_installer.exe прошло успешно"
    else
        echo "Ошибка при удалении файла Chess_installer.exe"
        exit 1
    fi
fi

# Создадим директорию files
mkdir files

# Копируем нужные файлы в files
for file in "${files_to_copy[@]}"
do
  cp "${file}" "${target_path}/"
  if [ $? -ne 0 ]; then
    echo "Ошибка при копировании файла ${file}"
    exit 1
  fi
done

for dll in "${stl_dlls[@]}"
do
  cp "${dll_path}/${dll}" "${target_path}/"
  if [ $? -ne 0 ]; then
    echo "Ошибка при копировании файла ${dll}"
    exit 1
  fi
done

for folder in "${folders_to_create[@]}"
do
  mkdir "${target_path}/${folder}"
  if [ $? -ne 0 ]; then
    echo "Ошибка при создании папки ${folder}"
    exit 1
  fi
done

# Переименуем files/Main_executable.exe в files/chess.exe
mv files/Main_executable.exe files/chess.exe

# Скопируем настройки
cp settings.json files/

echo "Копирование файлов прошло успешно"

# Создаем инсталлятор
makensis main.nsi