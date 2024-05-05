#include <iostream>

#include "chess-engine.hpp"
#include <iostream>
#include <omp.h>
#include <chrono>

using namespace std;
using namespace chess;


int main() {
    Board board = Board("8/8/8/8/8/8/8/2b5");
    print_bitboard(masks::get_bishop_mask(board, 2, 0));

}