cmake_minimum_required(VERSION 3.12)
project(engine)
set(CMAKE_CXX_STANDARD 17)

add_executable(Engine_executable
        src/board.cpp
        src/main.h
        src/figure.cpp)

include(../dependencies/conanbuildinfo.cmake)
conan_basic_setup()
target_link_libraries(Engine_executable PUBLIC ${CONAN_LIBS})