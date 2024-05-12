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
    int n = 1000;

    auto start = chrono::high_resolution_clock::now();
    for (int i = 0; i < n; i++) {
        board.get_legal_moves();
    }
    auto end = chrono::high_resolution_clock::now();

    auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start);
    cout << "Time: " << duration.count() / n << "ns" << endl;
}

int main() {
    Board board = Board("8/8/1r6/4q3/8/8/1K3r2/8");
    cout << board << endl;
    auto moves = board.get_legal_moves();
    for (int i = 0; i < moves.size; i++) {
        cout << moves[i] << endl;
    }

}