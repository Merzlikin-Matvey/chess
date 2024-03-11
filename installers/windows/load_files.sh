#!/bin/bash

echo "Введите абсолютный путь к директории, где находятся DLL:"
read dll_path

echo $dll_path

target_path="src/"

# Массив с названиями DLL
dlls=("libstdc++-6.dll" "libgcc_s_seh-1.dll")

# Копировать каждую DLL из массива из исходной директории в целевую
for dll in "${dlls[@]}"
do
  cp "${dll_path}/${dll}" "${target_path}/"
done