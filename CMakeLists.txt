cmake_minimum_required(VERSION 3.12)
project(chess)
set(CMAKE_CXX_STANDARD 14)

add_subdirectory(engine)

add_executable(Main_executable main.cpp)


include(dependencies/conanbuildinfo.cmake)
conan_basic_setup()
target_link_libraries(Main_executable PRIVATE ${CONAN_LIBS})

message("C Compiler: ${CMAKE_C_COMPILER}")
message("C++ Compiler: ${CMAKE_CXX_COMPILER}")