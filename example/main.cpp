#include <iostream>

#include "headers/check_and_checkmate.hpp"
#include <chrono>

using namespace std;
using namespace chess;

void test() {
    int n = 10000;
    auto board = Board("5K2/1R6/2R5/3R4/4R3/5R2/6R1/8");

    auto start = chrono::high_resolution_clock::now();
    for (int i = 0; i < n; i++) {
        board.get_legal_moves();
    }
    auto end = chrono::high_resolution_clock::now();

    auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start);
    cout << "Time: " << duration.count() / n << "ns" << endl;
}

int main() {
    Board board = Board("8/5q2/1K6/6N1/8/8/8/5k2");
    board.get_legal_moves();
    for (int i = 0; i < board.legal_moves.size(); i++){
        cout << board.legal_moves[i].to_string() << endl;
    }
    for (int i = 0; i < board.legal_moves.size(); i++){
        auto copy = board;
        cout << copy << endl;
        copy.move(copy.legal_moves[i]);
        cout << copy.legal_moves[i].to_string();
    }

}

