#include "headers/C functions/magic_numbers.h"
#include "headers/C functions/bitboard_operations.h"

#include <math.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>


const int right_bits[64] = {
        7, 6, 5, 4, 3, 2, 1, 0,
        7, 6, 5, 4, 3, 2, 1, 0,
        7, 6, 5, 4, 3, 2, 1, 0,
        7, 6, 5, 4, 3, 2, 1, 0,
        7, 6, 5, 4, 3, 2, 1, 0,
        7, 6, 5, 4, 3, 2, 1, 0,
        7, 6, 5, 4, 3, 2, 1, 0,
        7, 6, 5, 4, 3, 2, 1, 0
};

const int left_bits[64] = {
        0, 1, 2, 3, 4, 5, 6, 7,
        0, 1, 2, 3, 4, 5, 6, 7,
        0, 1, 2, 3, 4, 5, 6, 7,
        0, 1, 2, 3, 4, 5, 6, 7,
        0, 1, 2, 3, 4, 5, 6, 7,
        0, 1, 2, 3, 4, 5, 6, 7,
        0, 1, 2, 3, 4, 5, 6, 7,
        0, 1, 2, 3, 4, 5, 6, 7
};

Bitboard _set_horizontal_pin_board(uint8_t square, uint8_t blockers){
    Bitboard board = 0;
    int right = right_bits[square];
    int left = left_bits[square];

    for (int i = 0; i < right; i++){
        if (_c_bitboard_operations_get_bit(blockers, i)){
            _c_bitboard_operations_set_1(&board, square + (i + 1));
        }
    }

    for (int i = 0; i < left; i++){
        if (_c_bitboard_operations_get_bit(blockers, i + right)){
            _c_bitboard_operations_set_1(&board, square - (i + 1));
        }
    }

    return board;
}

uint16_t _get_horizontal_pin_mask_hash(Bitboard board, uint64_t magic_number){
    return (uint16_t)((board * magic_number) >> (64 - 7));
}

bool is_horizontal_pin_magic_number_valid(uint8_t square, uint64_t magic_number){
    Bitboard board;
    uint16_t hash;
    uint16_t number_of_positions = pow(2, 7);
    bool* array = calloc(number_of_positions, sizeof(bool));

    for (int i = 0; i < number_of_positions; i++){
        board = _set_horizontal_pin_board(square, i);
        hash = _get_horizontal_pin_mask_hash(board, magic_number);

        if (array[hash]){
            free(array);
            return false;
        }
        array[hash] = true;
    }

    free(array);
    return true;
}

Bitboard _generate_horizontal_pin_magic_number(uint8_t square){
    uint64_t magic_number;
    int i = 0;

    do {
        magic_number = _generate_random_64bit() & _generate_random_64bit() & _generate_random_64bit();
        i++;
    } while (!is_horizontal_pin_magic_number_valid(square, magic_number));

    return magic_number;
}

void _fancy_print_horizontal_pin_magic_numbers(){
    for (uint8_t i = 0; i < 64; i++){
        printf("%llu,\n", _generate_horizontal_pin_magic_number(i));
    }
}

