#include "headers/board.hpp"
#include "headers/bitboard_operations.hpp"

bool chess::Board::is_begin() {
    if (num_of_moves <= 4) {
        return true;
    }
    return false;
}

bool chess::Board::is_end() {
    if (bitboard_operations::count_1(side_bitboards[0]) <= 6 || bitboard_operations::count_1(side_bitboards[1]) <= 6) {
        return true;
    }
    return false;
}

