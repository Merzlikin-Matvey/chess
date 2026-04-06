#include "headers/bitboard_operations.hpp"

#include <cmath>
#include <cstdlib>
#include <cstdint>
#include <cstdio>

static const int up_bits[64] = {
        7, 7, 7, 7, 7, 7, 7, 7,
        6, 6, 6, 6, 6, 6, 6, 6,
        5, 5, 5, 5, 5, 5, 5, 5,
        4, 4, 4, 4, 4, 4, 4, 4,
        3, 3, 3, 3, 3, 3, 3, 3,
        2, 2, 2, 2, 2, 2, 2, 2,
        1, 1, 1, 1, 1, 1, 1, 1,
        0, 0, 0, 0, 0, 0, 0, 0,
};

static const int down_bits[64] = {
        0, 0, 0, 0, 0, 0, 0, 0,
        1, 1, 1, 1, 1, 1, 1, 1,
        2, 2, 2, 2, 2, 2, 2, 2,
        3, 3, 3, 3, 3, 3, 3, 3,
        4, 4, 4, 4, 4, 4, 4, 4,
        5, 5, 5, 5, 5, 5, 5, 5,
        6, 6, 6, 6, 6, 6, 6, 6,
        7, 7, 7, 7, 7, 7, 7, 7
};

namespace chess::magic_numbers {

Bitboard generate_random_64bit();

static Bitboard set_vertical_pin_board(uint8_t square, uint8_t blockers){
    Bitboard board = 0;
    const int up = up_bits[square];
    const int down = down_bits[square];

    for (int i = 0; i < up; i++){
        if (bitboard_operations::get_bit(blockers, i)){
            bitboard_operations::set_1(board, square + 8 * (i + 1));
        }
    }

    for (int i = 0; i < down; i++){
        if (bitboard_operations::get_bit(blockers, i + up)){
            bitboard_operations::set_1(board, square - 8 * (i + 1));
        }
    }

    return board;
}

static uint16_t get_vertical_pin_mask_hash(Bitboard board, uint64_t magic_number){
    return (uint16_t)((board * magic_number) >> (64 - 7));
}

static bool is_vertical_pin_magic_number_valid(uint8_t square, uint64_t magic_number){
    Bitboard board;
    uint16_t hash;
    const uint16_t number_of_positions = pow(2, 7);
    auto* array = new bool[number_of_positions]();

    for (uint16_t i = 0; i < number_of_positions; i++){
        board = set_vertical_pin_board(square, i);
        hash = get_vertical_pin_mask_hash(board, magic_number);

        if (array[hash]){
            delete[] array;
            return false;
        }
        array[hash] = true;
    }

    delete[] array;
    return true;
}

Bitboard generate_vertical_pin_magic_number(uint8_t square){
    uint64_t magic_number;

    do {
        magic_number = generate_random_64bit() & generate_random_64bit() & generate_random_64bit();
    } while (!is_vertical_pin_magic_number_valid(square, magic_number));

    return magic_number;
}

void fancy_print_vertical_pin_magic_numbers(){
    for (uint8_t i = 0; i < 64; i++){
        printf("%llu,\n", generate_vertical_pin_magic_number(i));
    }
}

}  // namespace chess::magic_numbers
