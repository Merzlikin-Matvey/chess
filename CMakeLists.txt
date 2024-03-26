cmake_minimum_required(VERSION 3.12)
project(chess-engine)
set(CMAKE_CXX_STANDARD 17)

add_library(chess-engine SHARED
        src/board.cpp
        src/figure.cpp
        src/chess-engine.h
        dependencies/nlohmann/json/json-master/single_include/nlohmann/json.hpp)

add_custom_command(TARGET chess-engine POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_SOURCE_DIR}/settings.json
        $<TARGET_FILE_DIR:chess-engine>)