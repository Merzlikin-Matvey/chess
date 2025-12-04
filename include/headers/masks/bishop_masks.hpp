#pragma once

#include "headers/bitboard_lines.hpp"
#include "headers/bitboard_operations.hpp"
#include "headers/board.hpp"
#include "headers/magic_numbers.hpp"
#include "headers/magic_numbers_constants.hpp"
#include "masks_utils.hpp"

#include <array>
#include <iostream>

typedef uint64_t Bitboard;

namespace chess::masks {
    constexpr std::array<uint8_t, 64> bishop_up_right_bits = {
        6, 5, 4, 3, 2, 1, 0, 0, 5, 5, 4, 3, 2, 1, 0, 0, 4, 4, 4, 3, 2, 1, 0, 0, 3, 3, 3, 3, 2, 1, 0, 0,
        2, 2, 2, 2, 2, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    constexpr std::array<uint8_t, 64> bishop_down_left_bits = {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 2, 2, 2, 2, 2,
        0, 0, 1, 2, 3, 3, 3, 3, 0, 0, 1, 2, 3, 4, 4, 4, 0, 0, 1, 2, 3, 4, 5, 5, 0, 0, 1, 2, 3, 4, 5, 6};

    constexpr std::array<uint8_t, 64> bishop_up_left_bits = {
        0, 0, 1, 2, 3, 4, 5, 6, 0, 0, 1, 2, 3, 4, 5, 5, 0, 0, 1, 2, 3, 4, 4, 4, 0, 0, 1, 2, 3, 3, 3, 3,
        0, 0, 1, 2, 2, 2, 2, 2, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    constexpr std::array<uint8_t, 64> bishop_down_right_bits = {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 2, 2, 2, 2, 2, 1, 0, 0,
        3, 3, 3, 3, 2, 1, 0, 0, 4, 4, 4, 3, 2, 1, 0, 0, 5, 5, 4, 3, 2, 1, 0, 0, 6, 5, 4, 3, 2, 1, 0, 0};

    constexpr int get_bishop_hash(Bitboard board, uint8_t square) {
        Bitboard magic_number = chess::magic_numbers::bishop_magic_numbers[square];
        int num_bits = bishop_up_right_bits[square] + bishop_down_right_bits[square] + bishop_up_left_bits[square] +
            bishop_down_left_bits[square];
        int hash = (board * magic_number) >> (64 - num_bits);
        return hash;
    }

    static constexpr std::array<Bitboard, 512> generate_primary_bishop_masks(uint8_t square) {
        std::array<Bitboard, 512> masks = {};
        Bitboard board, mask;
        uint8_t num_bishop_up_right_bits = bishop_up_right_bits[square];
        uint8_t num_bishop_down_right_bits = bishop_down_right_bits[square];
        uint8_t num_bishop_up_left_bits = bishop_up_left_bits[square];
        uint8_t num_bishop_down_left_bits = bishop_down_left_bits[square];
        uint8_t num_bits =
            num_bishop_up_right_bits + num_bishop_down_right_bits + num_bishop_up_left_bits + num_bishop_down_left_bits;
        int hash;
        bool flag;

        for (uint16_t blockers = 0; blockers < _pow2(num_bits); blockers++) {
            board = 0;
            mask = 0;

            flag = true;
            for (uint8_t bit = 0; bit < num_bishop_up_right_bits; bit++) {
                if (_get_bit(blockers, bit)) {
                    if (flag) {
                        mask |= chess::masks::lines[square + 9 * (bit + 1)][square];
                        flag = false;
                    }
                    bitboard_operations::set_1(board, square + 9 * (bit + 1));
                }
            }

            if (flag and (square % 8 != 7) and (square < 56) and (square + 9 * (num_bishop_up_right_bits + 1) >= 0)) {
                mask |= chess::masks::lines[square + 9 * (num_bishop_up_right_bits + 1)][square];
            }


            flag = true;
            for (uint8_t bit = 0; bit < num_bishop_down_right_bits; bit++) {
                if (_get_bit(blockers, bit + num_bishop_up_right_bits)) {
                    if (flag) {
                        mask |= chess::masks::lines[square - 7 * (bit + 1)][square];
                        flag = false;
                    }
                    bitboard_operations::set_1(board, square - 7 * (bit + 1));
                }
            }

            if (flag and (square % 8 != 7) and (square > 7) and (square - 7 * (num_bishop_down_right_bits + 1) >= 0)) {
                mask |= chess::masks::lines[square - 7 * (num_bishop_down_right_bits + 1)][square];
            }


            flag = true;
            for (uint8_t bit = 0; bit < num_bishop_up_left_bits; bit++) {
                if (_get_bit(blockers, bit + num_bishop_up_right_bits + num_bishop_down_right_bits)) {
                    if (flag) {
                        mask |= chess::masks::lines[square + 7 * (bit + 1)][square];
                        flag = false;
                    }
                    bitboard_operations::set_1(board, square + 7 * (bit + 1));
                }
            }

            if (flag and (square % 8 != 0) and (square < 56) and (square + 7 * (num_bishop_up_left_bits + 1) >= 0)) {
                mask |= chess::masks::lines[square + 7 * (num_bishop_up_left_bits + 1)][square];
            }


            flag = true;
            for (uint8_t bit = 0; bit < num_bishop_down_left_bits; bit++) {
                if (_get_bit(blockers,
                             bit + num_bishop_up_right_bits + num_bishop_down_right_bits + num_bishop_up_left_bits)) {
                    if (flag) {
                        mask |= chess::masks::lines[square - 9 * (bit + 1)][square];
                        flag = false;
                    }
                    bitboard_operations::set_1(board, square - 9 * (bit + 1));
                }
            }

            if (flag and (square % 8 != 0) and (square > 7) and (square - 9 * (num_bishop_down_left_bits + 1) >= 0)) {
                mask |= chess::masks::lines[square - 9 * (num_bishop_down_left_bits + 1)][square];
            }

            hash = get_bishop_hash(board, square);

            masks[hash] = mask;
        }

        return masks;
    }

    static consteval std::array<std::array<Bitboard, 512>, 64> get_primary_bishop_masks() {
        std::array<std::array<Bitboard, 512>, 64> masks = {};
        for (uint8_t square = 0; square < 64; square++) {
            masks[square] = generate_primary_bishop_masks(square);
        }
        return masks;
    }

    static constexpr Bitboard get_secondary_bishop_mask(uint8_t square) {
        Bitboard mask = 0;
        uint8_t num_bishop_up_right_bits = bishop_up_right_bits[square];
        uint8_t num_bishop_down_right_bits = bishop_down_right_bits[square];
        uint8_t num_bishop_up_left_bits = bishop_up_left_bits[square];
        uint8_t num_bishop_down_left_bits = bishop_down_left_bits[square];

        for (uint8_t i = 0; i < num_bishop_up_right_bits; i++) {
            bitboard_operations::set_1(mask, square + 9 * (i + 1));
        }

        for (uint8_t i = 0; i < num_bishop_down_right_bits; i++) {
            bitboard_operations::set_1(mask, square - 7 * (i + 1));
        }

        for (uint8_t i = 0; i < num_bishop_up_left_bits; i++) {
            bitboard_operations::set_1(mask, square + 7 * (i + 1));
        }

        for (uint8_t i = 0; i < num_bishop_down_left_bits; i++) {
            bitboard_operations::set_1(mask, square - 9 * (i + 1));
        }

        return mask;
    }

    static consteval std::array<Bitboard, 64> get_secondary_bishop_masks() {
        std::array<Bitboard, 64> masks = {};
        for (uint8_t square = 0; square < 64; square++) {
            masks[square] = get_secondary_bishop_mask(square);
        }
        return masks;
    }

    static constexpr std::array<Bitboard, 64> secondary_bishop_masks = get_secondary_bishop_masks();
    static constexpr std::array<std::array<Bitboard, 512>, 64> primary_bishop_masks = get_primary_bishop_masks();


} // namespace chess::masks
