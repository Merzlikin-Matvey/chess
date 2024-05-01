#ifndef CHESS_ENGINE_BITBOARD_OPERATIONS_H
#define CHESS_ENGINE_BITBOARD_OPERATIONS_H

#include <stdint.h>

typedef uint64_t Bitboard;

static inline void _c_bitboard_operations_set_1(Bitboard *bb, uint8_t square) {
    *bb = *bb | (1ull << square);
}

#endif
