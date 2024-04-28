#include <chess-engine.hpp>


chess::Board::Board(std::array<std::array<Bitboard, 6>, 2> board) {
    _piece_bitboards = board;
    _side_bitboards = {0, 0};
    _inversion_side_bitboards = {0, 0};
    _all = 0;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 6; j++) {
            _side_bitboards[i] |= board[i][j];
            _inversion_side_bitboards[i] |= ~board[i][j];
        }
    }
    _all = _side_bitboards[0] | _side_bitboards[1];

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


int8_t chess::Board::getPieceType(const chess::Board& board, uint8_t x, uint8_t y) {
    for (int i = 0; i < 6; i++) {
        if (chess_operations::get_bit(board._piece_bitboards[chess::White][i], y * 8 + x)) return i;
        if (chess_operations::get_bit(board._piece_bitboards[chess::Black][i], y * 8 + x)) return i + 6;
    }
    return -1;
}