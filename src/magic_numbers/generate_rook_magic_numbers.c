#include "headers/C functions/magic_numbers.h"
#include "headers/C functions/bitboard_operations.h"

#include <math.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>


const int _up_bits[64] = {
        6, 6, 6, 6, 6, 6, 6, 6,
        5, 5, 5, 5, 5, 5, 5, 5,
        4, 4, 4, 4, 4, 4, 4, 4,
        3, 3, 3, 3, 3, 3, 3, 3,
        2, 2, 2, 2, 2, 2, 2, 2,
        1, 1, 1, 1, 1, 1, 1, 1,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0
};

const int _down_bits[64] = {
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        1, 1, 1, 1, 1, 1, 1, 1,
        2, 2, 2, 2, 2, 2, 2, 2,
        3, 3, 3, 3, 3, 3, 3, 3,
        4, 4, 4, 4, 4, 4, 4, 4,
        5, 5, 5, 5, 5, 5, 5, 5,
        6, 6, 6, 6, 6, 6, 6, 6
};

const int _right_bits[64] = {
        6, 5, 4, 3, 2, 1, 0, 0,
        6, 5, 4, 3, 2, 1, 0, 0,
        6, 5, 4, 3, 2, 1, 0, 0,
        6, 5, 4, 3, 2, 1, 0, 0,
        6, 5, 4, 3, 2, 1, 0, 0,
        6, 5, 4, 3, 2, 1, 0, 0,
        6, 5, 4, 3, 2, 1, 0, 0,
        6, 5, 4, 3, 2, 1, 0, 0
};

const int _left_bits[64] = {
        0, 0, 1, 2, 3, 4, 5, 6,
        0, 0, 1, 2, 3, 4, 5, 6,
        0, 0, 1, 2, 3, 4, 5, 6,
        0, 0, 1, 2, 3, 4, 5, 6,
        0, 0, 1, 2, 3, 4, 5, 6,
        0, 0, 1, 2, 3, 4, 5, 6,
        0, 0, 1, 2, 3, 4, 5, 6,
        0, 0, 1, 2, 3, 4, 5, 6
};

Bitboard _set_rook_board(uint8_t square, uint16_t blockers) {
    Bitboard board = 0;
    int up = _up_bits[square];
    int down = _down_bits[square];
    int right = _right_bits[square];
    int left = _left_bits[square];

    for (int i = 0; i < up; i++) {
        if (_c_bitboard_operations_get_bit(blockers, i)){
            _c_bitboard_operations_set_1(&board, square + (i + 1) * 8);
        }
    }

    for (int i = 0; i < down; i++) {
        if (_c_bitboard_operations_get_bit(blockers, i + up)){
            _c_bitboard_operations_set_1(&board, square - (i + 1) * 8);
        }
    }

    for (int i = 0; i < right; i++) {
        if (_c_bitboard_operations_get_bit(blockers, i + up + down)){
            _c_bitboard_operations_set_1(&board, square + i + 1);
        }
    }

    for (int i = 0; i < left; i++) {
        if (_c_bitboard_operations_get_bit(blockers, i + up + down + right)){
            _c_bitboard_operations_set_1(&board, square - i - 1);
        }
    }

    return board;
}

uint8_t _get_number_of_rook_bits(uint8_t square) {
    return _up_bits[square] + _down_bits[square] + _right_bits[square] + _left_bits[square];
}

uint16_t _get_rook_hash(Bitboard board, uint64_t magic_number, uint8_t square) {
    return (board * magic_number) >> (64 - _get_number_of_rook_bits(square));
}

bool _is_rook_magic_number_valid(uint64_t magic_number, uint8_t square) {
    Bitboard board;
    uint16_t hash;
    uint8_t number_of_bits = _get_number_of_rook_bits(square);
    uint16_t number_of_positions = pow(2, number_of_bits);
    bool* array = calloc(number_of_positions, sizeof(bool));

    for (uint16_t i = 0; i < pow(2, number_of_bits); i++){
        board = _set_rook_board(square, i);
        hash = _get_rook_hash(board, magic_number, square);
        if (array[hash]){
            return false;
        }
        array[hash] = true;
    }
    free(array);
    return true;
}

uint64_t _generate_rook_magic_number(uint8_t square) {
    uint64_t magic_number;
    do {
        magic_number = _generate_random_64bit() & _generate_random_64bit() & _generate_random_64bit();
    } while (!_is_rook_magic_number_valid(magic_number, square));
    return magic_number;
}
