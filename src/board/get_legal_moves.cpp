#include "headers/board.hpp"
#include "headers/constants.hpp"
#include "headers/move.hpp"
#include "headers/bitboard_operations.hpp"
#include "headers/masks/pin_masks.hpp"
#include "headers/masks/pawn_masks.hpp"

#include <vector>
#include <iostream>


chess::MoveArray& chess::Board::get_legal_moves() {
    legal_moves.clear();
    uint8_t color = white_turn ? White : Black;
    uint8_t king_position = bitboard_operations::bitScanForward(piece_bitboards[color][King]);

    Bitboard vertical_pin_mask = masks::get_vertical_pin_mask(*this, color, king_position);
    Bitboard horizontal_pin_mask = masks::get_horizontal_pin_mask(*this, color, king_position);
    Bitboard up_right_pin_mask = masks::get_up_right_pin_mask(*this, color, king_position);
    Bitboard up_left_pin_mask = masks::get_down_right_pin_mask(*this, color, king_position);

    // Vertical
    Bitboard vertical_pinned_pawns = piece_bitboards[color][Pawn] & vertical_pin_mask;
    pawn_mask_to_moves(masks::get_pawn_mask(*this), 8, &legal_moves);

    Bitboard diagonal_pinned_pawns = piece_bitboards[color][Pawn] & (up_right_pin_mask | up_left_pin_mask);
    pawn_mask_to_moves(masks::get_pawn_right_mask(*this), 7, &legal_moves);
    pawn_mask_to_moves(masks::get_pawn_left_mask(*this), 9, &legal_moves);





    return legal_moves;
}