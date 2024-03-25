cmake_minimum_required(VERSION 3.12)
project(engine)
set(CMAKE_CXX_STANDARD 17)

add_library(chess-engine SHARED
        board.cpp
        figure.cpp
        chess-engine.h
        dependencies/nlohmann/json/json-master/single_include/nlohmann/json.hpp)

