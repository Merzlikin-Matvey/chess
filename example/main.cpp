#include <iostream>

#include "chess-engine.hpp"
#include <iostream>
#include <omp.h>
#include <chrono>
#include <cmath>

using namespace std;
using namespace chess;


int main() {
    Board board = Board("r7/P7/P7/K7/8/8/P7/r7");

    auto mask = masks::get_vertical_pin_mask(board, 32, 0);
    print_bitboard(mask);
}