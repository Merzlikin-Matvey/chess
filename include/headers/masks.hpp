#pragma once

#include <array>
#include <memory>
#include <string>
#include <map>
#include <iostream>


#include "headers/board.hpp"


typedef uint64_t Bitboard;

namespace masks {

    static consteval std::array<Bitboard, 64> get_up_masks(){
        std::array<Bitboard, 64> masks{};
        for (int i = 0; i < 64; i++) {
            Bitboard mask = 0;
            for (int j = i + 8; j < 64; j += 8) {
                mask |= (1ull << j);
            }
            masks[i] = mask;
        }
        return masks;
    }

    static consteval std::array<Bitboard, 64> get_down_masks(){
        std::array<Bitboard, 64> masks{};
        for (int i = 0; i < 64; i++) {
            Bitboard mask = 0;
            for (int j = i - 8; j >= 0; j -= 8) {
                mask |= (1ull << j);
            }
            masks[i] = mask;
        }
        return masks;
    }

    static consteval std::array<Bitboard, 64> get_right_masks(){
        std::array<Bitboard, 64> masks{};
        for (int i = 0; i < 64; i++) {
            Bitboard mask = 0;
            for (int j = i + 1; j % 8 != 0 and j < 64; j++) {
                mask |= (1ull << j);
            }
            masks[i] = mask;
        }
        return masks;
    }

    static consteval std::array<Bitboard, 64> get_left_masks(){
        std::array<Bitboard, 64> masks{};
        for (int i = 0; i < 64; i++) {
            Bitboard mask = 0;
            for (int j = i - 1; j % 8 != 7 and j > 0; j--) {
                mask |= (1ull << j);
            }
            masks[i] = mask;
        }
        return masks;
    }

    static consteval std::array<Bitboard, 64> get_up_right_masks(){
        std::array<Bitboard, 64> masks{};
        for (int i = 0; i < 64; i++) {
            Bitboard mask = 0;
            for (int j = i + 9; j % 8 != 0 and j < 64; j += 9) {
                mask |= (1ull << j);
            }
            masks[i] = mask;
        }
        return masks;
    }

    static consteval std::array<Bitboard, 64> get_up_left_masks(){
        std::array<Bitboard, 64> masks{};
        for (int i = 0; i < 64; i++) {
            Bitboard mask = 0;
            for (int j = i + 7; j % 8 != 7 and j < 64; j += 7) {
                mask |= (1ull << j);
            }
            masks[i] = mask;
        }
        return masks;
    }

    static consteval std::array<Bitboard, 64> get_down_right_masks(){
        std::array<Bitboard, 64> masks{};
        for (int i = 0; i < 64; i++) {
            Bitboard mask = 0;
            for (int j = i - 7; j % 8 != 0 and j > 0; j -= 7) {
                mask |= (1ull << j);
            }
            masks[i] = mask;
        }
        return masks;
    }

    static consteval std::array<Bitboard, 64> get_down_left_masks(){
        std::array<Bitboard, 64> masks{};
        for (int i = 0; i < 64; i++) {
            Bitboard mask = 0;
            for (int j = i - 9; j % 8 != 7 and j > 0; j -= 9) {
                mask |= (1ull << j);
            }
            masks[i] = mask;
        }
        return masks;
    }

    static consteval std::array<std::array<Bitboard, 64>, 8> get_directional_masks(){
        std::array<std::array<Bitboard, 64>, 8> masks{};
        for (int i = 0; i < 64; i++) {
            Bitboard up = 0, down = 0, right = 0, left = 0;
            Bitboard up_right = 0, up_left = 0, down_right = 0, down_left = 0;
            for (int j = i + 8; j < 64; j += 8) {
                up |= (1ull << j);
            }
            for (int j = i - 8; j >= 0; j -= 8) {
                down |= (1ull << j);
            }
            for (int j = i + 1; j % 8 != 0 and j < 64; j++) {
                right |= (1ull << j);
            }
            for (int j = i - 1; j % 8 != 7 and j > 0; j--) {
                left |= (1ull << j);
            }
            for (int j = i + 9; j % 8 != 0 and j < 64; j += 9) {
                up_right |= (1ull << j);
            }
            for (int j = i + 7; j % 8 != 7 and j < 64; j += 7) {
                up_left |= (1ull << j);
            }
            for (int j = i - 7; j % 8 != 0 and j > 0; j -= 7) {
                down_right |= (1ull << j);
            }
            for (int j = i - 9; j % 8 != 7 and j > 0; j -= 9) {
                down_left |= (1ull << j);
            }
            masks[0][i] = up;
            masks[1][i] = down;
            masks[2][i] = right;
            masks[3][i] = left;
            masks[4][i] = up_right;
            masks[5][i] = up_left;
            masks[6][i] = down_right;
            masks[7][i] = down_left;
        }
        return masks;
    }

    static consteval std::array<std::array<Bitboard, 1024>, 64> generate_rook_masks(){
        std::array<std::array<Bitboard, 1024>, 64> masks{};
        return masks;
    }

    static consteval std::array<Bitboard, 64> get_knight_masks() {
        std::array<Bitboard, 64> masks{};
        for (int i = 0; i < 64; i++) {
            Bitboard mask = 0;
            if (i % 8 < 6) {
                if (i / 8 < 7) {
                    if (i + 17 < 64){
                        mask |= (1ull << (i + 17));
                    }
                }
                if (i / 8 > 0) {
                    if (i >= 15) {
                        mask |= (1ull << (i - 15));
                    }
                }
            }
            if (i % 8 < 7) {
                if (i / 8 < 6) {
                    if (i + 10 < 64){
                        mask |= (1ull << (i + 10));
                    }
                }
                if (i / 8 > 1) {
                    if (i >= 6){
                        mask |= (1ull << (i - 6));
                    }
                }
            }
            if (i % 8 > 0) {
                if (i / 8 < 6) {
                    if (i + 15 < 64){
                        mask |= (1ull << (i + 15));
                    }
                }
                if (i / 8 > 0) {
                    if (i >= 17){
                        mask |= (1ull << (i - 17));
                    }
                }
            }
            if (i % 8 > 1) {
                if (i / 8 < 7) {
                    if (i + 6 < 64){
                        mask |= (1ull << (i + 6));
                    }
                }
                if (i / 8 > 1) {
                    if (i >= 10){
                        mask |= (1ull << (i - 10));
                    }
                }
            }
            masks[i] = mask;
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

    std::pair<Bitboard, Bitboard> get_check_mask(chess::Board& board, uint8_t side);

}



