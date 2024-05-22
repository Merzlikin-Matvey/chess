#include "headers/masks/pawn_masks.hpp"
#include "headers/constants.hpp"
#include "headers/bitboard_operations.hpp"
#include "headers/board.hpp"

#include <iostream>

Bitboard chess::masks::get_pawn_mask(Bitboard pawns, Board& board) {
    Bitboard empty = ~board.all;

    if (board.white_turn) {
        return (pawns << 8) & empty;
    } else {
        return (pawns >> 8) & empty;
    }
}

Bitboard chess::masks::get_pawn_long_mask(Bitboard pawns, Board& board) {
    Bitboard empty = ~board.all;

    if (board.white_turn) {
        Bitboard pawn_mask = get_pawn_mask(pawns & bitboard_operations::rows[1], board);
        return (pawn_mask << 8) & empty;
    } else {
        Bitboard pawn_mask = get_pawn_mask(pawns & bitboard_operations::rows[6], board);
        return (pawn_mask >> 8) & empty;
    }
}

Bitboard chess::masks::get_pawn_right_mask(Bitboard pawns, Board& board) {
    if (board.white_turn) {
        return (pawns << 9) & board.side_bitboards[Black] & ~bitboard_operations::columns[0];
    } else {
        return (pawns >> 7) & board.side_bitboards[White] & ~bitboard_operations::columns[0];
    }
}

Bitboard chess::masks::get_pawn_left_mask(Bitboard pawns, Board& board) {
    if (board.white_turn) {
        return (pawns << 7) & board.side_bitboards[Black] & ~bitboard_operations::columns[7];
    } else {
        return (pawns >> 9) & board.side_bitboards[White] & ~bitboard_operations::columns[7];
    }
}

Bitboard chess::masks::get_left_en_passant_mask(Bitboard pawns, Board& board) {
    Bitboard en_passant_mask = 0;
    if (board.white_turn) {
        pawns = pawns & bitboard_operations::rows[4];
        en_passant_mask = (pawns << 7) & ((board.piece_bitboards[Black][Pawn] & bitboard_operations::rows[4]) << 8);
    } else {
        pawns = pawns & bitboard_operations::rows[3];
        en_passant_mask = (pawns >> 9) & ((board.piece_bitboards[White][Pawn] & bitboard_operations::rows[3]) >> 8);
    }

    return en_passant_mask;
}

Bitboard chess::masks::get_right_en_passant_mask(Bitboard pawns, Board& board) {
    Bitboard en_passant_mask = 0;
    if (board.white_turn) {
        pawns = pawns & bitboard_operations::rows[4];
        en_passant_mask = (pawns << 9) & ((board.piece_bitboards[Black][Pawn] & bitboard_operations::rows[4]) << 8);
    } else {
        pawns = pawns & bitboard_operations::rows[3];
        en_passant_mask = (pawns >> 7) & ((board.piece_bitboards[White][Pawn] & bitboard_operations::rows[3]) >> 8);
    }

    return en_passant_mask;
}


