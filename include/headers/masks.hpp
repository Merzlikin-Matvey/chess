#pragma once

#include <array>
#include <memory>
#include <string>
#include <map>

#include "headers/board.hpp"

typedef uint64_t Bitboard;

namespace masks {
    static consteval std::array<std::array<Bitboard, 64>, 8> get_directions_masks() {
        std::array<std::array<Bitboard, 64>, 8> masks{};

        // UP
        for (int i = 0; i < 64; i++) {
            Bitboard mask = 0;
            for (int j = i + 8; j < 64; j += 8) {
                mask |= (1ull << j);
            }
            masks[0][i] = mask;
        }

        // DOWN
        for (int i = 0; i < 64; i++) {
            Bitboard mask = 0;
            for (int j = i - 8; j >= 0; j -= 8) {
                mask |= (1ull << j);
            }
            masks[1][i] = mask;
        }

        // RIGHT
        for (int i = 0; i < 64; i++) {
            Bitboard mask = 0;
            for (int j = i + 1; j % 8 != 0; j++) {
                mask |= (1ull << j);
            }
            masks[2][i] = mask;
        }

        // LEFT
        for (int i = 0; i < 64; i++) {
            Bitboard mask = 0;
            for (int j = i - 1; j >= 0 && j % 8 != 7; j--) {
                mask |= (1ull << j);
            }
            masks[3][i] = mask;
        }

        // UP RIGHT
        for (int i = 0; i < 64; i++) {
            Bitboard mask = 0;
            for (int j = i + 9; j % 8 != 0 && j < 64; j += 9) {
                mask |= (1ull << j);
            }
            masks[4][i] = mask;
        }

        // UP LEFT
        for (int i = 0; i < 64; i++) {
            Bitboard mask = 0;
            for (int j = i + 7; j % 8 != 7 && j < 64; j += 7) {
                mask |= (1ull << j);
            }
            masks[5][i] = mask;
        }

        // DOWN RIGHT
        for (int i = 0; i < 64; i++) {
            Bitboard mask = 0;
            for (int j = i - 7; j % 8 != 0 && j >= 0; j -= 7) {
                mask |= (1ull << j);
            }
            masks[6][i] = mask;
        }

        // DOWN LEFT
        for (int i = 0; i < 64; i++) {
            Bitboard mask = 0;
            for (int j = i - 9; j >= 0 && j % 8 != 7; j -= 9) {
                mask |= (1ull << j);
            }
            masks[7][i] = mask;
        }

        return masks;
    }

    static consteval std::array<Bitboard, 64> get_rook_masks(){
        std::array<Bitboard, 64> masks{};
        for (int i = 0; i < 64; i++) {
            Bitboard up = get_directions_masks()[0][i];
            Bitboard down = get_directions_masks()[1][i];
            Bitboard right = get_directions_masks()[2][i];
            Bitboard left = get_directions_masks()[3][i];
            masks[i] = up | down | right | left;
        }
        return masks;
    }

    static consteval std::array<Bitboard, 64> get_bishop_masks(){
        std::array<Bitboard, 64> masks{};
        for (int i = 0; i < 64; i++) {
            Bitboard up_right = get_directions_masks()[4][i];
            Bitboard up_left = get_directions_masks()[5][i];
            Bitboard down_right = get_directions_masks()[6][i];
            Bitboard down_left = get_directions_masks()[7][i];
            masks[i] = up_right | up_left | down_right | down_left;
        }
        return masks;
    }

    static consteval std::array<Bitboard, 64> get_knight_masks() {
        std::array<Bitboard, 64> masks{};
        for (int i = 0; i < 64; i++) {
            Bitboard mask = 0;
            if (i % 8 < 6) {
                if (i / 8 < 7) {
                    mask |= (1ull << (i + 17));
                }
                if (i / 8 > 0) {
                    mask |= (1ull << (i - 15));
                }
            }
            if (i % 8 < 7) {
                if (i / 8 < 6) {
                    mask |= (1ull << (i + 10));
                }
                if (i / 8 > 1) {
                    mask |= (1ull << (i - 6));
                }
            }
            if (i % 8 > 0) {
                if (i / 8 < 6) {
                    mask |= (1ull << (i + 15));
                }
                if (i / 8 > 0) {
                    mask |= (1ull << (i - 17));
                }
            }
            if (i % 8 > 1) {
                if (i / 8 < 7) {
                    mask |= (1ull << (i + 6));
                }
                if (i / 8 > 1) {
                    mask |= (1ull << (i - 10));
                }
            }
            masks[i] = mask;
        }
        return masks;
    }

    static consteval std::array<Bitboard, 64> get_queen_masks() {
        std::array<Bitboard, 64> masks{};
        for (int i = 0; i < 64; i++) {
            masks[i] = get_rook_masks()[i] | get_bishop_masks()[i];
        }
        return masks;
    }

    static consteval std::array<Bitboard, 64> get_king_masks() {
        std::array<Bitboard, 64> masks{};
        for (int i = 0; i < 64; i++) {
            Bitboard mask = 0;
            if (i % 8 < 7) {
                mask |= (1ull << (i + 1));
                if (i / 8 < 7) {
                    mask |= (1ull << (i + 9));
                }
                if (i / 8 > 0) {
                    mask |= (1ull << (i - 7));
                }
            }
            if (i % 8 > 0) {
                mask |= (1ull << (i - 1));
                if (i / 8 < 7) {
                    mask |= (1ull << (i + 7));
                }
                if (i / 8 > 0) {
                    mask |= (1ull << (i - 9));
                }
            }
            if (i / 8 < 7) {
                mask |= (1ull << (i + 8));
            }
            if (i / 8 > 0) {
                mask |= (1ull << (i - 8));
            }
            masks[i] = mask;
        }
        return masks;
    }

    Bitboard get_pawn_short_mask(chess::Board board, uint8_t side);
    Bitboard get_pawn_long_mask(chess::Board board, uint8_t side);
    Bitboard get_pawn_right_mask(chess::Board board, uint8_t side);
    Bitboard get_pawn_left_mask(chess::Board board, uint8_t side);



}



