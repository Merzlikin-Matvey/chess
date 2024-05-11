#include "headers/board.hpp"
#include "headers/masks/pawn_masks.hpp"
#include "headers/masks/rook_masks.hpp"
#include "headers/masks/bishop_masks.hpp"
#include "headers/masks/pawn_masks.hpp"
#include "headers/masks/king_knight_masks.hpp"
#include "headers/constants.hpp"


bool chess::Board::is_position_attacked(uint8_t x) {
    uint8_t color = white_turn ? White : Black;
    Bitboard rook_mask = masks::get_rook_mask(*this, x);
    Bitboard bishop_mask = masks::get_bishop_mask(*this, x);
    Bitboard king_mask = masks::get_king_mask(x);
    Bitboard knight_mask = masks::get_knight_mask(x);

    if (rook_mask & (piece_bitboards[!color][Rook] | piece_bitboards[!color][Queen])) {
        return true;
    }

    if (bishop_mask & (piece_bitboards[!color][Bishop] | piece_bitboards[!color][Queen])) {
        return true;
    }

    if (king_mask & piece_bitboards[!color][King]) {
        return true;
    }

    if (knight_mask & piece_bitboards[!color][Knight]) {
        return true;
    }

    if (color == White){
        if (x + 9 < 64){
            if (bitboard_operations::get_bit(side_bitboards[!color], x + 9)) {
                return true;
            }
        }
        if (x + 7 < 64){
            if (bitboard_operations::get_bit(side_bitboards[!color], x + 7)) {
                return true;
            }
        }
    }
    else {
        if (x >= 9){
            if (bitboard_operations::get_bit(side_bitboards[!color], x - 9)) {
                return true;
            }
        }

        if (x >= 7){
            if (bitboard_operations::get_bit(side_bitboards[!color], x - 7)) {
                return true;
            }
        }
    }

    return false;
}

bool chess::Board::is_check() {
    uint8_t color = white_turn ? White : Black;
    uint8_t king_index = bitboard_operations::bitScanForward(piece_bitboards[color][King]);
    return is_position_attacked(king_index);
}

bool chess::Board::is_double_check() {
    uint16_t count = 0;
    uint8_t king_index = bitboard_operations::bitScanForward(piece_bitboards[white_turn ? White : Black][King]);
    uint8_t color = white_turn ? White : Black;
    Bitboard rook_mask = masks::get_rook_mask(*this, king_index);
    Bitboard bishop_mask = masks::get_bishop_mask(*this, king_index);
    Bitboard king_mask = masks::get_king_mask(king_index);
    Bitboard knight_mask = masks::get_knight_mask(king_index);

    count += bitboard_operations::count_1(rook_mask & (piece_bitboards[!color][Rook] | piece_bitboards[!color][Queen]));
    count += bitboard_operations::count_1(bishop_mask & (piece_bitboards[!color][Bishop] | piece_bitboards[!color][Queen]));
    count += bitboard_operations::count_1(king_mask & piece_bitboards[!color][King]);
    count += bitboard_operations::count_1(knight_mask & piece_bitboards[!color][Knight]);

    if (color == White){
        if (king_index + 9 < 64){
            if (bitboard_operations::get_bit(side_bitboards[!color], king_index + 9)) {
                count++;
            }
        }
        if (king_index + 7 < 64){
            if (bitboard_operations::get_bit(side_bitboards[!color], king_index + 7)) {
                count++;
            }
        }
    }
    else {
        if (king_index >= 9){
            if (bitboard_operations::get_bit(side_bitboards[!color], king_index - 9)) {
                count++;
            }
        }

        if (king_index >= 7){
            if (bitboard_operations::get_bit(side_bitboards[!color], king_index - 7)) {
                count++;
            }
        }
    }

    return count >= 2;
}

bool chess::Board::is_checkmate() {
    MoveArray& moves = get_legal_moves();
    return moves.size == 0;
}