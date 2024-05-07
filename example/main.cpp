#include <iostream>

#include "chess-engine.hpp"
#include <iostream>
#include <omp.h>
#include <chrono>
#include <cmath>

using namespace std;
using namespace chess;


int main() {
    Board board = Board("8/8/8/4b3/3P4/8/1K6/8");
    print_bitboard(masks::get_up_right_pin_mask(board, 7, 0));
}