#include "headers/masks/pawn_masks.hpp"
#include "headers/constants.hpp"
#include "headers/bitboard_operations.hpp"

Bitboard chess::masks::get_pawn_mask(Bitboard board, uint8_t color) {
    if (color == White) {
        return (board << 8);
    }
    return (board >> 8);
}

Bitboard chess::masks::get_pawn_long_mask(Bitboard board, uint8_t color) {
    return get_pawn_mask(get_pawn_mask(board, color), color);
}

Bitboard chess::masks::get_pawn_right_mask(Bitboard board, uint8_t color) {
    
}

