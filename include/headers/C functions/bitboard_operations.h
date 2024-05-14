#ifndef CHESS_LIB_BITBOARD_OPERATIONS_H
#define CHESS_LIB_BITBOARD_OPERATIONS_H

#include <stdint.h>
#include <stdio.h>

typedef uint64_t Bitboard;

static inline void _c_bitboard_operations_set_1(Bitboard *bb, uint8_t square) {
    *bb = *bb | (1ull << square);
}

static inline int _c_bitboard_operations_get_bit(Bitboard board, int i) {
    return (board >> i) & 1;
}

static inline void _c_print_bitboard(Bitboard bitboard) {
    for (int8_t y = 7; y >= 0; y = y - 1) {
        for (uint8_t x = 0; x < 8; x = x + 1) {
            if (_c_bitboard_operations_get_bit(bitboard, y * 8 + x)) {
                printf("1");
            }
            else {
                printf("0");
            }
        }
        printf("\n");
    }
}

#endif
