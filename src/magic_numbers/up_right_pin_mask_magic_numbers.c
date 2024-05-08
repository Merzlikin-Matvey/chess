#include "headers/C functions/magic_numbers.h"
#include "headers/C functions/bitboard_operations.h"

#include <math.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <time.h>


const int up_right_bits[64] = {
        7, 6, 5, 4, 3, 2, 1, 0,
        6, 6, 5, 4, 3, 2, 1, 0,
        5, 5, 5, 4, 3, 2, 1, 0,
        4, 4, 4, 4, 3, 2, 1, 0,
        3, 3, 3, 3, 3, 2, 1, 0,
        2, 2, 2, 2, 2, 2, 1, 0,
        1, 1, 1, 1, 1, 1, 1, 0,
        0, 0, 0, 0, 0, 0, 0, 0
};

const int down_left_bits[64] = {
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 1, 1, 1, 1, 1, 1, 1,
        0, 1, 2, 2, 2, 2, 2, 2,
        0, 1, 2, 3, 3, 3, 3, 3,
        0, 1, 2, 3, 4, 4, 4, 4,
        0, 1, 2, 3, 4, 5, 5, 5,
        0, 1, 2, 3, 4, 5, 6, 6,
        0, 1, 2, 3, 4, 5, 6, 7
};

Bitboard _set_up_right_pin_board(uint8_t square, uint8_t blockers){
    Bitboard board = 0;
    int down_left = down_left_bits[square];
    int up_right = up_right_bits[square];

    for (int i = 0; i < up_right; i++){
        if (_c_bitboard_operations_get_bit(blockers, i)){
            _c_bitboard_operations_set_1(&board, square + 9 * (i + 1));
        }
    }

    for (int i = 0; i < down_left; i++){
        if (_c_bitboard_operations_get_bit(blockers, i + up_right)){
            _c_bitboard_operations_set_1(&board, square - 9 * (i + 1));
        }
    }


    return board;
}

uint8_t _get_number_of_up_right_pin_mask_bits(uint8_t square) {
    return down_left_bits[square] + up_right_bits[square];
}


uint16_t _get_up_right_pin_mask_hash(Bitboard board, uint64_t magic_number, uint8_t square){
    uint8_t number_of_bits = _get_number_of_up_right_pin_mask_bits(square);
    return (uint16_t)((board * magic_number) >> (64 - number_of_bits));
}

bool is_up_right_pin_magic_number_valid(uint8_t square, uint64_t magic_number){
    Bitboard board;
    uint16_t hash;
    uint16_t number_of_positions = pow(2, _get_number_of_up_right_pin_mask_bits(square));
    bool* array = calloc(number_of_positions, sizeof(bool));

    for (uint16_t blocker = 0; blocker < number_of_positions; blocker++){
        board = _set_up_right_pin_board(square, blocker);
        hash = _get_up_right_pin_mask_hash(board, magic_number, square);
        if (array[hash]){
            free(array);
            return false;
        }
        array[hash] = true;
    }

    free(array);
    return true;
}

Bitboard _generate_up_right_pin_magic_number(uint8_t square){
    Bitboard magic_number;

    for (uint8_t i = 0; i < 32; i++){
        magic_number = pow(2, i);
        if (is_up_right_pin_magic_number_valid(square, magic_number)) {
            return magic_number;
        }
    }

    do {
        magic_number = _generate_random_64bit() & _generate_random_64bit() & _generate_random_64bit();
    } while (!is_up_right_pin_magic_number_valid(square, magic_number));

    return magic_number;
}


void _fancy_print_up_right_pin_magic_numbers(){
    for (uint8_t i = 0; i < 64; i++){
        printf("%llu,\n", _generate_up_right_pin_magic_number(i));
    }
}

