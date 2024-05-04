#include <iostream>

#include "chess-engine.hpp"
#include <iostream>
#include <omp.h>
#include <chrono>

using namespace std;
using namespace chess;


int main() {
    auto masks = masks::bishop_masks;
    print_bitboard(masks[0][0]);
}