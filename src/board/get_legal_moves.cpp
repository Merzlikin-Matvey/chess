#include "headers/board.hpp"
#include "headers/constants.hpp"
#include "headers/move.hpp"
#include "headers/bitboard_operations.hpp"
#include "headers/masks/pin_masks.hpp"

#include <vector>
#include <iostream>


chess::MoveArray& chess::Board::get_legal_moves() {
    uint8_t color = white_turn ? White : Black;
    uint8_t king_position = bitboard_operations::bitScanForward(piece_bitboards[color][King]);

    Bitboard vertical_pin_mask = masks::get_vertical_pin_mask(*this, color, king_position);
    Bitboard horizontal_pin_mask = masks::get_horizontal_pin_mask(*this, color, king_position);
    Bitboard up_right_pin_mask = masks::get_up_right_pin_mask(*this, color, king_position);
    Bitboard up_left_pin_mask = masks::get_down_right_pin_mask(*this, color, king_position);

    // Vertical
    Bitboard pinned_pawns = piece_bitboards[color][Pawn] & vertical_pin_mask;



    return legal_moves;
}