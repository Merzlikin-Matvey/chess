#include "headers/board.hpp"
#include "headers/constants.hpp"
#include "headers/move.hpp"
#include "headers/masks/masks.hpp"
#include "headers/check_and_checkmate.hpp"


void chess::Board::castling(chess::MoveArray *moves) {
    uint8_t color = white_turn ? White : Black;

    if (color == White and !white_castling){
        return;
    }
    if (color == Black and !black_castling){
        return;
    }

    if (color == White){
        // Long
        if (bitboard_operations::get_bit(piece_bitboards[White][Rook], 0) and
            !bitboard_operations::get_bit(all, 1) and
            !bitboard_operations::get_bit(all, 2) and
            !bitboard_operations::get_bit(all, 3) and
            bitboard_operations::get_bit(piece_bitboards[White][King], 4)
        ) {
            if (!is_position_attacked(2)){
                moves->push_back(Move(
                        4, White, King,
                        2, 255, 255,
                        true, false, false, false,
                        false, false, 255
                        ));
            }
        }

        // Short
        if (bitboard_operations::get_bit(piece_bitboards[White][Rook], 7) and
            !bitboard_operations::get_bit(all, 5) and
            !bitboard_operations::get_bit(all, 6) and
            bitboard_operations::get_bit(piece_bitboards[White][King], 4)
        ) {
            if (!is_position_attacked(6)){
                moves->push_back(Move(
                        4, White, King,
                        6, 255, 255,
                        false, true, false, false,
                        false, false, 255
                        ));
            }
        }
    }
    else {
        // Long
        if (bitboard_operations::get_bit(piece_bitboards[Black][Rook], 56) and
            !bitboard_operations::get_bit(all, 57) and
            !bitboard_operations::get_bit(all, 58) and
            !bitboard_operations::get_bit(all, 59) and
            bitboard_operations::get_bit(piece_bitboards[Black][King], 60)
        ) {
            if (!is_position_attacked(58)){
                moves->push_back(Move(
                        60, Black, King,
                        58, 255, 255,
                        false, false, true, false,
                        false, false, 255
                        ));
            }
        }

        // Short
        if (bitboard_operations::get_bit(piece_bitboards[Black][Rook], 63) and
            !bitboard_operations::get_bit(all, 61) and
            !bitboard_operations::get_bit(all, 62) and
            bitboard_operations::get_bit(piece_bitboards[Black][King], 60)
        ) {
            if (!is_position_attacked(62)){
                moves->push_back(Move(
                        60, Black, King,
                        62, 255, 255,
                        false, false, false, true,
                        false, false, 255
                        ));
            }
        }
    }

}


Bitboard chess::Board::get_king_legal_moves_mask() {
    uint8_t color = white_turn ? White : Black;
    uint8_t king_position = bitboard_operations::bitScanForward(piece_bitboards[color][King]);
    Bitboard primary_mask = masks::king_masks[king_position];
    Bitboard mask = 0;
    uint8_t bit;

    bitboard_operations::set_0(piece_bitboards[color][King], king_position);
    bitboard_operations::set_0(side_bitboards[color], king_position);
    bitboard_operations::set_0(all, king_position);
    while (primary_mask) {
        bit = bitboard_operations::bitScanForward(primary_mask);
        bitboard_operations::set_0(primary_mask, bit);

        bitboard_operations::set_1(piece_bitboards[color][King], bit);
        if (!is_check()) {
            bitboard_operations::set_1(mask, bit);
        }
        bitboard_operations::set_0(piece_bitboards[color][King], bit);
    }

    bitboard_operations::set_1(piece_bitboards[color][King], king_position);
    bitboard_operations::set_1(side_bitboards[color], king_position);
    bitboard_operations::set_1(all, king_position);
    return mask;
}



