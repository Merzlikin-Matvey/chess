#pragma once

#include "headers/board.hpp"

#include <memory>
#include <array>


typedef uint64_t Bitboard;

namespace chess::masks {
    Bitboard get_pawn_mask(Bitboard pawns, Board& board);
    Bitboard get_pawn_long_mask(Bitboard pawns, Board& board);
    Bitboard get_pawn_right_mask(Bitboard pawns, Board& board);
    Bitboard get_pawn_left_mask(Bitboard pawns, Board& board);
    Bitboard get_left_en_passant_mask(Bitboard pawns, Board& board);
    Bitboard get_right_en_passant_mask(Bitboard pawns, Board& board);
}