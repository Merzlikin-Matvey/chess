cmake_minimum_required(VERSION 3.14)
project(chess-lib-tests LANGUAGES CXX)

find_package(nlohmann_json REQUIRED)

set(tests
        legal_moves/test.cpp
)

add_executable(chess-lib-tests ${tests})
target_link_libraries(chess-lib-tests PRIVATE chess-lib::chess-lib GTest::gtest_main nlohmann_json::nlohmann_json)
target_compile_definitions(chess-lib-tests PRIVATE
        TEST_DATA_DIR="${CMAKE_CURRENT_SOURCE_DIR}/legal_moves/data")

add_custom_command(TARGET chess-lib-tests POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:chess-lib>
        $<TARGET_FILE_DIR:chess-lib-tests>)

