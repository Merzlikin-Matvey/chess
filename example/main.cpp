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
    Board board = Board("3b2n1/p1N1kppr/4Q2p/1p6/2P5/1P4P1/P2PP2P/R1B1KBNR");
    board.white_turn = false;
    cout << board << endl;
    auto moves = board.get_legal_moves();
    for (int i = 0; i < moves.size(); i++) {
        cout << moves[i].to_string() << endl;
    }
    cout << "Is check: " << board.is_check() << endl;

}

