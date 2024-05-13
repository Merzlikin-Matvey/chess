#include <iostream>

#include "headers/check_and_checkmate.hpp"
#include "chess-engine.hpp"
#include <iostream>
#include <omp.h>
#include <chrono>
#include <cmath>

using namespace std;
using namespace chess;

void test() {
    int n = 1000;
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
    test();
}

