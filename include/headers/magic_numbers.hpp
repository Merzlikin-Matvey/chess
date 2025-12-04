#pragma once

#include <array>
#include <cstdint>
#include <iostream>

typedef uint64_t Bitboard;


extern "C" {
#include "C functions/magic_numbers.h"
}

namespace chess::magic_numbers {
    inline Bitboard generate_rook_magic_number(uint8_t square) { return ::_generate_rook_magic_number(square); }

    inline std::array<Bitboard, 64> generate_rook_magic_numbers() {
        std::array<Bitboard, 64> magic_numbers{};
        for (uint8_t square = 0; square < 64; square++) {
            magic_numbers[square] = generate_rook_magic_number(square);
        }
        return magic_numbers;
    }

    inline void fancy_print_rook_magic_numbers() {
        std::array<Bitboard, 64> magic_numbers = generate_rook_magic_numbers();
        for (uint8_t square = 0; square < 64; square += 4) {
            std::cout << "0x" << std::hex << magic_numbers[square] << ", "
                      << "0x" << std::hex << magic_numbers[square + 1] << ", "
                      << "0x" << std::hex << magic_numbers[square + 2] << ", "
                      << "0x" << std::hex << magic_numbers[square + 3] << "," << std::endl;
        }
    }

    inline Bitboard generate_bishop_magic_number(uint8_t square) { return ::_generate_bishop_magic_number(square); }

    inline std::array<Bitboard, 64> generate_bishop_magic_numbers() {
        std::array<Bitboard, 64> magic_numbers{};
        for (uint8_t square = 0; square < 64; square++) {
            magic_numbers[square] = generate_bishop_magic_number(square);
        }
        return magic_numbers;
    }

    inline void fancy_print_bishop_magic_numbers() {
        std::array<Bitboard, 64> magic_numbers = generate_bishop_magic_numbers();
        for (uint8_t square = 0; square < 64; square += 4) {
            std::cout << "0x" << std::hex << magic_numbers[square] << ", "
                      << "0x" << std::hex << magic_numbers[square + 1] << ", "
                      << "0x" << std::hex << magic_numbers[square + 2] << ", "
                      << "0x" << std::hex << magic_numbers[square + 3] << "," << std::endl;
        }
    }
} // namespace chess::magic_numbers
