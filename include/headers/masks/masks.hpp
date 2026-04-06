#pragma once

#include "headers/masks/bishop_masks.hpp"
#include "headers/masks/king_knight_masks.hpp"
#include "headers/masks/rook_masks.hpp"

namespace chess::masks {
    inline Bitboard get_rook_mask(Board& board, const uint8_t square) {
        const Bitboard mask = board.all & secondary_rook_masks[square];
        const int hash = get_rook_hash(mask, square);
        return primary_rook_masks[square][hash];
    }

    inline Bitboard get_bishop_mask(Board& board, const uint8_t square) {
        const Bitboard mask = board.all & secondary_bishop_masks[square];
        const int hash = get_bishop_hash(mask, square);
        return primary_bishop_masks[square][hash];
    }

    inline Bitboard get_knight_mask(const uint8_t square) {
        return knight_masks[square];
    }

    inline Bitboard get_king_mask(const uint8_t square) {
        return king_masks[square];
    }

}  // namespace chess::masks
