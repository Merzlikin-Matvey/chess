#include <iostream>

#include "chess-lib.hpp"
#include <chrono>

#include "headers/uci.hpp"

using namespace std;
using namespace chess;

void test() {
    int n = 100;
    Board board = Board("rnbqkbnr/pppppppp/R6R/1R4R1/2R3R1/2R5/PPPPPPPP/RNBQKBNR");

    auto start = chrono::high_resolution_clock::now();
    for (int i = 0; i < n; i++) {
        board.get_legal_moves();
    }
    auto end = chrono::high_resolution_clock::now();

    auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start);
    cout << "Time: " << duration.count() / n << "ns" << endl;
}

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
    std::cout << "START GAME" << std::endl;
    auto uci = uci::UCI();
    uci.start_handle();
}

