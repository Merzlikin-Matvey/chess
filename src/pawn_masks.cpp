#include "headers/masks.hpp"
#include "headers/constants.hpp"
#include "headers/bitboard_operations.hpp"

#include "headers/masks.hpp"
#include "headers/constants.hpp"
#include "headers/bitboard_operations.hpp"

Bitboard masks::get_pawns_short_masks(chess::Board board, uint8_t side) {
    if (side == chess::White){
        return (board.piece_bitboards[chess::White][chess::Pawn] << 8) & ~board.all;
    }
    else {
        return (board.piece_bitboards[chess::Black][chess::Pawn] >> 8) & ~board.all;
    }
}

Bitboard masks::get_pawns_long_masks(chess::Board board, uint8_t side) {
    auto mask = get_pawns_short_masks(board, side);

    if (side == chess::White) {
        return ((mask & bitboard_operations::get_rows()[1]) << 8) & ~board.all;
    }
    else {
        return ((mask & bitboard_operations::get_rows()[6]) >> 8) & ~board.all;
    }
}

Bitboard masks::get_pawns_left_masks(chess::Board board, uint8_t side) {
    if (side == chess::White){
        return (board.piece_bitboards[chess::White][chess::Pawn] << 7) & bitboard_operations::get_inverse_rows()[7] & board.side_bitboard[chess::Black];
    }
    else {
        return (board.piece_bitboards[chess::Black][chess::Pawn] >> 9) & bitboard_operations::get_inverse_rows()[0] & board.side_bitboard[chess::White];
    }
}

Bitboard masks::get_pawns_right_masks(chess::Board board, uint8_t side) {
    if (side == chess::White){
        return (board.piece_bitboards[chess::White][chess::Pawn] << 9) & bitboard_operations::get_inverse_rows()[0] & board.side_bitboard[chess::Black];
    }
    else {
        return (board.piece_bitboards[chess::Black][chess::Pawn] >> 7) & bitboard_operations::get_inverse_rows()[7] & board.side_bitboard[chess::White];
    }
}