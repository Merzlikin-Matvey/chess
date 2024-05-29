#pragma once

#include <memory>
#include <math.h>
#include <unordered_map>

namespace chess::engine::constants {


    static constexpr double maximum = 1024;
    static constexpr double minimum = -1024;

    static constexpr double material_weight = 2.5;
    static constexpr double pawn = 1;
    static constexpr double knight = 3.1;
    static constexpr double bishop = 3.5;
    static constexpr double rook = 4;
    static constexpr double queen = 10;
    static constexpr double king = 11;

    static constexpr double mobility_weight = 0.1;
    static constexpr double pawn_mobility = 1;
    static constexpr double knight_mobility = 1;
    static constexpr double bishop_mobility = 2.5;
    static constexpr double rook_mobility = 2.6;
    static constexpr double queen_mobility = 3;
    static constexpr double king_mobility = 4;

    static constexpr double check = -5;
    static constexpr double double_check = -15;

    static constexpr double pawn_structure = 0.5;
    static constexpr double no_pawns_in_column = -2;
    static constexpr double pawn_1_in_column = 0.5;
    static constexpr double pawn_2_in_column = -7;
    static constexpr double pawn_3_in_column = -12;
    static constexpr double pawn_4_in_column = -30;
    static constexpr double many_pawns_in_column = -80;
    static constexpr double pawn_after_king = 10;
    static constexpr double defended_pawn = 1.5;
    static constexpr double pawns_in_end = -50;

    static constexpr double center_control = 0.2;

    static constexpr double two_bishops = 3;

    static consteval Bitboard get_center_bitboard() {
        Bitboard center = 0;
        bitboard_operations::set_1(center, 27);
        bitboard_operations::set_1(center, 28);
        bitboard_operations::set_1(center, 35);
        bitboard_operations::set_1(center, 36);
        return center;
    }

    static constexpr Bitboard center = get_center_bitboard();

}