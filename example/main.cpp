#include <iostream>

#include "chess-engine.hpp"
#include <iostream>
#include <omp.h>
#include <chrono>
#include <cmath>

using namespace std;
using namespace chess;


int main() {
    Board board = Board("rPP1KnPr/8/8/8/8/8/8/8");
    print_bitboard(masks::get_horizontal_pin_mask(board, 60, 0));
}