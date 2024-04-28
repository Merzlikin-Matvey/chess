#include "headers/zobrist.hpp"
#include "headers/bitboard_operations.hpp"
#include "headers/constants.hpp"

#include <iostream>

zobrist::ZobristHash::ZobristHash(chess::Board board,
                                    bool black_move,
                                    bool w_l_castling,
                                    bool w_s_castling,
                                    bool b_l_castling,
                                    bool b_s_castling) {
    this->hash = 0;

    if (black_move) {
        this->hash = this->hash ^ zobrist::BlackMove;
    }
    if (w_l_castling) {
        this->hash = this->hash ^ zobrist::WhiteLongCastling;
    }
    if (w_s_castling) {
        this->hash = this->hash ^ zobrist::WhiteShortCastling;
    }
    if (b_l_castling) {
        this->hash = this->hash ^ zobrist::BlackLongCastling;
    }
    if (b_s_castling) {
        this->hash = this->hash ^ zobrist::BlackShortCastling;
    }

    uint8_t side;
    for (uint8_t square = 0; square < 64; square = square + 1) {
        if (bitboard_operations::get_bit(board._side_bitboards[chess::White], square)) side = chess::White;
        else if (bitboard_operations::get_bit(board._side_bitboards[chess::Black], square)) side = chess::Black;
        else continue;

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