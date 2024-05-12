#include "headers/board.hpp"
#include "headers/constants.hpp"
#include "headers/move.hpp"
#include "headers/bitboard_operations.hpp"
#include "headers/masks/masks.hpp"

#include <vector>
#include <iostream>


chess::MoveArray& chess::Board::get_legal_moves() {
    legal_moves.clear();
    uint8_t color = white_turn ? White : Black;
    uint8_t king_position = bitboard_operations::bitScanForward(piece_bitboards[color][King]);

    Bitboard vertical_pin_mask = masks::get_vertical_pin_mask(*this, king_position, color);
    Bitboard horizontal_pin_mask = masks::get_horizontal_pin_mask(*this, king_position, color);
    Bitboard up_right_pin_mask = masks::get_up_right_pin_mask(*this, king_position, color);
    Bitboard up_left_pin_mask = masks::get_down_right_pin_mask(*this, king_position, color);

    uint8_t square;

    // Pawns
    Bitboard pinned_pawns = piece_bitboards[color][Pawn] & vertical_pin_mask;
    pawn_mask_to_moves(masks::get_pawn_mask(pinned_pawns, *this), 8, &legal_moves);


    // Rooks
    Bitboard pinned_rooks = piece_bitboards[color][Rook] & (horizontal_pin_mask | vertical_pin_mask);
    while (pinned_rooks) {
        square = bitboard_operations::bitScanForward(pinned_rooks);
        bitboard_operations::set_0(pinned_rooks, square);
        mask_to_moves(masks::get_rook_mask(*this, square) & (horizontal_pin_mask | vertical_pin_mask),
                      square, color, Rook,
                      &legal_moves);
    }

    // Bishops
    Bitboard pinned_bishops = piece_bitboards[color][Bishop] & (up_right_pin_mask | up_left_pin_mask);
    while (pinned_bishops) {
        square = bitboard_operations::bitScanForward(pinned_bishops);
        bitboard_operations::set_0(pinned_bishops, square);
        mask_to_moves(masks::get_bishop_mask(*this, square) & (up_right_pin_mask | up_left_pin_mask),
                      square, color, Bishop,
                      &legal_moves);
    }

    // Queens
    Bitboard vertical_and_horizontal_pinned_queens = piece_bitboards[color][Queen] & (horizontal_pin_mask | vertical_pin_mask);
    Bitboard diagonal_pinned_queens = piece_bitboards[color][Queen] & (up_right_pin_mask | up_left_pin_mask);

    while (vertical_and_horizontal_pinned_queens) {
        square = bitboard_operations::bitScanForward(vertical_and_horizontal_pinned_queens);
        bitboard_operations::set_0(vertical_and_horizontal_pinned_queens, square);
        mask_to_moves(masks::get_rook_mask(*this, square) & (horizontal_pin_mask | vertical_pin_mask),
                      square, color, Queen,
                      &legal_moves);
    }

    while (diagonal_pinned_queens) {
        square = bitboard_operations::bitScanForward(diagonal_pinned_queens);
        bitboard_operations::set_0(diagonal_pinned_queens, square);
        mask_to_moves(masks::get_bishop_mask(*this, square) & (up_right_pin_mask | up_left_pin_mask),
                      square, color, Queen,
                      &legal_moves);
    }









    return legal_moves;
}