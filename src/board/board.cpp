#include "headers/board.hpp"
#include "headers/bitboard_operations.hpp"
#include "headers/fen.hpp"
#include "headers/constants.hpp"
#include "headers/fen.hpp"

#include <string>

chess::Board::Board(std::array<std::array<Bitboard, 6>, 2> board) {
    _piece_bitboards = board;
    _side_bitboard = 0;
    _inversion_side_bitboard = 0;
    _all = 0;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 6; j++) {
            _side_bitboard |= board[i][j];
            _inversion_side_bitboard |= ~board[i][j];
        }
    }
    _all = _side_bitboard | _inversion_side_bitboard;

}

chess::Board::Board(std::string fen){
    std::array<std::array<Bitboard, 6>, 2> board = chess::convert_fen_to_bitboards(fen);
    _piece_bitboards = board;
    _side_bitboard = 0;
    _inversion_side_bitboard = 0;
    _all = 0;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 6; j++) {
            _side_bitboard |= board[i][j];
            _inversion_side_bitboard |= ~board[i][j];
        }
    }
    _all = _side_bitboard | _inversion_side_bitboard;
}



chess::Board::Board() {
    std::array<std::array<Bitboard, 6>, 2> board = chess::convert_default_positions();
    _piece_bitboards = board;
    _side_bitboard = 0;
    _inversion_side_bitboard = 0;
    _all = 0;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 6; j++) {
            _side_bitboard |= board[i][j];
            _inversion_side_bitboard |= ~board[i][j];
        }
    }
    _all = _side_bitboard | _inversion_side_bitboard;

}

bool chess::Board::operator == (const Board &board) const {
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 6; j++) {
            if (_piece_bitboards[i][j] != board._piece_bitboards[i][j]) {
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
        if (bitboard_operations::get_bit(board._piece_bitboards[chess::White][i], y * 8 + x)) return i;
        if (bitboard_operations::get_bit(board._piece_bitboards[chess::Black][i], y * 8 + x)) return i + 6;
    }
    return -1;
}

int8_t chess::Board::get_piece_type(const chess::Board& board, uint8_t x) {
    for (int i = 0; i < 6; i++) {
        if (bitboard_operations::get_bit(board._piece_bitboards[chess::White][i], x)) return i;
        if (bitboard_operations::get_bit(board._piece_bitboards[chess::Black][i], x)) return i + 6;
    }
    return -1;
}