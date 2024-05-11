#include "headers/masks/pawn_masks.hpp"
#include "headers/constants.hpp"
#include "headers/bitboard_operations.hpp"
#include "headers/board.hpp"

Bitboard chess::masks::get_pawn_mask(Board& board) {
    Bitboard empty = ~board.all;

    if (board.white_turn) {
        Bitboard pawns = board.piece_bitboards[White][Pawn];
        return (pawns >> 8) & empty;
    } else {
        Bitboard pawns = board.piece_bitboards[Black][Pawn];
        return (pawns << 8) & empty;
    }
}

Bitboard chess::masks::get_pawn_long_mask(Board& board) {
    Bitboard pawn_mask =  get_pawn_mask(board);
    Bitboard empty = ~board.all;

    if (board.white_turn) {
        return (pawn_mask >> 8) & empty;
    } else {
        return (pawn_mask << 8) & empty;
    }
}

Bitboard chess::masks::get_pawn_right_mask(Board& board) {
    if (board.white_turn) {
        Bitboard pawns = board.piece_bitboards[White][Pawn];
        return (pawns >> 9) & board.side_bitboards[Black] & ~bitboard_operations::columns[0];
    } else {
        Bitboard pawns = board.piece_bitboards[Black][Pawn];
        Bitboard empty = ~board.all;
        return (pawns << 7) & board.side_bitboards[Black] & ~bitboard_operations::columns[0];
    }
}

Bitboard chess::masks::get_pawn_left_mask(Board& board) {
    if (board.white_turn) {
        Bitboard pawns = board.piece_bitboards[White][Pawn];
        return (pawns >> 7) & board.side_bitboards[Black] & ~bitboard_operations::columns[7];
    } else {
        Bitboard pawns = board.piece_bitboards[Black][Pawn];
        return (pawns << 9) & board.side_bitboards[Black] & ~bitboard_operations::columns[7];
    }
}


