#pragma once
#include "bitboard_operations.hpp"


namespace chess::engine::constants {

    static constexpr int maximum = 100000;
    static constexpr int minimum = -100000;

    static constexpr int mate_score = 99000;

    static consteval Bitboard get_center_bitboard() {
        Bitboard center = 0;
        bitboard_operations::set_1(center, 27);
        bitboard_operations::set_1(center, 28);
        bitboard_operations::set_1(center, 35);
        bitboard_operations::set_1(center, 36);
        return center;
    }

    static constexpr Bitboard center = get_center_bitboard();

}  // namespace chess::engine::constants
