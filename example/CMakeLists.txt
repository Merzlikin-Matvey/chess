cmake_minimum_required(VERSION 3.14)
project(chess-lib-example LANGUAGES CXX)

set(sources main.cpp)
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${sources})

add_executable(chess-lib-example)
target_sources(chess-lib-example PRIVATE ${sources})
target_link_libraries(chess-lib-example PRIVATE chess-lib::chess-lib)

add_custom_command(TARGET chess-lib-example POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:chess-lib>
        $<TARGET_FILE_DIR:chess-lib-example>)

