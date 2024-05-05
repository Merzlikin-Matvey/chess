#include <iostream>

#include "chess-engine.hpp"
#include <iostream>
#include <omp.h>
#include <chrono>
#include <cmath>

using namespace std;
using namespace chess;


int main() {
    Board board = Board("8/8/8/8/4p3/8/2B5/B7");
    print_bitboard(masks::get_bishop_mask(board, 10, 1));

}