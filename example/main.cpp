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
    Board board = Board();

    string move;
    for (int i = 0; i < 10; i++){
        cin >> move;
        board.move(move);
        cout << board;
    }

}

