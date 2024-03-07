cmake_minimum_required(VERSION 3.12)
project(engine)
set(CMAKE_CXX_STANDARD 17)

add_executable(Engine_executable
        src/board.cpp
        src/main.h
        src/figure.cpp

        dependencies/nlohmann/json/json.hpp
        dependencies/olmallet81/GALGO-2.0/Galgo.hpp)

