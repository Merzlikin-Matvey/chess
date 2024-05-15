#include "headers/board.hpp"
#include "headers/bitboard_operations.hpp"
#include "headers/fen.hpp"
#include "headers/constants.hpp"
#include "headers/fen.hpp"

#include <string>

chess::Board::Board(std::array<std::array<Bitboard, 6>, 2> board) {
    piece_bitboards = board;
    side_bitboards = {0, 0};
    all = 0;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 6; j++) {
            side_bitboards[i] |= board[i][j];
        }
    }
    all = side_bitboards[0] | side_bitboards[1];
    _hashes.push_back(zobrist::ZobristHash(*this));

}

chess::Board::Board(std::string fen){
    piece_bitboards = chess::convert_fen_to_bitboards(fen);
    side_bitboards = {0, 0};
    all = 0;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 6; j++) {
            side_bitboards[i] |= piece_bitboards[i][j];
        }
    }
    all = side_bitboards[0] | side_bitboards[1];
    _hashes.push_back(zobrist::ZobristHash(*this));
}



chess::Board::Board() {
    std::array<std::array<Bitboard, 6>, 2> board = chess::convert_default_positions();
    piece_bitboards = board;
    side_bitboards = {0, 0};
    all = 0;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 6; j++) {
            side_bitboards[i] |= board[i][j];
        }
    }
    all = side_bitboards[0] | side_bitboards[1];
    _hashes.push_back(zobrist::ZobristHash(*this));
}

bool chess::Board::operator == (const Board &board) const {
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 6; j++) {
            if (piece_bitboards[i][j] != board.piece_bitboards[i][j]) {
                return false;
            }
        }
    }
    return true;
}


bool chess::Board::operator != (const Board &board) const {
    return !(*this == board);
}


int8_t chess::Board::get_piece_type(const chess::Board& board, uint8_t x, uint8_t y) {
    for (int i = 0; i < 6; i++) {
        if (bitboard_operations::get_bit(board.piece_bitboards[chess::White][i], y * 8 + x)) return i;
        if (bitboard_operations::get_bit(board.piece_bitboards[chess::Black][i], y * 8 + x)) return i + 6;
    }
    return -1;
}

int8_t chess::Board::get_piece_type(const chess::Board& board, uint8_t x) {
    for (int i = 0; i < 6; i++) {
        if (bitboard_operations::get_bit(board.piece_bitboards[chess::White][i], x)) return i;
        if (bitboard_operations::get_bit(board.piece_bitboards[chess::Black][i], x)) return i + 6;
    }
    return -1;
}

chess::Board& chess::Board::operator = (const Board& other) {
    piece_bitboards = other.piece_bitboards;
    side_bitboards = other.side_bitboards;
    all = other.all;
    white_turn = other.white_turn;
    white_castling = other.white_castling;
    black_castling = other.black_castling;
    w_l_castling = other.w_l_castling;
    w_s_castling = other.w_s_castling;
    b_l_castling = other.b_l_castling;
    b_s_castling = other.b_s_castling;
    num_of_moves = other.num_of_moves;
    legal_moves = other.legal_moves;
    _hashes = other._hashes;

    return *this;
}