#include <iostream>

#include "headers/check_and_checkmate.hpp"
#include <chrono>

using namespace std;
using namespace chess;

void test() {
    int n = 10000;
    auto default_board = Board();

    auto start = chrono::high_resolution_clock::now();
    for (int i = 0; i < n; i++) {
        auto board = default_board;
        board.get_legal_moves();
        board.move(board.legal_moves[0]);

    }
    auto end = chrono::high_resolution_clock::now();

    auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start);
    cout << "Time: " << duration.count() / n << "ns" << endl;
}

int main() {
    Board board = Board("8/8/8/6n1/4K3/3n4/8/8");
    auto moves = board.get_legal_moves();
    for (int i = 0; i < moves.size; i++){
        cout << moves[i].to_string() << endl;
    }
}

