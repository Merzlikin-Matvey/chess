#pragma once

#include <array>
#include <iostream>
#include <memory>

typedef uint64_t Bitboard;

extern "C" {
    #include "C functions/magic_numbers.h"
}

namespace chess::magic_numbers {
    inline Bitboard generate_vertical_pin_magic_number(uint8_t square){
        return _generate_vertical_pin_magic_number(square);
    }

    inline std::array<Bitboard, 64> generate_vertical_pin_magic_numbers() {
        std::array<Bitboard, 64> magic_numbers{};
        for (uint8_t square = 0; square < 64; square++) {
            magic_numbers[square] = generate_vertical_pin_magic_number(square);
        }
        return magic_numbers;
    }

    inline void fancy_print_vertical_pin_magic_numbers() {
        _fancy_print_vertical_pin_magic_numbers();
    }

    inline Bitboard generate_horizontal_pin_magic_number(uint8_t square){
        return ::_generate_horizontal_pin_magic_number(square);
    }

    inline std::array<Bitboard, 64> generate_horizontal_pin_magic_numbers() {
        std::array<Bitboard, 64> magic_numbers{};
        for (uint8_t square = 0; square < 64; square++) {
            magic_numbers[square] = generate_horizontal_pin_magic_number(square);
        }
        return magic_numbers;
    }

    inline void fancy_print_horizontal_pin_magic_numbers() {
        _fancy_print_horizontal_pin_magic_numbers();
    }

    inline Bitboard generate_up_right_pin_magic_number(uint8_t square){
        return ::_generate_up_right_pin_magic_number(square);
    }

    inline std::array<Bitboard, 64> generate_up_right_pin_magic_numbers() {
        std::array<Bitboard, 64> magic_numbers{};
        for (uint8_t square = 0; square < 64; square++) {
            magic_numbers[square] = generate_up_right_pin_magic_number(square);
        }
        return magic_numbers;
    }

    inline void fancy_print_up_right_pin_magic_numbers() {
        _fancy_print_up_right_pin_magic_numbers();
    }

    inline Bitboard generate_down_right_pin_magic_number(uint8_t square){
        return ::_generate_down_right_pin_magic_number(square);
    }

    inline std::array<Bitboard, 64> generate_down_right_pin_magic_numbers() {
        std::array<Bitboard, 64> magic_numbers{};
        for (uint8_t square = 0; square < 64; square++) {
            magic_numbers[square] = generate_down_right_pin_magic_number(square);
        }
        return magic_numbers;
    }

    inline void fancy_print_down_right_pin_magic_numbers() {
        _fancy_print_down_right_pin_magic_numbers();
    }
}