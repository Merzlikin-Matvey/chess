cmake_minimum_required(VERSION 3.14)
project(chess-engine-example LANGUAGES CXX)

include("../cmake/utils.cmake")
string(COMPARE EQUAL "${CMAKE_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}" is_top_level)

if(is_top_level)
    find_package(chess-engine-example REQUIRED)
endif()

set(sources main.cpp)
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${sources})

add_executable(chess-engine-example)
target_sources(chess-engine-example PRIVATE ${sources})
target_link_libraries(chess-engine-example PRIVATE chess-engine::chess-engine)

if(NOT is_top_level)
    win_copy_deps_to_target_dir(chess-engine chess-engine::chess-engine)
endif()