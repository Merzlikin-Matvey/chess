#include <iostream>

#include "chess-engine.hpp"
#include "headers/C functions/magic_numbers.h"
#include <iostream>
#include <omp.h>
#include <chrono>
#include <cmath>

using namespace std;
using namespace chess;


int main() {
    Board board = Board("8/6q1/8/4N3/3K4/8/1B6/q7");
    print_bitboard(masks::get_up_right_pin_mask(board, 27, 0));

}