cmake_minimum_required(VERSION 3.14)
project(chess-lib-stateless-example LANGUAGES CXX)

set(sources main.cpp)
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${sources})

add_executable(chess-lib-stateless-example)
target_sources(chess-lib-stateless-example PRIVATE ${sources})
target_link_libraries(chess-lib-stateless-example PRIVATE chess-lib::chess-lib)

add_custom_command(TARGET chess-lib-stateless-example POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:chess-lib>
        $<TARGET_FILE_DIR:chess-lib-stateless-example>)

