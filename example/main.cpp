#include <iostream>

#include "chess-lib.hpp"
#include <chrono>

using namespace std;
using namespace chess;

int count_positions(Board& board, int depth) {
    if (depth == 0) {
        return 1;
    }

    int count = 0;
    board.get_legal_moves();
    for (int i = 0; i < board.legal_moves.size(); i++) {
        Board copy = board;
        copy.move(board.legal_moves.moves[i]);
        count += count_positions(copy, depth - 1);
    }

    return count;
}

int main() {
    auto  board = Board("8/ppp3p1/8/8/3p4/8/1ppp2K1/brk2Q1n b - - 12 7");

    cout << "FEN: " << board.to_fen() << endl;

    board.get_legal_moves();

    for (int i = 0; i < board.legal_moves.size(); i++) {
        cout << board.legal_moves.moves[i].to_string() << endl;
    }
}

