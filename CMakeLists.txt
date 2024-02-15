cmake_minimum_required(VERSION 3.12)
project(chess)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static-libgcc -static-libstdc++")

add_subdirectory(engine)
add_executable(Main_executable main.cpp)


message("C Compiler: ${CMAKE_C_COMPILER}")
message("C++ Compiler: ${CMAKE_CXX_COMPILER}")

include(dependencies/conanbuildinfo.cmake)
conan_basic_setup()
target_link_libraries(Main_executable PUBLIC ${CONAN_LIBS})