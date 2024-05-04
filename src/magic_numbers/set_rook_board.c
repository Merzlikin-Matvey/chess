#include "headers/C functions/magic_numbers.h"
#include "headers/C functions/bitboard_operations.h"

Bitboard _set_rook_board(uint8_t square) {
    Bitboard board = 0;
    uint8_t start_index = square / 8 * 8 + 1;
    uint8_t end_index = start_index + 6;

    for (uint8_t i = start_index; i < end_index; i++) {
        if (i != square) {
            _c_bitboard_operations_set_1(&board, i);
        }
    }

    start_index = square % 8 + 8;
    end_index = 56 + square % 8 - 8;

    for (uint8_t i = start_index; i <= end_index; i += 8) {
        if (i != square) {
            _c_bitboard_operations_set_1(&board, i);
        }
    }

    return board;
}

uint8_t _get_number_of_rook_bits(uint8_t square) {
    uint8_t count = 0;
    uint8_t start_index = square / 8 * 8 + 1;
    uint8_t end_index = start_index + 6;

    for (uint8_t i = start_index; i < end_index; i++) {
        if (i != square) {
            count++;
        }
    }

    start_index = square % 8 + 8;
    end_index = 56 + square % 8 - 8;

    for (uint8_t i = start_index; i <= end_index; i += 8) {
        if (i != square) {
            count++;
        }
    }

    return count;
}

