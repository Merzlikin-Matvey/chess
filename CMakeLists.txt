cmake_minimum_required(VERSION 3.14)
project(chess-lib
        VERSION 0.4.4
        DESCRIPTION "Chess library"
        LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

#------------------------------#
# General settings and options #
#------------------------------#

message(STATUS "COMPILER: ${CMAKE_CXX_COMPILER_ID}")

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fconstexpr-ops-limit=2147483647 -fconstexpr-loop-limit=2147483647")
endif ()

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fconstexpr-steps=2147483647")
endif ()

if (CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fconstexpr-steps=2147483647")
endif ()

add_definitions(-O3)

add_library(chess-lib SHARED)
add_library(chess-lib::chess-lib ALIAS chess-lib)

option(CHESS_LIB_BUILD_EXAMPLES "Build chess-lib examples" ON)
option(CHESS_LIB_BUILD_UCI "Build chess-lib uci" ON)
option(WASM_INTERFACE "Enable WebAssembly interface" OFF)


if (DEFINED CHESS_LIB_SHARED_LIBS)
    set(BUILD_SHARED_LIBS ${CHESS_LIB_SHARED_LIBS})
endif ()

#------------------------------#
#         Dependencies         #
#------------------------------#

if (WASM_INTERFACE)
    find_package(emscripten REQUIRED)
endif ()

#------------------------------#
#         Source files         #
#------------------------------#

set(public_headers
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
        include/headers/uci.hpp
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
        src/board/begin_and_end.cpp
        src/ai/ai.cpp
        src/ai/evaluate_position.cpp
        src/ai/minimax.cpp
        src/ai/move_sorting.cpp
        src/uci.cpp
)

if (WASM_INTERFACE)
    add_subdirectory(wasm)
    set(WASM_FILES src/wasm/wasm.cpp)

    list(APPEND sources ${WASM_FILES})
endif ()

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${sources})

list(APPEND public_headers
        "${CMAKE_CURRENT_BINARY_DIR}/include/${chess-lib.hpp}")
list(APPEND sources
        "${CMAKE_CURRENT_BINARY_DIR}/include/${chess-lib.hpp}")

#------------------------------#
#        Target settings       #
#------------------------------#

include(CMakePackageConfigHelpers)

target_sources(chess-lib PRIVATE ${sources})
if (NOT BUILD_SHARED_LIBS)
    target_compile_definitions(chess-lib
            PUBLIC
            CHESS_LIB_STATIC_DEFINE)
endif ()


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
#         Testing              #
#------------------------------#

# TODO: Add tests

#------------------------------#
#        Other targets         #
#------------------------------#

if (CHESS_LIB_BUILD_EXAMPLES)
    add_subdirectory(example)
endif ()

if (CHESS_LIB_BUILD_UCI)
    add_subdirectory(uci)
endif ()