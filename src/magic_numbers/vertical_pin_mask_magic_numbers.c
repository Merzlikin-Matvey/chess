#include "headers/C functions/magic_numbers.h"
#include "headers/C functions/bitboard_operations.h"

#include <math.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

const int up_bits[64] = {
        7, 7, 7, 7, 7, 7, 7, 7,
        6, 6, 6, 6, 6, 6, 6, 6,
        5, 5, 5, 5, 5, 5, 5, 5,
        4, 4, 4, 4, 4, 4, 4, 4,
        3, 3, 3, 3, 3, 3, 3, 3,
        2, 2, 2, 2, 2, 2, 2, 2,
        1, 1, 1, 1, 1, 1, 1, 1,
        0, 0, 0, 0, 0, 0, 0, 0,
};

const int down_bits[64] = {
        0, 0, 0, 0, 0, 0, 0, 0,
        1, 1, 1, 1, 1, 1, 1, 1,
        2, 2, 2, 2, 2, 2, 2, 2,
        3, 3, 3, 3, 3, 3, 3, 3,
        4, 4, 4, 4, 4, 4, 4, 4,
        5, 5, 5, 5, 5, 5, 5, 5,
        6, 6, 6, 6, 6, 6, 6, 6,
        7, 7, 7, 7, 7, 7, 7, 7
};

Bitboard _set_vertical_pin_board(uint8_t square, uint8_t blockers){
    Bitboard board = 0;
    int up = up_bits[square];
    int down = down_bits[square];

    for (int i = 0; i < up; i++){
        if (_c_bitboard_operations_get_bit(blockers, i)){
            _c_bitboard_operations_set_1(&board, square + 8 * (i + 1));
        }
    }

    for (int i = 0; i < down; i++){
        if (_c_bitboard_operations_get_bit(blockers, i + up)){
            _c_bitboard_operations_set_1(&board, square - 8 * (i + 1));
        }
    }

    return board;
}

uint16_t _get_vertical_pin_mask_hash(Bitboard board, uint64_t magic_number){
    return (uint16_t)((board * magic_number) >> (64 - 7));
}

bool is_vertical_pin_magic_number_valid(uint8_t square, uint64_t magic_number){
    Bitboard board;
    uint16_t hash;
    uint16_t number_of_positions = pow(2, 7);
    bool* array = calloc(number_of_positions, sizeof(bool));

    for (uint16_t i = 0; i < number_of_positions; i++){
        board = _set_vertical_pin_board(square, i);
        hash = _get_vertical_pin_mask_hash(board, magic_number);

        if (array[hash]){
            free(array);
            return false;
        }
        array[hash] = true;
    }

    free(array);
    return true;
}

Bitboard _generate_vertical_pin_magic_number(uint8_t square){
    uint64_t magic_number;

    do {
        magic_number = _generate_random_64bit() & _generate_random_64bit() & _generate_random_64bit();
    } while (!is_vertical_pin_magic_number_valid(square, magic_number));

    return magic_number;
}

void _fancy_print_vertical_pin_magic_numbers(){
    for (uint8_t i = 0; i < 64; i++){
        printf("%llu,\n", _generate_vertical_pin_magic_number(i));
    }
}

