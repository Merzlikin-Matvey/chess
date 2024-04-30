#include <iostream>

#include "chess-engine.hpp"
#include <iostream>
#include <omp.h>
#include <chrono>

using namespace std;
using namespace chess;

int main() {
    Board board = Board("4R3/8/8/8/Q3k3/5PN1/8/8");

    auto mask = masks::get_check_mask(board, Black);

    print_bitboard(mask);




}