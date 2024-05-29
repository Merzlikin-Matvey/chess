cmake_minimum_required(VERSION 3.14)
project(chess-lib
        VERSION 0.4.4
        DESCRIPTION "Chess library"
        LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 23)

#------------------------------#
# General settings and options #
#------------------------------#

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fconstexpr-ops-limit=2147483647 -fconstexpr-loop-limit=2147483647")
endif()

if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fconstexpr-steps=2147483647")
endif()

add_definitions(-O3)

add_library(chess-lib SHARED
        src/wasm/wasm.cpp
        src/wasm/wasm.cpp)
add_library(chess-lib::chess-lib ALIAS chess-lib)

string(COMPARE EQUAL "${CMAKE_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}"
        is_top_level)

include(cmake/utils.cmake)
include(GNUInstallDirs)

string(COMPARE EQUAL "${CMAKE_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}" is_top_level)

option(CHESS_LIB_BUILD_TESTS "Build chess-lib tests" OFF)
option(CHESS_LIB_BUILD_EXAMPLES "Build chess-lib examples" ON)
option(CHESS_LIB_INSTALL "Generate target for installing chess-lib" ${is_top_level})
option(WASM_INTERFACE "Enable WebAssembly interface" OFF)
set_if_undefined(CHESS_LIB_INSTALL_CMAKEDIR
        "${CMAKE_INSTALL_LIBDIR}/cmake/chess-lib-${PROJECT_VERSION}" CACHE STRING
        "Install path for chess-lib package-related CMake files")

if(DEFINED CHESS_LIB_SHARED_LIBS)
    set(BUILD_SHARED_LIBS ${CHESS_LIB_SHARED_LIBS})
endif()

#------------------------------#
#         Dependencies         #
#------------------------------#

if (WASM_INTERFACE)
    find_package(emscripten REQUIRED)
endif ()

#------------------------------#
#         Source files         #
#------------------------------#

include(GenerateExportHeader)
set(export_file_name "export_shared.h")

if(NOT BUILD_SHARED_LIBS)
    set(export_file_name "export_static.h")
endif()

generate_export_header(chess-lib EXPORT_FILE_NAME include/${export_file_name})


set(public_headers
        include/export.h
        include/chess-lib.hpp
        include/headers/bitboard_operations.hpp
        include/headers/board.hpp
        include/headers/constants.hpp
        include/headers/zobrist.hpp
        include/headers/bitboard_lines.hpp
        include/headers/fen.hpp
        include/headers/move.hpp
        include/headers/notations.hpp
        include/headers/masks/rook_masks.hpp
        include/headers/bitboard_lines.hpp
        include/headers/magic_numbers.hpp
        include/headers/masks/masks_utils.hpp
        include/headers/masks/bishop_masks.hpp
        include/headers/masks/king_knight_masks.hpp
        include/headers/magic_numbers_constants.hpp
        include/headers/masks/vertical_pin_masks.hpp
        include/headers/masks/number_of_bits.hpp
        include/headers/masks/up_right_diagonal_pin_masks.hpp
        include/headers/masks/down_right_diagonal_pin_masks.hpp
        include/headers/magic_numbers_constants.hpp
        include/headers/pin_mask_magic_numbers.hpp
        include/headers/masks/masks.hpp
        include/headers/masks/pawn_masks.hpp
        include/headers/check_and_checkmate.hpp
        src/board/begin_and_end.cpp
)

set(sources
        ${public_headers}
        src/board/board.cpp
        src/board/fen.cpp
        src/board/output.cpp
        src/zobrist.cpp
        src/board/history.cpp
        src/move.cpp
        src/notations.cpp
        src/board/get_legal_moves.cpp
        src/magic_numbers/random_generator.c
        src/magic_numbers/bishop_magic_numbers.c
        src/magic_numbers/rook_magic_numbers.c
        src/magic_numbers/vertical_pin_mask_magic_numbers.c
        src/magic_numbers/horizontal_pin_mask_magic_numbers.c
        src/magic_numbers/up_right_pin_mask_magic_numbers.c
        src/magic_numbers/down_right_pin_mask_magic_numbers.c
        src/pawn_mask.cpp
        src/mask_to_moves.cpp
        src/move_array.cpp
)

