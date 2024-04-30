#include "headers/masks.hpp"
#include "headers/constants.hpp"
#include "headers/bitboard_operations.hpp"

Bitboard masks::get_pawn_short_mask(chess::Board board, uint8_t side) {
    if (side == chess::White){
        return (board._piece_bitboards[chess::White][chess::Pawn] << 8) & ~board._all;
    }
    else {
        return (board._piece_bitboards[chess::Black][chess::Pawn] >> 8) & ~board._all;
    }
}

Bitboard masks::get_pawn_long_mask(chess::Board board, uint8_t side) {
    auto mask = get_pawn_short_mask(board, side);

    if (side == chess::White) {
        return ((mask & bitboard_operations::get_rows()[1]) << 8) & ~board._all;
    }
    else {
        return ((mask & bitboard_operations::get_rows()[6]) >> 8) & ~board._all;
    }
}

Bitboard masks::get_pawn_left_mask(chess::Board board, uint8_t side) {
    if (side == chess::White){
        return (board._piece_bitboards[chess::White][chess::Pawn] << 7) & bitboard_operations::get_inverse_rows()[7] & board._inversion_side_bitboard;
    }
    else {
        return (board._piece_bitboards[chess::Black][chess::Pawn] >> 9) & bitboard_operations::get_inverse_rows()[0] & board._side_bitboard;
    }
}

Bitboard masks::get_pawn_right_mask(chess::Board board, uint8_t side) {
    if (side == chess::White){
        return (board._piece_bitboards[chess::White][chess::Pawn] << 9) & bitboard_operations::get_inverse_rows()[0] & board._inversion_side_bitboard;
    }
    else {
        return (board._piece_bitboards[chess::Black][chess::Pawn] >> 7) & bitboard_operations::get_inverse_rows()[7] & board._side_bitboard;
    }
}