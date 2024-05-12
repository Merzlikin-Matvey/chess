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
    auto board = Board();
    int n = 10;

    auto start = chrono::high_resolution_clock::now();
    for (int i = 0; i < n; i++) {
        auto board1 = board;
    }
    auto end = chrono::high_resolution_clock::now();

    auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start);
    cout << "Time: " << duration.count() / n << "ns" << endl;
}

int main() {
    string fen;
    for (int i = 0; i < 10; i++) {
        cin >> fen;
        auto board = Board(fen);
        cout << "Check: " << board.is_check() << endl;
        cout << "Double check: " << board.is_double_check() << endl;
    }
}