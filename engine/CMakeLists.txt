# Минимальная версия CMake
cmake_minimum_required(VERSION 3.12)

# Имя проекта
project(chess)

# Установка стандарта языка
set(CMAKE_CXX_STANDARD 14)

# Добавление исполняемого файла из нескольких исходных файлов
add_executable(MyExecutable board.cpp exceptions.cpp main.cpp
        board.h
        exceptions.h
)
