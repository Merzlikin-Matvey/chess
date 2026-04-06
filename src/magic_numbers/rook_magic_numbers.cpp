#include "headers/bitboard_operations.hpp"

#include <cmath>
#include <cstdlib>
#include <cstdint>


static const int up_bits[64] = {
        6, 6, 6, 6, 6, 6, 6, 6,
        5, 5, 5, 5, 5, 5, 5, 5,
        4, 4, 4, 4, 4, 4, 4, 4,
        3, 3, 3, 3, 3, 3, 3, 3,
        2, 2, 2, 2, 2, 2, 2, 2,
        1, 1, 1, 1, 1, 1, 1, 1,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0
};

static const int down_bits[64] = {
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        1, 1, 1, 1, 1, 1, 1, 1,
        2, 2, 2, 2, 2, 2, 2, 2,
        3, 3, 3, 3, 3, 3, 3, 3,
        4, 4, 4, 4, 4, 4, 4, 4,
        5, 5, 5, 5, 5, 5, 5, 5,
        6, 6, 6, 6, 6, 6, 6, 6
};

static const int right_bits[64] = {
        6, 5, 4, 3, 2, 1, 0, 0,
        6, 5, 4, 3, 2, 1, 0, 0,
        6, 5, 4, 3, 2, 1, 0, 0,
        6, 5, 4, 3, 2, 1, 0, 0,
        6, 5, 4, 3, 2, 1, 0, 0,
        6, 5, 4, 3, 2, 1, 0, 0,
        6, 5, 4, 3, 2, 1, 0, 0,
        6, 5, 4, 3, 2, 1, 0, 0
};

static const int left_bits[64] = {
        0, 0, 1, 2, 3, 4, 5, 6,
        0, 0, 1, 2, 3, 4, 5, 6,
        0, 0, 1, 2, 3, 4, 5, 6,
        0, 0, 1, 2, 3, 4, 5, 6,
        0, 0, 1, 2, 3, 4, 5, 6,
        0, 0, 1, 2, 3, 4, 5, 6,
        0, 0, 1, 2, 3, 4, 5, 6,
        0, 0, 1, 2, 3, 4, 5, 6
};

namespace chess::magic_numbers {

Bitboard generate_random_64bit();

static Bitboard set_rook_board(uint8_t square, uint16_t blockers) {
    Bitboard board = 0;
    const int up = up_bits[square];
    const int down = down_bits[square];
    const int right = right_bits[square];
    const int left = left_bits[square];

    for (int i = 0; i < up; i++) {
        if (bitboard_operations::get_bit(blockers, i)){
            bitboard_operations::set_1(board, square + (i + 1) * 8);
        }
    }

    for (int i = 0; i < down; i++) {
        if (bitboard_operations::get_bit(blockers, i + up)){
            bitboard_operations::set_1(board, square - (i + 1) * 8);
        }
    }

    for (int i = 0; i < right; i++) {
        if (bitboard_operations::get_bit(blockers, i + up + down)){
            bitboard_operations::set_1(board, square + i + 1);
        }
    }

    for (int i = 0; i < left; i++) {
        if (bitboard_operations::get_bit(blockers, i + up + down + right)){
            bitboard_operations::set_1(board, square - i - 1);
        }
    }

    return board;
}

static uint8_t get_number_of_rook_bits(uint8_t square) {
    return up_bits[square] + down_bits[square] + right_bits[square] + left_bits[square];
}

static uint16_t get_rook_hash(Bitboard board, uint64_t magic_number, uint8_t square) {
    return (board * magic_number) >> (64 - get_number_of_rook_bits(square));
}

static bool is_rook_magic_number_valid(uint64_t magic_number, uint8_t square) {
    Bitboard board;
    uint16_t hash;
    const uint8_t number_of_bits = get_number_of_rook_bits(square);
    const uint16_t number_of_positions = pow(2, number_of_bits);
    auto* array = new bool[number_of_positions]();

    for (uint16_t i = 0; i < pow(2, number_of_bits); i++){
        board = set_rook_board(square, i);
        hash = get_rook_hash(board, magic_number, square);
        if (array[hash]){
            delete[] array;
            return false;
        }
        array[hash] = true;
    }
    delete[] array;
    return true;
}

Bitboard generate_rook_magic_number(uint8_t square) {
    uint64_t magic_number;
    do {
        magic_number = generate_random_64bit() & generate_random_64bit() & generate_random_64bit();
    } while (!is_rook_magic_number_valid(magic_number, square));
    return magic_number;
}

}  // namespace chess::magic_numbers
