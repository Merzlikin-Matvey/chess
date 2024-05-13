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
    int n = 100000;

    auto start = chrono::high_resolution_clock::now();
    for (int i = 0; i < n; i++) {
        board.get_legal_moves();
    }
    auto end = chrono::high_resolution_clock::now();

    auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start);
    cout << "Time: " << duration.count() / n << "ns" << endl;
}

int main() {
    Board board = Board("8/8/8/8/8/8/8/R3K3");
    auto moves = board.get_legal_moves();
    for (int i = 0; i < moves.size; i++) {
        cout << moves[i].to_string() << endl;
    }
}