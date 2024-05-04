#pragma once

#include "headers/masks_utils.hpp"
#include "headers/magic_numbers.hpp"
#include "headers/bitboard_lines.hpp"
#include "headers/bitboard_operations.hpp"
#include "headers/board.hpp"

#include <array>
#include <iostream>

typedef uint64_t Bitboard;

namespace chess::masks {
    constexpr std::array<uint8_t, 64> up_right_bits = {
            6, 5, 4, 3, 2, 1, 0, 0,
            5, 5, 4, 3, 2, 1, 0, 0,
            4, 4, 4, 3, 2, 1, 0, 0,
            3, 3, 3, 3, 2, 1, 0, 0,
            2, 2, 2, 2, 2, 1, 0, 0,
            1, 1, 1, 1, 1, 1, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0
    };

    constexpr std::array<uint8_t, 64> down_left_bits = {
            0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 1, 1, 1, 1, 1, 1,
            0, 0, 1, 2, 2, 2, 2, 2,
            0, 0, 1, 2, 3, 3, 3, 3,
            0, 0, 1, 2, 3, 4, 4, 4,
            0, 0, 1, 2, 3, 4, 5, 5,
            0, 0, 1, 2, 3, 4, 5, 6
    };

    constexpr std::array<uint8_t, 64> up_left_bits = {
            0, 0, 1, 2, 3, 4, 5, 6,
            0, 0, 1, 2, 3, 4, 5, 5,
            0, 0, 1, 2, 3, 4, 4, 4,
            0, 0, 1, 2, 3, 3, 3, 3,
            0, 0, 1, 2, 2, 2, 2, 2,
            0, 0, 1, 1, 1, 1, 1, 1,
            0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0
    };

    constexpr std::array<uint8_t, 64> down_right_bits = {
            0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0,
            1, 1, 1, 1, 1, 1, 0, 0,
            2, 2, 2, 2, 2, 1, 0, 0,
            3, 3, 3, 3, 2, 1, 0, 0,
            4, 4, 4, 3, 2, 1, 0, 0,
            5, 5, 4, 3, 2, 1, 0, 0,
            6, 5, 4, 3, 2, 1, 0, 0
    };

    constexpr int get_bishop_hash(Bitboard board, uint8_t square) {
        Bitboard magic_number = chess::magic_numbers::bishop_magic_numbers[square];
        int num_bits = up_right_bits[square] + down_right_bits[square] + up_left_bits[square] + down_left_bits[square];
        int hash = (board * magic_number) >> (64 - num_bits);
        return hash;
    }

    static constexpr std::array<Bitboard, 512> _generate_bishop_masks(uint8_t square) {
        std::array<Bitboard, 512> masks = {};
        Bitboard board, mask;
        uint8_t num_up_right_bits = up_right_bits[square];
        uint8_t num_down_right_bits = down_right_bits[square];
        uint8_t num_up_left_bits = up_left_bits[square];
        uint8_t num_down_left_bits = down_left_bits[square];
        uint8_t num_bits = num_up_right_bits + num_down_right_bits + num_up_left_bits + num_down_left_bits;
        int hash;
        bool flag;

        for (uint16_t blockers = 0; blockers < _pow2(num_bits); blockers++) {
            board = 0;
            mask = 0;

            flag = true;
            for (uint8_t bit = 0; bit < num_up_right_bits; bit++) {
                if (_get_bit(blockers, bit)) {
                    if (flag) {
                        mask |= chess::masks::lines[square + 9 * (bit + 1)][square];
                        flag = false;
                    }
                    bitboard_operations::set_1(board, square + 9 * (bit + 1));
                }
            }

            if (flag and (square + 9 * (num_up_right_bits + 1) < 64)) {
                mask |= chess::masks::lines[square + 9 * num_up_right_bits][square];
            }


            flag = true;
            for (uint8_t bit = 0; bit < num_down_right_bits; bit++) {
                if (_get_bit(blockers, bit + num_up_right_bits)) {
                    if (flag) {
                        mask |= chess::masks::lines[square - 9 * (bit + 1)][square];
                        flag = false;
                    }
                    bitboard_operations::set_1(board, square - 9 * (bit + 1));
                }
            }

            if (flag and (square - 9 * (num_down_right_bits + 1) >= 0)) {
                mask |= chess::masks::lines[square - 9 * num_down_right_bits][square];
            }


            flag = true;
            for (uint8_t bit = 0; bit < num_up_left_bits; bit++) {
                if (_get_bit(blockers, bit + num_up_right_bits + num_down_right_bits)) {
                    if (flag) {
                        mask |= chess::masks::lines[square + 7 * (bit + 1)][square];
                        flag = false;
                    }
                    bitboard_operations::set_1(board, square + 7 * (bit + 1));
                }
            }

            if (flag and num_up_left_bits > 0) {
                mask |= chess::masks::lines[square + 7 * num_up_left_bits][square];
            }


            flag = true;
            for (uint8_t bit = 0; bit < num_down_left_bits; bit++) {
                if (_get_bit(blockers, bit + num_up_right_bits + num_down_right_bits + num_up_left_bits)) {
                    if (flag) {
                        mask |= chess::masks::lines[square - 7 * (bit + 1)][square];
                        flag = false;
                    }
                    bitboard_operations::set_1(board, square - 7 * (bit + 1));
                }
            }

            if (flag and num_down_left_bits > 0) {
                mask |= chess::masks::lines[square - 7 * num_down_left_bits][square];
            }

            hash = get_bishop_hash(board, square);
            masks[hash] = mask;
        }

        return masks;
    }

     consteval std::array<std::array<Bitboard, 512>, 64> _get_bishop_masks(){
        std::array<std::array<Bitboard, 512>, 64> masks = {};
        for (uint8_t square = 0; square < 64; square++) {
            masks[square] = _generate_bishop_masks(square);
        }
        return masks;
    }

    constexpr std::array<std::array<Bitboard, 512>, 64> bishop_masks = _get_bishop_masks();


}