if (WASM_INTERFACE)
    add_subdirectory(wasm)
    set(WASM_FILES src/wasm/wasm.cpp)

    list(APPEND sources ${WASM_FILES})
endif()

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${sources})

list(APPEND public_headers
        "${CMAKE_CURRENT_BINARY_DIR}/include/${export_file_name}")
list(APPEND sources
        "${CMAKE_CURRENT_BINARY_DIR}/include/${export_file_name}")

#------------------------------#
#        Target settings       #
#------------------------------#

include(CMakePackageConfigHelpers)

target_sources(chess-lib PRIVATE ${sources})
if(NOT BUILD_SHARED_LIBS)
    target_compile_definitions(chess-lib
            PUBLIC
            CHESS_LIB_STATIC_DEFINE)
endif()


target_include_directories(chess-lib
        PUBLIC
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/dependencies>"
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>"
        "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
        PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/src")

set_target_properties(chess-lib PROPERTIES
        PUBLIC_HEADER "${public_headers}"
        SOVERSION ${PROJECT_VERSION_MAJOR}
        VERSION ${PROJECT_VERSION})


#------------------------------#
#         Installation         #
#------------------------------#
if(CHESS_LIB_INSTALL AND NOT CMAKE_SKIP_INSTALL_RULES)
    if(WIN32)
        message(STATUS "Windows detected")
        set(CMAKE_INSTALL_PREFIX "C:/Users/$ENV{USERNAME}/chess-lib")
    elseif (UNIX)
        message(STATUS "Unix detected")
        set(CMAKE_INSTALL_PREFIX "/home/$ENV{USER}/chess-lib")
    endif()

    if(NOT EXISTS ${CMAKE_INSTALL_PREFIX})
        file(MAKE_DIRECTORY ${CMAKE_INSTALL_PREFIX})
    endif()


    message(STATUS "Library will be installed to: ${CMAKE_INSTALL_PREFIX}/bin")


    configure_package_config_file(cmake/chess-lib-config.cmake.in chess-lib-config.cmake
            INSTALL_DESTINATION "${CHESS_LIB_INSTALL_CMAKEDIR}")

    write_basic_package_version_file(chess-lib-config-version.cmake
            COMPATIBILITY SameMajorVersion)

    install(TARGETS chess-lib EXPORT chess-lib_export
            RUNTIME COMPONENT chess-lib
            LIBRARY COMPONENT chess-lib NAMELINK_COMPONENT chess-lib-dev
            ARCHIVE COMPONENT chess-lib-dev
            INCLUDES DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}")
    install(DIRECTORY include/
            TYPE INCLUDE
            COMPONENT chess-lib-dev)
    install(FILES "${CMAKE_CURRENT_BINARY_DIR}/include/${export_file_name}"
            COMPONENT chess-lib-dev
            DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/chess-lib")

    set(targets_file "chess-lib-shared-targets.cmake")

    if(NOT BUILD_SHARED_LIBS)
        set(targets_file "chess-lib-static-targets.cmake")
    endif()

    install(EXPORT chess-lib_export
            COMPONENT chess-lib-dev
            FILE "${targets_file}"
            DESTINATION "${CHESS_LIB_INSTALL_CMAKEDIR}"
            NAMESPACE chess-lib::)

    install(FILES
            "${CMAKE_CURRENT_BINARY_DIR}/chess-lib-config.cmake"
            "${CMAKE_CURRENT_BINARY_DIR}/chess-lib-config-version.cmake"
            COMPONENT chess-lib-dev
            DESTINATION "${CHESS_LIB_INSTALL_CMAKEDIR}")

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

if(CHESS_LIB_BUILD_EXAMPLES)
    add_subdirectory(example)
endif()
