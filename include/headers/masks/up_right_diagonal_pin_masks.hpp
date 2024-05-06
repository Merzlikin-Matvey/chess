#pragma once

#include "headers/magic_numbers.hpp"
#include "headers/bitboard_lines.hpp"
#include "headers/bitboard_operations.hpp"
#include "headers/masks/masks_utils.hpp"
#include "headers/board.hpp"
#include "headers/constants.hpp"
#include "headers/masks/number_of_bits.hpp"

namespace chess::masks {
    constexpr int get_up_right_diagonal_pin_hash(Bitboard board, uint8_t square) {
        Bitboard magic_number = chess::magic_numbers::up_right_diagonal_pin_magic_numbers[square];
        int num_bits = _up_right_bits[square] + _down_left_diagonal_bits[square];
        return (board * magic_number) >> (64 - num_bits);
    }

}