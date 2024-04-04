cmake_minimum_required(VERSION 3.14)
project(chess=engine
        VERSION 1.0.0
        DESCRIPTION "Chess engine"
        LANGUAGES CXX)

#------------------------------#
# General settings and options #
#------------------------------#

add_library(chess-engine SHARED)
add_library(chess-engine::chess-engine ALIAS chess-engine)

string(COMPARE EQUAL "${CMAKE_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}"
        is_top_level)

include(cmake/utils.cmake)
include(GNUInstallDirs)

option(CHESS_ENGINE_BUILD_TESTS "Build chess-engine tests" OFF)
option(CHESS_ENGINE_BUILD_EXAMPLES "Build chess-engine examples" OFF)
option(CHESS_ENGINE_INSTALL "Generate target for installing chess-engine" ${is_top_level})
set_if_undefined(CHESS_ENGINE_INSTALL_CMAKEDIR
        "${CMAKE_INSTALL_LIBDIR}/cmake/chess-engine-${PROJECT_VERSION}" CACHE STRING
        "Install path for chess-engine package-related CMake files")

if(DEFINED CHESS_ENGINE_SHARED_LIBS)
    set(BUILD_SHARED_LIBS ${CHESS_ENGINE_SHARED_LIBS})
endif()

#------------------------------#
#         Dependencies         #
#------------------------------#

# TODO: Add dependencies

#------------------------------#
#         Source files         #
#------------------------------#

include(GenerateExportHeader)
set(export_file_name "export_shared.h")

if(NOT BUILD_SHARED_LIBS)
    set(export_file_name "export_static.h")
endif()

generate_export_header(chess-engine EXPORT_FILE_NAME include/chess-engine/${export_file_name})

set(public_headers
        include/chess-engine/export.h
        include/chess-engine/chess-engine.h
        include/json/json.hpp
)
set(sources
        ${public_headers}
        src/board.cpp
        src/figure.cpp)

set(data
    chess_default_positions.json)

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${sources})

list(APPEND public_headers
        "${CMAKE_CURRENT_BINARY_DIR}/include/chess-engine/${export_file_name}")
list(APPEND sources
        "${CMAKE_CURRENT_BINARY_DIR}/include/chess-engine/${export_file_name}")

#------------------------------#
#        Target settings       #
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

#------------------------------#
#         Installation         #
#------------------------------#

if(CHESS_ENGINE_INSTALL AND NOT CMAKE_SKIP_INSTALL_RULES)
    configure_package_config_file(cmake/chess-engine-config.cmake.in chess-engine-config.cmake
            INSTALL_DESTINATION "${CHESS_ENGINE_INSTALL_CMAKEDIR}")

    write_basic_package_version_file(chess-engine-config-version.cmake
            COMPATIBILITY SameMajorVersion)

    install(TARGETS chess-engine EXPORT chess-engine_export
            RUNTIME COMPONENT chess-engine
            LIBRARY COMPONENT chess-engine NAMELINK_COMPONENT chess-engine-dev
            ARCHIVE COMPONENT chess-engine-dev
            INCLUDES DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}")
    install(DIRECTORY include/
            TYPE INCLUDE
            COMPONENT chess-engine-dev)
    install(FILES "${CMAKE_CURRENT_BINARY_DIR}/include/chess-engine/${export_file_name}"
            COMPONENT chess-engine-dev
            DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/chess-engine")

    foreach(file ${data})
        install(FILES ${file}
                DESTINATION ${CMAKE_INSTALL_DATADIR}/chess-engine)
    endforeach()


    set(targets_file "chess-engine-shared-targets.cmake")

    if(NOT BUILD_SHARED_LIBS)
        set(targets_file "chess-engine-static-targets.cmake")
    endif()

    install(EXPORT chess-engine_export
            COMPONENT chess-engine-dev
            FILE "${targets_file}"
            DESTINATION "${CHESS_ENGINE_INSTALL_CMAKEDIR}"
            NAMESPACE chess-engine::)

    install(FILES
            "${CMAKE_CURRENT_BINARY_DIR}/chess-engine-config.cmake"
            "${CMAKE_CURRENT_BINARY_DIR}/chess-engine-config-version.cmake"
            COMPONENT chess-engine-dev
            DESTINATION "${CHESS_ENGINE_INSTALL_CMAKEDIR}")
endif()

#------------------------------#
#         Testing              #
#------------------------------#

# TODO: Add tests

#------------------------------#
#        Other targets         #
#------------------------------#

if(CHESS_ENGINE_EXAMPLES)
    add_subdirectory(example)
endif()
