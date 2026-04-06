#include "headers/bitboard_operations.hpp"

#include <cmath>
#include <cstdlib>
#include <cstdint>
#include <cstdio>

static const int right_bits[64] = {
        7, 6, 5, 4, 3, 2, 1, 0,
        7, 6, 5, 4, 3, 2, 1, 0,
        7, 6, 5, 4, 3, 2, 1, 0,
        7, 6, 5, 4, 3, 2, 1, 0,
        7, 6, 5, 4, 3, 2, 1, 0,
        7, 6, 5, 4, 3, 2, 1, 0,
        7, 6, 5, 4, 3, 2, 1, 0,
        7, 6, 5, 4, 3, 2, 1, 0
};

static const int left_bits[64] = {
        0, 1, 2, 3, 4, 5, 6, 7,
        0, 1, 2, 3, 4, 5, 6, 7,
        0, 1, 2, 3, 4, 5, 6, 7,
        0, 1, 2, 3, 4, 5, 6, 7,
        0, 1, 2, 3, 4, 5, 6, 7,
        0, 1, 2, 3, 4, 5, 6, 7,
        0, 1, 2, 3, 4, 5, 6, 7,
        0, 1, 2, 3, 4, 5, 6, 7
};

namespace chess::magic_numbers {

Bitboard generate_random_64bit();

static Bitboard set_horizontal_pin_board(uint8_t square, uint8_t blockers){
    Bitboard board = 0;
    const int right = right_bits[square];
    const int left = left_bits[square];

    for (int i = 0; i < right; i++){
        if (bitboard_operations::get_bit(blockers, i)){
            bitboard_operations::set_1(board, square + (i + 1));
        }
    }

    for (int i = 0; i < left; i++){
        if (bitboard_operations::get_bit(blockers, i + right)){
            bitboard_operations::set_1(board, square - (i + 1));
        }
    }

    return board;
}

static uint16_t get_horizontal_pin_mask_hash(Bitboard board, uint64_t magic_number){
    return (uint16_t)((board * magic_number) >> (64 - 7));
}

static bool is_horizontal_pin_magic_number_valid(uint8_t square, uint64_t magic_number){
    Bitboard board;
    uint16_t hash;
    const uint16_t number_of_positions = pow(2, 7);
    auto* array = new bool[number_of_positions]();

    for (int i = 0; i < number_of_positions; i++){
        board = set_horizontal_pin_board(square, i);
        hash = get_horizontal_pin_mask_hash(board, magic_number);

        if (array[hash]){
            delete[] array;
            return false;
        }
        array[hash] = true;
    }

    delete[] array;
    return true;
}

Bitboard generate_horizontal_pin_magic_number(uint8_t square){
    uint64_t magic_number;
    int i = 0;

    do {
        magic_number = generate_random_64bit() & generate_random_64bit() & generate_random_64bit();
        i++;
    } while (!is_horizontal_pin_magic_number_valid(square, magic_number));

    return magic_number;
}

void fancy_print_horizontal_pin_magic_numbers(){
    for (uint8_t i = 0; i < 64; i++){
        printf("%llu,\n", generate_horizontal_pin_magic_number(i));
    }
}

}  // namespace chess::magic_numbers
