#include "headers/masks/pawn_masks.hpp"
#include "headers/constants.hpp"
#include "headers/bitboard_operations.hpp"
#include "headers/board.hpp"

Bitboard chess::masks::get_pawn_mask(Bitboard pawns, Board& board) {
    Bitboard empty = ~board.all;

    if (board.white_turn) {
        return (pawns << 8) & empty;
    } else {
        return (pawns >> 8) & empty;
    }
}

Bitboard chess::masks::get_pawn_long_mask(Bitboard pawns, Board& board) {
    Bitboard pawn_mask = get_pawn_mask(pawns, board);
    Bitboard empty = ~board.all;

    if (board.white_turn) {
        return (pawn_mask << 8) & empty;
    } else {
        return (pawn_mask >> 8) & empty;
    }
}

Bitboard chess::masks::get_pawn_right_mask(Bitboard pawns, Board& board) {
    if (board.white_turn) {
        return (pawns << 9) & board.side_bitboards[Black] & ~bitboard_operations::columns[0];
    } else {
        return (pawns >> 7) & board.side_bitboards[Black] & ~bitboard_operations::columns[0];
    }
}

Bitboard chess::masks::get_pawn_left_mask(Bitboard pawns, Board& board) {
    if (board.white_turn) {
        return (pawns << 7) & board.side_bitboards[Black] & ~bitboard_operations::columns[7];
    } else {
        return (pawns >> 9) & board.side_bitboards[Black] & ~bitboard_operations::columns[7];
    }
}


