cmake_minimum_required(VERSION 3.14)
project(chess-engine
        VERSION 0.2.4
        DESCRIPTION "Chess engine"
        LANGUAGES C CXX)

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")
set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -flto")
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fconstexpr-ops-limit=1000000000 -fconstexpr-loop-limit=1000000000")

#------------------------------#
# General settings and options #
#------------------------------#

add_library(chess-engine SHARED
        src/magic_numbers/generate_rook_magic_numbers.c
        src/magic_numbers/generate_vertical_check_mask_magic_numbers.c
        include/headers/masks/vertical_pin_masks.hpp
        src/magic_numbers/generate_horizontal_pin_mask_magic_numbers.c
        include/headers/masks/number_of_bits.hpp)

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

find_package(OpenMP)
if (OPENMP_FOUND)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()

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
        dependencies/json/json.hpp
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
        src/magic_numbers/generate_bishop_magic_numbers.c
)


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


    message(STATUS "Library will be installed to: ${CMAKE_INSTALL_PREFIX}/bin")


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
