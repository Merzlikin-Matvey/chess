#include <iostream>

#include "chess-lib.hpp"
#include <chrono>

#include "headers/uci.hpp"

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
    Board board = Board("7k/8/8/8/pPp5/8/8/7K b - b3 0 1");

    cout << "FEN: " << board.to_fen() << endl;

    board.get_legal_moves();

    for (int i = 0; i < board.legal_moves.size(); i++) {
        cout << board.legal_moves.moves[i].to_string() << endl;
    }
}

