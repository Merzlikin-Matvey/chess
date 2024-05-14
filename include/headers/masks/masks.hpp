#pragma once

#include "headers/masks/vertical_pin_masks.hpp"
#include "headers/masks/horizontal_pin_masks.hpp"
#include "headers/masks/up_right_diagonal_pin_masks.hpp"
#include "headers/masks/down_right_diagonal_pin_masks.hpp"


#include "headers/masks/rook_masks.hpp"
#include "headers/masks/bishop_masks.hpp"
#include "headers/masks/pawn_masks.hpp"
#include "headers/masks/king_knight_masks.hpp"


namespace chess::masks{
    inline Bitboard get_rook_mask(Board& board, uint8_t square) {
        Bitboard mask = board.all & secondary_rook_masks[square];
        int hash = get_rook_hash(mask, square);
        return primary_rook_masks[square][hash];
    }

    inline Bitboard get_bishop_mask(Board& board, uint8_t square) {
        Bitboard mask = board.all & secondary_bishop_masks[square];
        int hash = get_bishop_hash(mask, square);
        return primary_bishop_masks[square][hash];
    }

    inline Bitboard get_knight_mask(uint8_t square) {
        return knight_masks[square];
    }

    inline Bitboard get_king_mask( uint8_t square) {
        return king_masks[square];
    }

}

