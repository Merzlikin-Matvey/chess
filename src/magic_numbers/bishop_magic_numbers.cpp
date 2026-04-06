#include "headers/bitboard_operations.hpp"

#include <cmath>
#include <cstdlib>
#include <cstdint>

namespace chess::magic_numbers {

Bitboard generate_random_64bit();

static const int up_right_bits[64] = {
        6, 5, 4, 3, 2, 1, 0, 0,
        5, 5, 4, 3, 2, 1, 0, 0,
        4, 4, 4, 3, 2, 1, 0, 0,
        3, 3, 3, 3, 2, 1, 0, 0,
        2, 2, 2, 2, 2, 1, 0, 0,
        1, 1, 1, 1, 1, 1, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0
};

static const int down_left_bits[64] = {
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 1, 1, 1, 1, 1, 1,
        0, 0, 1, 2, 2, 2, 2, 2,
        0, 0, 1, 2, 3, 3, 3, 3,
        0, 0, 1, 2, 3, 4, 4, 4,
        0, 0, 1, 2, 3, 4, 5, 5,
        0, 0, 1, 2, 3, 4, 5, 6
};

static const int up_left_bits[64] = {
        0, 0, 1, 2, 3, 4, 5, 6,
        0, 0, 1, 2, 3, 4, 5, 5,
        0, 0, 1, 2, 3, 4, 4, 4,
        0, 0, 1, 2, 3, 3, 3, 3,
        0, 0, 1, 2, 2, 2, 2, 2,
        0, 0, 1, 1, 1, 1, 1, 1,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0
};


static const int down_right_bits[64] = {
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        1, 1, 1, 1, 1, 1, 0, 0,
        2, 2, 2, 2, 2, 1, 0, 0,
        3, 3, 3, 3, 2, 1, 0, 0,
        4, 4, 4, 3, 2, 1, 0, 0,
        5, 5, 4, 3, 2, 1, 0, 0,
        6, 5, 4, 3, 2, 1, 0, 0
};



static Bitboard set_bishop_board(uint8_t square, uint16_t blockers) {
    Bitboard board = 0;
    const int up_right = up_right_bits[square];
    const int down_left = down_left_bits[square];
    const int up_left = up_left_bits[square];
    const int down_right = down_right_bits[square];

    for (int i = 0; i < up_right; i++){
        if (bitboard_operations::get_bit(blockers, i)){
            bitboard_operations::set_1(board, square + (i + 1) * 9);
        }
    }

    for (int i = 0; i < down_left; i++){
        if (bitboard_operations::get_bit(blockers, i + up_right)){
            bitboard_operations::set_1(board, square - (i + 1) * 9);
        }
    }

    for (int i = 0; i < up_left; i++){
        if (bitboard_operations::get_bit(blockers, i + up_right + down_left)){
            bitboard_operations::set_1(board, square + (i + 1) * 7);
        }
    }

    for (int i = 0; i < down_right; i++){
        if (bitboard_operations::get_bit(blockers, i + up_right + down_left + up_left)){
            bitboard_operations::set_1(board, square - (i + 1) * 7);
        }
    }


    return board;

}

static uint8_t get_number_of_bishop_bits(uint8_t square) {
    return up_right_bits[square] + down_left_bits[square] + up_left_bits[square] + down_right_bits[square];
}

static uint16_t get_bishop_hash(Bitboard board, uint64_t magic_number, uint8_t square) {
    return (board * magic_number) >> (64 - get_number_of_bishop_bits(square));
}

static bool is_bishop_magic_number_valid(uint64_t magic_number, uint8_t square) {
    Bitboard board;
    uint16_t hash;
    const uint8_t number_of_bits = get_number_of_bishop_bits(square);
    const uint16_t number_of_positions = pow(2, number_of_bits);
    auto* array = new bool[number_of_positions]();

    for (uint16_t i = 0; i < pow(2, number_of_bits); i++){
        board = set_bishop_board(square, i);
        hash = get_bishop_hash(board, magic_number, square);
        if (array[hash]){
            delete[] array;
            return false;
        }
        array[hash] = true;
    }
    delete[] array;
    return true;
}

Bitboard generate_bishop_magic_number(uint8_t square) {
    uint64_t magic_number;
    do {
        magic_number = generate_random_64bit() & generate_random_64bit() & generate_random_64bit();
    } while (!is_bishop_magic_number_valid(magic_number, square));
    return magic_number;
}

}  // namespace chess::magic_numbers
