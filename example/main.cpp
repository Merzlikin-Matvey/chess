#include <iostream>

#include "headers/check_and_checkmate.hpp"
#include <chrono>

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

int main() {
    Board board = Board("8/8/8/8/8/6K1/2Q3r1/6k1");
    auto legal_moves = board.get_legal_moves();
    for (int i = 0; i < legal_moves.size(); i++) {
        cout << legal_moves.moves[i].to_string() << endl;
    }
}

