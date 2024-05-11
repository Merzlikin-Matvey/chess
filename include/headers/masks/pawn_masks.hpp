#pragma once

#include "headers/board.hpp"

#include <memory>
#include <array>


typedef uint64_t Bitboard;

namespace chess::masks {
    Bitboard get_pawn_mask(Board& board);
    Bitboard get_pawn_long_mask(Board& board);
    Bitboard get_pawn_right_mask(Board& board);
    Bitboard get_pawn_left_mask(Board& board);
}