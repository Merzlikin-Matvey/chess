#pragma once

#include <memory>
#include <array>

typedef uint64_t Bitboard;

namespace chess::masks {
    Bitboard get_pawn_mask(Bitboard board, uint8_t color);
    Bitboard get_pawn_long_mask(Bitboard board, uint8_t color);
    Bitboard get_pawn_right_mask(Bitboard board, uint8_t color);
    Bitboard get_pawn_left_mask(Bitboard board, uint8_t color);
}