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
    test();

}

