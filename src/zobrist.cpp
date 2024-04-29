#include "headers/zobrist.hpp"
#include "headers/bitboard_operations.hpp"
#include "headers/constants.hpp"
#include "headers/board.hpp"

#include <iostream>

zobrist::ZobristHash::ZobristHash(chess::Board board) {
    this->hash = 0;

    if (!board.white_turn){
        this->hash = this->hash ^ zobrist::BlackMove;
    }
    if (board.w_l_castling) {
        this->hash = this->hash ^ zobrist::WhiteLongCastling;
    }
    if (board.w_s_castling) {
        this->hash = this->hash ^ zobrist::WhiteShortCastling;
    }
    if (board.b_l_castling) {
        this->hash = this->hash ^ zobrist::BlackLongCastling;
    }
    if (board.b_s_castling) {
        this->hash = this->hash ^ zobrist::BlackShortCastling;
    }

    uint8_t side;
    for (uint8_t square = 0; square < 64; square = square + 1) {
        if (bitboard_operations::get_bit(board._side_bitboards[chess::White], square)) {
            side = chess::White;
        }
        else if (bitboard_operations::get_bit(board._side_bitboards[chess::Black], square)) {
            side = chess::Black;
        }
        else {
            continue;
        }

        for (uint8_t type = 0; type < 6; type = type + 1) {
            if (bitboard_operations::get_bit(board._piece_bitboards[side][type], square)) {
                this->hash = this->hash ^ zobrist::Constants[square][side][type];
                break;
            }
        }
    }
}

std::ostream& zobrist::operator<<(std::ostream &ostream, zobrist::ZobristHash hash) {
    ostream << static_cast<unsigned long long>(hash.hash);
    return ostream;
}