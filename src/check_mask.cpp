#include "headers/board.hpp"
#include "headers/masks.hpp"
#include "headers/bitboard_operations.hpp"
#include "headers/constants.hpp"
#include "headers/board.hpp"
#include "headers/bitboard_lines.hpp"

#include <iostream>

Bitboard masks::get_check_mask(chess::Board board, uint8_t side) {
    Bitboard mask = 0;

    Bitboard pawns = board.piece_bitboards[!side][chess::Pawn];
    Bitboard rooks = board.piece_bitboards[!side][chess::Rook];
    Bitboard knights = board.piece_bitboards[!side][chess::Knight];
    Bitboard bishops = board.piece_bitboards[!side][chess::Bishop];
    Bitboard queens = board.piece_bitboards[!side][chess::Queen];

    Bitboard king = board.piece_bitboards[side][chess::King];
    uint8_t king_index = bitboard_operations::bitScanForward(king);




    if (get_pawns_left_masks(board, !side) & king) {
        if (side == chess::White){
            bitboard_operations::set_1(mask, king_index + 9);
        }
        else {
            bitboard_operations::set_1(mask, king_index - 7);
        }
    }

    if (get_pawns_right_masks(board, !side) & king) {
        if (side == chess::White){
            bitboard_operations::set_1(mask, king_index + 7);
        }
        else {
            bitboard_operations::set_1(mask, king_index - 9);
        }
    }

    uint8_t index;

    while (knights){
        index = bitboard_operations::bitScanForward(knights);
        bitboard_operations::set_0(knights, index);
        if (get_knight_masks()[index] & king){
            mask |= masks::get_lines()[index][king_index];
        }
    }

    while (rooks){
        index = bitboard_operations::bitScanForward(rooks);
        bitboard_operations::set_0(rooks, index);
        if (get_rook_masks()[index] & king){
            mask |= masks::get_lines()[index][king_index];
        }
    }

    while (bishops){
        index = bitboard_operations::bitScanForward(bishops);
        bitboard_operations::set_0(bishops, index);
        if (get_bishop_masks()[index] & king){
            mask |= masks::get_lines()[index][king_index];
        }
    }

    while (queens){
        index = bitboard_operations::bitScanForward(queens);
        bitboard_operations::set_0(queens, index);
        if (get_queen_masks()[index] & king){
            mask |= masks::get_lines()[index][king_index];
        }
    }


    return mask;


}