chess::MoveArray& chess::Board::get_legal_moves() {
    legal_moves.clear();
    uint8_t color = white_turn ? White : Black;
    uint8_t king_position = bitboard_operations::bitScanForward(piece_bitboards[color][King]);

    if (is_double_check()){
        mask_to_moves(get_king_legal_moves_mask(), king_position, color,King, &legal_moves);
        return legal_moves;
    }

    Bitboard vertical_pin_mask = masks::get_vertical_pin_mask(*this, king_position, color);
    Bitboard horizontal_pin_mask = masks::get_horizontal_pin_mask(*this, king_position, color);
    Bitboard up_right_pin_mask = masks::get_up_right_pin_mask(*this, king_position, color);
    Bitboard up_left_pin_mask = masks::get_down_right_pin_mask(*this, king_position, color);
    Bitboard pin_mask = vertical_pin_mask | horizontal_pin_mask | up_right_pin_mask | up_left_pin_mask;
    Bitboard inverse_pin_mask = ~pin_mask;

    uint8_t square;

    if (is_check()){
        Bitboard check_mask = get_check_mask();

        // Pinned pawns
        Bitboard vertical_pinned_pawns = piece_bitboards[color][Pawn] & vertical_pin_mask;
        Bitboard up_right_pinned_pawns = piece_bitboards[color][Pawn] & up_right_pin_mask;
        Bitboard up_left_pinned_pawns = piece_bitboards[color][Pawn] & up_left_pin_mask;
        pawn_mask_to_moves(masks::get_pawn_mask(vertical_pinned_pawns, *this) & check_mask, 8, &legal_moves, false);
        pawn_mask_to_moves(masks::get_pawn_long_mask(vertical_pinned_pawns, *this) & check_mask, 16, &legal_moves, false);
        if (color == White){
            pawn_mask_to_moves(masks::get_pawn_right_mask(up_right_pinned_pawns, *this) & check_mask, 9, &legal_moves, false);
            pawn_mask_to_moves(masks::get_pawn_left_mask(up_left_pinned_pawns, *this) & check_mask, 7, &legal_moves, false);
        }
        else {
            pawn_mask_to_moves(masks::get_pawn_right_mask(up_right_pinned_pawns, *this) & check_mask, 7, &legal_moves, false);
            pawn_mask_to_moves(masks::get_pawn_left_mask(up_left_pinned_pawns, *this) & check_mask, 9, &legal_moves, false);
        }

        // Pinned rooks
        Bitboard pinned_rooks = piece_bitboards[color][Rook] & (horizontal_pin_mask | vertical_pin_mask);
        while (pinned_rooks) {
            square = bitboard_operations::bitScanForward(pinned_rooks);
            bitboard_operations::set_0(pinned_rooks, square);
            mask_to_moves(masks::get_rook_mask(*this, square) & (horizontal_pin_mask | vertical_pin_mask) & check_mask,
                          square, color, Rook,
                          &legal_moves);
        }

        // Pinned bishops
        Bitboard pinned_bishops = piece_bitboards[color][Bishop] & (up_right_pin_mask | up_left_pin_mask);
        while (pinned_bishops) {
            square = bitboard_operations::bitScanForward(pinned_bishops);
            bitboard_operations::set_0(pinned_bishops, square);
            mask_to_moves(masks::get_bishop_mask(*this, square) & (up_right_pin_mask | up_left_pin_mask) & check_mask,
                          square, color, Bishop,
                          &legal_moves);
        }

        // Pinned queens
        Bitboard vertical_and_horizontal_pinned_queens = piece_bitboards[color][Queen] & (horizontal_pin_mask | vertical_pin_mask);
        Bitboard diagonal_pinned_queens = piece_bitboards[color][Queen] & (up_right_pin_mask | up_left_pin_mask);

        while (vertical_and_horizontal_pinned_queens) {
            square = bitboard_operations::bitScanForward(vertical_and_horizontal_pinned_queens);
            bitboard_operations::set_0(vertical_and_horizontal_pinned_queens, square);
            mask_to_moves(masks::get_rook_mask(*this, square) & (horizontal_pin_mask | vertical_pin_mask) & check_mask,
                          square, color, Queen,
                          &legal_moves);
        }

        while (diagonal_pinned_queens) {
            square = bitboard_operations::bitScanForward(diagonal_pinned_queens);
            bitboard_operations::set_0(diagonal_pinned_queens, square);
            mask_to_moves(masks::get_bishop_mask(*this, square) & (up_right_pin_mask | up_left_pin_mask) & check_mask,
                          square, color, Queen,
                          &legal_moves);
        }

        // Pawns
        Bitboard pawns = piece_bitboards[color][Pawn] & inverse_pin_mask;
        pawn_mask_to_moves(masks::get_pawn_mask(pawns, *this) & check_mask, 8, &legal_moves, false);
        pawn_mask_to_moves(masks::get_pawn_long_mask(pawns, *this) & check_mask, 16, &legal_moves, false);
        if (color == White){
            pawn_mask_to_moves(masks::get_pawn_right_mask(pawns, *this) & check_mask, 9, &legal_moves, false);
            pawn_mask_to_moves(masks::get_pawn_left_mask(pawns, *this) & check_mask, 7, &legal_moves, false);
        }
        else {
            pawn_mask_to_moves(masks::get_pawn_right_mask(pawns, *this) & check_mask, 7, &legal_moves, false);
            pawn_mask_to_moves(masks::get_pawn_left_mask(pawns, *this) & check_mask, 9, &legal_moves, false);
        }

        // Rooks
        Bitboard rooks = piece_bitboards[color][Rook] & inverse_pin_mask;
        while (rooks) {
            square = bitboard_operations::bitScanForward(rooks);
            bitboard_operations::set_0(rooks, square);
            mask_to_moves(masks::get_rook_mask(*this, square) & check_mask,
                          square, color, Rook,
                          &legal_moves);
        }

        // Bishops
        Bitboard bishops = piece_bitboards[color][Bishop] & inverse_pin_mask;
        while (bishops) {
            square = bitboard_operations::bitScanForward(bishops);
            bitboard_operations::set_0(bishops, square);
            mask_to_moves(masks::get_bishop_mask(*this, square) & check_mask,
                          square, color, Bishop,
                          &legal_moves);
        }

        // Queens
        Bitboard queens = piece_bitboards[color][Queen] & inverse_pin_mask;
        while (queens) {
            square = bitboard_operations::bitScanForward(queens);
            bitboard_operations::set_0(queens, square);
            mask_to_moves(masks::get_bishop_mask(*this, square) & check_mask,
                          square, color, Queen,
                          &legal_moves);
            mask_to_moves(masks::get_rook_mask(*this, square) & check_mask,
                            square, color, Queen,
                            &legal_moves);
        }

        // Knights
        Bitboard knights = piece_bitboards[color][Knight] & inverse_pin_mask;
        while (knights) {
            square = bitboard_operations::bitScanForward(knights);
            bitboard_operations::set_0(knights, square);
            mask_to_moves(masks::get_knight_mask(square) & check_mask,
                          square, color, Knight,
                          &legal_moves);
        }

        // King
        mask_to_moves(get_king_legal_moves_mask(), king_position, color,King, &legal_moves);

        // Castling
        castling(&legal_moves);

        return legal_moves;

    }

    // Pinned pawns
    Bitboard vertical_pinned_pawns = piece_bitboards[color][Pawn] & vertical_pin_mask;
    Bitboard up_right_pinned_pawns = piece_bitboards[color][Pawn] & up_right_pin_mask;
    Bitboard up_left_pinned_pawns = piece_bitboards[color][Pawn] & up_left_pin_mask;
    pawn_mask_to_moves(masks::get_pawn_mask(vertical_pinned_pawns, *this), 8, &legal_moves, false);
    pawn_mask_to_moves(masks::get_pawn_long_mask(vertical_pinned_pawns, *this), 16, &legal_moves, false);
    if (color == White){
        pawn_mask_to_moves(masks::get_pawn_right_mask(up_right_pinned_pawns, *this), 9, &legal_moves, false);
        pawn_mask_to_moves(masks::get_pawn_left_mask(up_left_pinned_pawns, *this), 7, &legal_moves, false);
    }
    else {
        pawn_mask_to_moves(masks::get_pawn_right_mask(up_left_pinned_pawns, *this), 7, &legal_moves, false);
        pawn_mask_to_moves(masks::get_pawn_left_mask(up_right_pinned_pawns, *this), 9, &legal_moves, false);
    }

    // Pinned rooks
    Bitboard pinned_rooks = piece_bitboards[color][Rook] & (horizontal_pin_mask | vertical_pin_mask);
    while (pinned_rooks) {
        square = bitboard_operations::bitScanForward(pinned_rooks);
        bitboard_operations::set_0(pinned_rooks, square);
        mask_to_moves(masks::get_rook_mask(*this, square) & (horizontal_pin_mask | vertical_pin_mask),
                      square, color, Rook,
                      &legal_moves);
    }

    // Pinned queens
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

    // Pawns
    Bitboard pawns = piece_bitboards[color][Pawn] & inverse_pin_mask;
    pawn_mask_to_moves(masks::get_pawn_mask(pawns, *this), 8, &legal_moves, false);
    pawn_mask_to_moves(masks::get_pawn_long_mask(pawns, *this), 16, &legal_moves, false);
    if (color == White){
        pawn_mask_to_moves(masks::get_pawn_right_mask(pawns, *this), 9, &legal_moves, false);
        pawn_mask_to_moves(masks::get_pawn_left_mask(pawns, *this), 7, &legal_moves, false);
    }
    else {
        pawn_mask_to_moves(masks::get_pawn_right_mask(pawns, *this), 7, &legal_moves, false);
        pawn_mask_to_moves(masks::get_pawn_left_mask(pawns, *this), 9, &legal_moves, false);
    }


    // Rooks
    Bitboard rooks = piece_bitboards[color][Rook] & inverse_pin_mask;
    while (rooks) {
        square = bitboard_operations::bitScanForward(rooks);
        bitboard_operations::set_0(rooks, square);
        mask_to_moves(masks::get_rook_mask(*this, square),
                      square, color, Rook,
                      &legal_moves);
    }

    // Bishops
    Bitboard bishops = piece_bitboards[color][Bishop] & inverse_pin_mask;
    while (bishops) {
        square = bitboard_operations::bitScanForward(bishops);
        bitboard_operations::set_0(bishops, square);
        mask_to_moves(masks::get_bishop_mask(*this, square),
                      square, color, Bishop,
                      &legal_moves);
    }

    // Queens
    Bitboard queens = piece_bitboards[color][Queen] & inverse_pin_mask;
    while (queens) {
        square = bitboard_operations::bitScanForward(queens);
        bitboard_operations::set_0(queens, square);
        mask_to_moves(masks::get_bishop_mask(*this, square),
                      square, color, Queen,
                      &legal_moves);
        mask_to_moves(masks::get_rook_mask(*this, square),
                      square, color, Queen,
                      &legal_moves);
    }

    // Knights
    Bitboard knights = piece_bitboards[color][Knight] & inverse_pin_mask;
    while (knights) {
        square = bitboard_operations::bitScanForward(knights);
        bitboard_operations::set_0(knights, square);
        mask_to_moves(masks::get_knight_mask(square),
                      square, color, Knight,
                      &legal_moves);
    }

    // King
    mask_to_moves(get_king_legal_moves_mask(), king_position, color,King, &legal_moves);


    // Castling
    castling(&legal_moves);



    return legal_moves;
}