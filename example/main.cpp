#include <iostream>

#include "chess-engine.hpp"
#include "headers/C functions/magic_numbers.h"
#include <iostream>
#include <omp.h>
#include <chrono>
#include <cmath>

using namespace std;
using namespace chess;

void test() {
    Board board = Board("8/6q1/8/4N3/3K4/8/1B6/q7");

    int n = 1000;

    auto start = chrono::high_resolution_clock::now();
    for (int i = 0; i < n; i++) {
        auto arr = board.get_legal_moves();
    }
    auto end = chrono::high_resolution_clock::now();

    auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start);
    cout << "Time: " << duration.count() / n << "ns" << endl;
}

int main() {
    Board board = Board("8/8/8/8/8/8/8/P7");
    auto mask = masks::get_pawn_mask(board.piece_bitboards[White][Pawn], White);
    MoveArray moves = MoveArray();
    board.pawn_mask_to_moves(mask, 8, &moves);
    for (int i = 0; i < moves.size; i++) {
        cout << moves.moves[i] << endl;
    }

}