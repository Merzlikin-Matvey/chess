#include "headers/C functions/magic_numbers.h"
#include "headers/C functions/bitboard_operations.h"

#include <math.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

int _up_right_bits[64] = {
        6, 5, 4, 3, 2, 1, 0, 0,
        5, 5, 4, 3, 2, 1, 0, 0,
        4, 4, 4, 3, 2, 1, 0, 0,
        3, 3, 3, 3, 2, 1, 0, 0,
        2, 2, 2, 2, 2, 1, 0, 0,
        1, 1, 1, 1, 1, 1, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0
};

int _down_left_bits[64] = {
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 1, 1, 1, 1, 1, 1,
        0, 0, 1, 2, 2, 2, 2, 2,
        0, 0, 1, 2, 3, 3, 3, 3,
        0, 0, 1, 2, 3, 4, 4, 4,
        0, 0, 1, 2, 3, 4, 5, 5,
        0, 0, 1, 2, 3, 4, 5, 6
};

int _up_left_bits[64] = {
        0, 0, 1, 2, 3, 4, 5, 6,
        0, 0, 1, 2, 3, 4, 5, 5,
        0, 0, 1, 2, 3, 4, 4, 4,
        0, 0, 1, 2, 3, 3, 3, 3,
        0, 0, 1, 2, 2, 2, 2, 2,
        0, 0, 1, 1, 1, 1, 1, 1,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0
};


int _down_right_bits[64] = {
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        1, 1, 1, 1, 1, 1, 0, 0,
        2, 2, 2, 2, 2, 1, 0, 0,
        3, 3, 3, 3, 2, 1, 0, 0,
        4, 4, 4, 3, 2, 1, 0, 0,
        5, 5, 4, 3, 2, 1, 0, 0,
        6, 5, 4, 3, 2, 1, 0, 0
};



Bitboard _set_bishop_board(uint8_t square, uint16_t blockers) {
    Bitboard board = 0;
    int up_right = _up_right_bits[square];
    int down_left = _down_left_bits[square];
    int up_left = _up_left_bits[square];
    int down_right = _down_right_bits[square];

    for (int pos = 1; pos < up_right + 1; pos++){
        if (_c_bitboard_operations_get_bit(blockers, square + pos * 9)){
            _c_bitboard_operations_set_1(&board, square + pos * 9);
        }
    }

    for (int pos = 1; pos < down_left + 1; pos++){
        if (_c_bitboard_operations_get_bit(blockers, square - pos * 9)){
            _c_bitboard_operations_set_1(&board, square - pos * 9);
        }
    }

    for (int pos = 1; pos < up_left + 1; pos++){
        if (_c_bitboard_operations_get_bit(blockers, square + pos * 7)){
            _c_bitboard_operations_set_1(&board, square + pos * 7);
        }
    }

    for (int pos = 1; pos < down_right + 1; pos++){
        if (_c_bitboard_operations_get_bit(blockers, square - pos * 7)){
            _c_bitboard_operations_set_1(&board, square - pos * 7);
        }
    }

    return board;

}

uint8_t _get_number_of_bishop_bits(uint8_t square) {
    return _up_right_bits[square] + _down_left_bits[square] + _up_left_bits[square] + _down_right_bits[square];
}

uint16_t _get_bishop_hash(Bitboard board, uint64_t magic_number, uint8_t square) {
    return (board * magic_number) >> (64 - _get_number_of_bishop_bits(square));
}

bool _is_bishop_magic_number_valid(uint64_t magic_number, uint8_t square) {
    Bitboard board;
    uint16_t hash;
    uint8_t number_of_bits = _get_number_of_bishop_bits(square);
    uint16_t number_of_positions = pow(2, number_of_bits);
    bool* array = calloc(number_of_positions, sizeof(bool));

    for (uint16_t i = 0; i < pow(2, number_of_bits); i++){
        board = _set_bishop_board(square, i);
        hash = _get_bishop_hash(board, magic_number, square);
        if (array[hash]){
            return false;
        }
    }
    free(array);
    return true;
}

uint64_t _generate_bishop_magic_number(uint8_t square) {
    uint64_t magic_number;
    do {
        magic_number = _generate_random_64bit();
    } while (!_is_bishop_magic_number_valid(magic_number, square));
    return magic_number;
}

