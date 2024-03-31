cmake_minimum_required(VERSION 3.14)
project(chess=engine
        VERSION 1.0.0
        DESCRIPTION "Chess engine"
        LANGUAGES CXX)

#------------------------------#
# General settings and options #
#------------------------------#

add_library(chess-engine)
add_library(chess-engine::chess-engine ALIAS chess-engine)

string(COMPARE EQUAL "${CMAKE_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}"
        is_top_level)

include(cmake/utils.cmake)
include(GNUInstallDirs)

option(CHESS-ENGINE_BUILD_TESTS "Build chess-engine tests" OFF)
option(CHESS-ENGINE_BUILD_EXAMPLES "Build chess-engine examples" OFF)
option(CHESS-ENGINE_INSTALL "Generate target for installing chess-engine" ${is_top_level})
set_if_undefined(CHESS-ENGINE_INSTALL_CMAKEDIR
        "${CMAKE_INSTALL_LIBDIR}/cmake/chess-engine-${PROJECT_VERSION}" CACHE STRING
        "Install path for chess-engine package-related CMake files")

if(DEFINED CHESS-ENGINE_SHARED_LIBS)
    set(BUILD_SHARED_LIBS ${CHESS-ENGINE_SHARED_LIBS})
endif()

#------------------------------#
#         Dependencies         #
#------------------------------#

#TODO: Add dependencies

#------------------------------#
#         Source files         #
#------------------------------#

include(GenerateExportHeader)
set(export_file_name "export_shared.h")

if(NOT BUILD_SHARED_LIBS)
    set(export_file_name "export_static.h")
endif()

generate_export_header(chess-engine EXPORT_FILE_NAME include/${export_file_name})

set(public_headers
        include/export.h
        include/chess-engine.h)
set(sources
        ${public_headers}
        src/board.cpp
        src/figure.cpp)
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${sources})

list(APPEND public_headers
        "${CMAKE_CURRENT_BINARY_DIR}/include/${export_file_name}")
list(APPEND sources
        "${CMAKE_CURRENT_BINARY_DIR}/include/${export_file_name}")

#------------------------------#
#         Target settings      #
#------------------------------#

include(CMakePackageConfigHelpers)

target_sources(chess-engine PRIVATE ${sources})
if(NOT BUILD_SHARED_LIBS)
    target_compile_definitions(chess-engine
            PUBLIC
            CHESS_ENGINE_STATIC_DEFINE)
endif()

target_include_directories(chess-engine
        PUBLIC
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>"
        "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
        PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/src")

set_target_properties(chess-engine PROPERTIES
        PUBLIC_HEADER "${public_headers}"
        SOVERSION ${PROJECT_VERSION_MAJOR}
        VERSION ${PROJECT_VERSION})