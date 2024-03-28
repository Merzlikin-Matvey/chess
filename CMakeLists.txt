cmake_minimum_required(VERSION 3.12)
project(chess-engine)
set(CMAKE_CXX_STANDARD 17)

message(STATUS "C Compiler Version: ${CMAKE_C_COMPILER_VERSION}")
message(STATUS "C++ Compiler Version: ${CMAKE_CXX_COMPILER_VERSION}")

if(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/dependencies)
    message(FATAL_ERROR "Dependencies folder not found")
endif()

add_library(chess-engine SHARED
        src/board.cpp
        src/figure.cpp
        src/chess-engine.h
        dependencies/nlohmann/json/json-master/single_include/nlohmann/json.hpp)

add_custom_command(TARGET chess-engine POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_CURRENT_SOURCE_DIR}/default_positions.json
        $<TARGET_FILE_DIR:chess-engine>)

add_executable(chess-engine-app main.cpp)

target_link_libraries(chess-engine-app chess-engine)