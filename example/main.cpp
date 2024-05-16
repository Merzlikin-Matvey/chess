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
    vector<string> moves = {
            "f2f4",
            "e7e5",
            "a2a3",
            "g7g5",
            "b2b3",
            "a7a6",
            "c2c3",
            "f8b4",
            "c3c4",
            "b7b5",
            "e2e3",
            "d7d5",
            "g2g3",
            "b4c3",
            //"d2d3",
    };

    Board board = Board("7k/8/1b6/8/8/4P3/5K2/8");


    Bitboard vertical_pin_mask = masks::get_vertical_pin_mask(board, 13, White);
    Bitboard horizontal_pin_mask = masks::get_horizontal_pin_mask(board, 13, White);
    Bitboard up_right_pin_mask = masks::get_up_right_pin_mask(board, 13, White);
    Bitboard up_left_pin_mask = masks::get_down_right_pin_mask(board, 13, White);


    print_bitboard(up_left_pin_mask);

}

