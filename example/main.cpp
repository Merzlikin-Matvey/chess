#include <iostream>

#include "headers/check_and_checkmate.hpp"
#include <chrono>

using namespace std;
using namespace chess;

void test() {
    int n = 100;
    Board board = Board();

    auto start = chrono::high_resolution_clock::now();
    for (int i = 0; i < n; i++) {
        board.get_legal_moves();
    }
    auto end = chrono::high_resolution_clock::now();

    auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start);
    cout << "Time: " << duration.count() / n << "ns" << endl;
}

int main() {
    Board board = Board("6k1/8/8/8/K7/8/8/4bR2");
    print_bitboard(masks::primary_bishop_masks[8][0]);
}

