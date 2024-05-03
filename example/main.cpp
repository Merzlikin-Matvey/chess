#include <iostream>

#include "chess-engine.hpp"
#include "headers/C functions/magic_numbers.h"
#include <iostream>
#include <omp.h>
#include <chrono>

using namespace std;
using namespace chess;

void test(){
    Board board = Board("4r3/4q3/8/6b1/4P3/p1rPKR1p/4P3/8");

    long long n = 1000;

    auto start = chrono::high_resolution_clock::now();
    for (long long i = 0; i < n; i++) {
        auto mask = chess::magic_numbers::rook_magic_numbers[i % 64];
    }
    auto end = chrono::high_resolution_clock::now();

    cout << "Time per iteration: " << chrono::duration_cast<chrono::nanoseconds>(end - start).count() / n << "ns" << endl;
}

int main() {
    std::array<std::array<Bitboard, 1024>, 64> masks{};
    std::array<Bitboard, 64> magic_numbers = magic_numbers::rook_magic_numbers;
    Bitboard magic;
    Bitboard mask = 0;
    Bitboard board;

    magic = magic_numbers[0];
    board = board >> 54;
    board /= magic;
    print_bitboard(board);



}