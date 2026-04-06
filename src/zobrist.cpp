#include "headers/zobrist.hpp"

#include <iostream>

#include "headers/bitboard_operations.hpp"
#include "headers/board.hpp"
#include "headers/constants.hpp"

chess::zobrist::ZobristHash::ZobristHash(const Board &board) {
    this->hash = 0;

    if (!board.white_turn) {
        this->hash = this->hash ^ BlackMove;
    }

    if (board.w_l_castling) {
        this->hash = this->hash ^ WhiteLongCastling;
    }

    if (board.w_s_castling) {
        this->hash = this->hash ^ WhiteShortCastling;
    }

    if (board.b_l_castling) {
        this->hash = this->hash ^ BlackLongCastling;
    }

    if (board.b_s_castling) {
        this->hash = this->hash ^ BlackShortCastling;
    }

    uint8_t side;
    for (uint8_t square = 0; square < 64; square = square + 1) {
        if (bitboard_operations::get_bit(board.side_bitboards[White], square)) {
            side = White;
        } else if (bitboard_operations::get_bit(board.side_bitboards[Black], square)) {
            side = Black;
        } else {
            continue;
        }

        for (uint8_t type = 0; type < 6; type = type + 1) {
            if (bitboard_operations::get_bit(board.piece_bitboards[side][type], square)) {
                this->hash = this->hash ^ Constants[square][side][type];
                break;
            }
        }
    }

    if (board.en_passant_square >= 0) {
        this->hash ^= EnPassantFile[board.en_passant_square % 8];
    }
}

std::ostream &chess::zobrist::operator<<(std::ostream &ostream, ZobristHash hash) {
    ostream << hash.hash;
    return ostream;
}