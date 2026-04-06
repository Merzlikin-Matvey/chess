#include "headers/bitboard_operations.hpp"

#include <cmath>
#include <cstdlib>
#include <cstdint>
#include <cstdio>

static const int up_left_bits[64] = {
        0, 1, 2, 3, 4, 5, 6, 7,
        0, 1, 2, 3, 4, 5, 6, 6,
        0, 1, 2, 3, 4, 5, 5, 5,
        0, 1, 2, 3, 4, 4, 4, 4,
        0, 1, 2, 3, 3, 3, 3, 3,
        0, 1, 2, 2, 2, 2, 2, 2,
        0, 1, 1, 1, 1, 1, 1, 1,
        0, 0, 0, 0, 0, 0, 0, 0
};

static const int down_right_bits[64] = {
        0, 0, 0, 0, 0, 0, 0, 0,
        1, 1, 1, 1, 1, 1, 1, 0,
        2, 2, 2, 2, 2, 2, 1, 0,
        3, 3, 3, 3, 3, 2, 1, 0,
        4, 4, 4, 4, 3, 2, 1, 0,
        5, 5, 5, 4, 3, 2, 1, 0,
        6, 6, 5, 4, 3, 2, 1, 0,
        7, 6, 5, 4, 3, 2, 1, 0
};

namespace chess::magic_numbers::generators {

Bitboard generate_random_64bit();

static Bitboard set_down_right_pin_board(uint8_t square, uint8_t blockers){
    Bitboard board = 0;
    const int up_left = up_left_bits[square];
    const int down_right = down_right_bits[square];

    for (int i = 0; i < up_left; i++){
        if (bitboard_operations::get_bit(blockers, i)){
            bitboard_operations::set_1(board, square + 7 * (i + 1));
        }
    }

    for (int i = 0; i < down_right; i++){
        if (bitboard_operations::get_bit(blockers, i + up_left)){
            bitboard_operations::set_1(board, square - 7 * (i + 1));
        }
    }

    return board;
}

static uint8_t get_number_of_down_right_pin_mask_bits(uint8_t square) {
    return up_left_bits[square] + down_right_bits[square];
}

static uint16_t get_down_right_pin_mask_hash(Bitboard board, uint64_t magic_number, uint8_t square){
    const uint8_t number_of_bits = get_number_of_down_right_pin_mask_bits(square);
    return (uint16_t)((board * magic_number) >> (64 - number_of_bits));
}

static bool is_down_right_pin_magic_number_valid(uint8_t square, uint64_t magic_number){
    Bitboard board;
    uint16_t hash;
    const uint16_t number_of_positions = pow(2, get_number_of_down_right_pin_mask_bits(square));
    auto* array = new bool[number_of_positions]();

    for (uint16_t blocker = 0; blocker < number_of_positions; blocker++){
        board = set_down_right_pin_board(square, blocker);
        hash = get_down_right_pin_mask_hash(board, magic_number, square);
        if (array[hash]){
            delete[] array;
            return false;
        }
        array[hash] = true;
    }

    delete[] array;
    return true;
}

Bitboard generate_down_right_pin_magic_number(uint8_t square){
    Bitboard magic_number;

    for (uint8_t i = 0; i < 32; i++){
        magic_number = pow(2, i);
        if (is_down_right_pin_magic_number_valid(square, magic_number)) {
            return magic_number;
        }
    }

    do {
        magic_number = generate_random_64bit() & generate_random_64bit() & generate_random_64bit();
    } while (!is_down_right_pin_magic_number_valid(square, magic_number));
    return magic_number;
}

void fancy_print_down_right_pin_magic_numbers(){
    for (uint8_t i = 0; i < 64; i++){
        printf("%llu,\n", generate_down_right_pin_magic_number(i));
    }
}

}  // namespace chess::magic_numbers
