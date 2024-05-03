#include <iostream>

#include "chess-engine.hpp"
#include "headers/C functions/magic_numbers.h"
#include <iostream>
#include <omp.h>
#include <chrono>

using namespace std;
using namespace chess;


int main() {
    Bitboard board1 = 0;
    bitboard_operations::set_1(board1, 4);
    int hash = chess::masks::get_rook_hash(board1, 1);
    auto masks = chess::masks::generate_rook_masks();
    print_bitboard(masks[1][hash]);



}