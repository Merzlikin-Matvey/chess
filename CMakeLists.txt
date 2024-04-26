cmake_minimum_required(VERSION 3.14)
project(chess-engine
        VERSION 0.1.4
        DESCRIPTION "Chess engine"
        LANGUAGES C CXX)

#------------------------------#
# General settings and options #
#------------------------------#

add_library(chess-engine SHARED)
add_library(chess-engine::chess-engine ALIAS chess-engine)

string(COMPARE EQUAL "${CMAKE_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}"
        is_top_level)

include(cmake/utils.cmake)
include(GNUInstallDirs)

string(COMPARE EQUAL "${CMAKE_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}" is_top_level)

option(CHESS_ENGINE_BUILD_TESTS "Build chess-engine tests" OFF)
option(CHESS_ENGINE_BUILD_EXAMPLES "Build chess-engine examples" ON)
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

generate_export_header(chess-engine EXPORT_FILE_NAME include/${export_file_name})

set(public_headers
        include/export.h
        include/chess-engine.hpp
        include/utils.h
        dependencies/json/json.hpp
)
set(sources
        ${public_headers}
        src/board.cpp
        src/figure.cpp
        src/resource_dir.c
        src/path_to_res.cpp
)

set(data
        res/chess_default_positions.json)

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${sources})

list(APPEND public_headers
        "${CMAKE_CURRENT_BINARY_DIR}/include/${export_file_name}")
list(APPEND sources
        "${CMAKE_CURRENT_BINARY_DIR}/include/${export_file_name}")

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
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/dependencies>"
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>"
        "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
        PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/src")

set_target_properties(chess-engine PROPERTIES
        PUBLIC_HEADER "${public_headers}"
        SOVERSION ${PROJECT_VERSION_MAJOR}
        VERSION ${PROJECT_VERSION})

file(COPY ${data} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/res)
message(STATUS "Local resource path: ${CMAKE_CURRENT_BINARY_DIR}/res ..")

#------------------------------#
#         Installation         #
#------------------------------#
if(CHESS_ENGINE_INSTALL AND NOT CMAKE_SKIP_INSTALL_RULES)
    if(WIN32)
        message(STATUS "Windows detected")
        set(CMAKE_INSTALL_PREFIX "C:/Users/$ENV{USERNAME}/chess-engine")
    elseif (UNIX)
        message(STATUS "Unix detected")
        set(CMAKE_INSTALL_PREFIX "/home/$ENV{USER}/chess-engine")
    endif()

    if(NOT EXISTS ${CMAKE_INSTALL_PREFIX})
        file(MAKE_DIRECTORY ${CMAKE_INSTALL_PREFIX})
    endif()

    set(RESOURCE_PATH ${CMAKE_INSTALL_PREFIX}/res)


    message(STATUS "Library will be installed to: ${CMAKE_INSTALL_PREFIX}/bin")
    message(STATUS "Resource path: ${RESOURCE_PATH}")


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
    install(FILES "${CMAKE_CURRENT_BINARY_DIR}/include/${export_file_name}"
            COMPONENT chess-engine-dev
            DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/chess-engine")
    install(FILES ${data}
            DESTINATION ${RESOURCE_PATH})


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

    message(STATUS "Setting paths on the system")
    if(WIN32)
        execute_process(COMMAND net session
                RESULT_VARIABLE IS_ADMIN)
        if(NOT IS_ADMIN EQUAL 0)
            message(WARNING "Administrator rights are required to set paths on the system. Please run CMake as administrator")
        else()
            execute_process(COMMAND powershell -File ${CMAKE_SOURCE_DIR}/scripts/install_paths.ps1 ${CMAKE_INSTALL_PREFIX})
        endif()

    else()
        execute_process(COMMAND bash ${CMAKE_SOURCE_DIR}/scripts/install_paths.sh ${CMAKE_INSTALL_PREFIX})
    endif()

endif()



#------------------------------#
#         Testing              #
#------------------------------#

# TODO: Add tests

#------------------------------#
#        Other targets         #
#------------------------------#

if(CHESS_ENGINE_BUILD_EXAMPLES)
    add_subdirectory(example)
endif()
