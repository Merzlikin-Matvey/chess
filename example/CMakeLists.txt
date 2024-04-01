cmake_minimum_required(VERSION 3.14)
project(chess-engine-test LANGUAGES CXX)

include("../../cmake/utils.cmake")
string(COMPARE EQUAL "${CMAKE_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}" is_top_level)

if(is_top_level)
    find_package(chess-engine-test REQUIRED)
endif()

set(sources main.cpp)
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${sources})

add_executable(chess-engine-test)
target_sources(chess-engine-test PRIVATE ${sources})
target_link_libraries(mylib-add PRIVATE mylib::mylib)

if(NOT is_top_level)
    win_copy_deps_to_target_dir(mylib-add mylib::mylib)
endif()