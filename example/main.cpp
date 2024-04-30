#include <iostream>

#include "chess-engine.hpp"
#include <iostream>
#include <omp.h>
#include <chrono>

using namespace std;
using namespace chess;

int main() {
    Board board = Board();
    print_bitboard(board._all);

}