cmake_minimum_required(VERSION 3.14)
project(chess-lib-performance LANGUAGES CXX)

set(sources main.cpp)
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${sources})

add_executable(chess-lib-performance
        main.h
        tests/perft.cpp
        tests/alpha_beta.cpp
        common.cpp)
target_sources(chess-lib-performance PRIVATE ${sources})
target_link_libraries(chess-lib-performance PRIVATE chess-lib::chess-lib)

add_custom_command(TARGET chess-lib-performance POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:chess-lib>
        $<TARGET_FILE_DIR:chess-lib-performance>)