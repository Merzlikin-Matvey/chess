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
    masks::generate_rook_or_queen_horizontal_pin_masks(10);
}