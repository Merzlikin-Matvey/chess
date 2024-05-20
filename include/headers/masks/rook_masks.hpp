#pragma once

#include "headers/magic_numbers.hpp"
#include "headers/bitboard_lines.hpp"
#include "headers/masks/masks_utils.hpp"
#include "headers/magic_numbers_constants.hpp"

namespace chess::masks {
    constexpr std::array<uint8_t, 64> rook_up_bits = {
            6, 6, 6, 6, 6, 6, 6, 6,
            5, 5, 5, 5, 5, 5, 5, 5,
            4, 4, 4, 4, 4, 4, 4, 4,
            3, 3, 3, 3, 3, 3, 3, 3,
            2, 2, 2, 2, 2, 2, 2, 2,
            1, 1, 1, 1, 1, 1, 1, 1,
            0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0
    };

    constexpr std::array<uint8_t, 64> rook_down_bits {
            0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0,
            1, 1, 1, 1, 1, 1, 1, 1,
            2, 2, 2, 2, 2, 2, 2, 2,
            3, 3, 3, 3, 3, 3, 3, 3,
            4, 4, 4, 4, 4, 4, 4, 4,
            5, 5, 5, 5, 5, 5, 5, 5,
            6, 6, 6, 6, 6, 6, 6, 6,
    };

    constexpr std::array<uint8_t, 64> rook_right_bits {
            6, 5, 4, 3, 2, 1, 0, 0,
            6, 5, 4, 3, 2, 1, 0, 0,
            6, 5, 4, 3, 2, 1, 0, 0,
            6, 5, 4, 3, 2, 1, 0, 0,
            6, 5, 4, 3, 2, 1, 0, 0,
            6, 5, 4, 3, 2, 1, 0, 0,
            6, 5, 4, 3, 2, 1, 0, 0,
            6, 5, 4, 3, 2, 1, 0, 0
    };

    constexpr std::array<uint8_t, 64> rook_left_bits {
            0, 0, 1, 2, 3, 4, 5, 6,
            0, 0, 1, 2, 3, 4, 5, 6,
            0, 0, 1, 2, 3, 4, 5, 6,
            0, 0, 1, 2, 3, 4, 5, 6,
            0, 0, 1, 2, 3, 4, 5, 6,
            0, 0, 1, 2, 3, 4, 5, 6,
            0, 0, 1, 2, 3, 4, 5, 6,
            0, 0, 1, 2, 3, 4, 5, 6
    };

    constexpr int get_rook_hash(Bitboard board, uint8_t square){
        Bitboard magic_number = chess::magic_numbers::rook_magic_numbers[square];
        int num_bits = rook_up_bits[square] + rook_down_bits[square] + rook_right_bits[square] + rook_left_bits[square];
        return (board * magic_number) >> (64 - num_bits);
    }

     constexpr std::array<Bitboard , 4096> generate_primary_rook_masks(uint8_t square){
        std::array<Bitboard , 4096> masks = {};
        Bitboard board, mask;
        uint8_t num_up_bits = rook_up_bits[square];
        uint8_t num_down_bits = rook_down_bits[square];
        uint8_t num_right_bits = rook_right_bits[square];
        uint8_t num_left_bits = rook_left_bits[square];
        uint8_t num_bits = num_up_bits + num_down_bits + num_right_bits + num_left_bits;
        int hash;
        bool flag;

        for (uint16_t blockers = 0; blockers < _pow2(num_bits); blockers++) {
            board = 0;
            mask = 0;

            flag = true;
            for (uint8_t bit = 0; bit < num_up_bits; bit++) {
                if (_get_bit(blockers, bit)) {
                    if (flag) {
                        mask |= chess::masks::lines[square + 8 * (bit + 1)][square];
                        flag = false;
                    }
                    bitboard_operations::set_1(board, square + 8 * (bit + 1));
                }
            }

            if (flag and num_up_bits > 0) {
                mask |= chess::masks::lines[square + 8 * (num_up_bits + 1)][square];
            }


            flag = true;
            for (uint8_t bit = 0; bit < num_down_bits; bit++) {
                if (_get_bit(blockers, bit + num_up_bits)) {
                    if (flag) {
                        mask |= chess::masks::lines[square - 8 * (bit + 1)][square];
                        flag = false;
                    }
                    bitboard_operations::set_1(board, square - 8 * (bit + 1));
                }
            }

            if (flag  and num_down_bits > 0) {
                mask |= chess::masks::lines[square - 8 * (num_down_bits + 1)][square];
            }


            flag = true;
            for (uint8_t bit = 0; bit < num_right_bits; bit++) {
                if (_get_bit(blockers, bit + num_up_bits + num_down_bits)) {
                    if (flag) {
                        mask |= chess::masks::lines[square + (bit + 1)][square];
                        flag = false;
                    }
                    bitboard_operations::set_1(board, square + (bit + 1));
                }
            }

            if (flag and num_right_bits > 0) {
                mask |= chess::masks::lines[square + (num_right_bits + 1)][square];
            }


            flag = true;
            for (uint8_t bit = 0; bit < num_left_bits; bit++) {
                if (_get_bit(blockers, bit + num_up_bits + num_down_bits + num_right_bits)) {
                    if (flag) {
                        mask |= chess::masks::lines[square - (bit + 1)][square];
                        flag = false;
                    }
                    bitboard_operations::set_1(board, square - (bit + 1));
                }
            }

            if (flag and (square % 8) != 0) {
                mask |= chess::masks::lines[square - (num_left_bits + 1)][square];
            }

            hash = get_rook_hash(board, square);
            masks[hash] = mask;
        }

        return masks;
    }

    static consteval std::array<std::array<Bitboard, 4096>, 64> get_primary_rook_masks(){
        std::array<std::array<Bitboard, 4096>, 64> masks{};
        for (uint8_t square = 0; square < 64; square++) {
            masks[square] = generate_primary_rook_masks(square);
        }
        return masks;
    }

    static constexpr Bitboard generate_secondary_rook_mask(uint8_t square) {
        Bitboard mask = 0;
        uint8_t num_up_bits = rook_up_bits[square];
        uint8_t num_down_bits = rook_down_bits[square];
        uint8_t num_right_bits = rook_right_bits[square];
        uint8_t num_left_bits = rook_left_bits[square];

        for (uint8_t i = 0; i < num_up_bits; i++){
            bitboard_operations::set_1(mask, square + 8 * (i + 1));
        }

        for (uint8_t i = 0; i < num_down_bits; i++){
            bitboard_operations::set_1(mask, square - 8 * (i + 1));
        }

        for (uint8_t i = 0; i < num_right_bits; i++){
            bitboard_operations::set_1(mask, square + (i + 1));
        }

        for (uint8_t i = 0; i < num_left_bits; i++){
            bitboard_operations::set_1(mask, square - (i + 1));
        }

        return mask;
    }

    static consteval std::array<Bitboard, 64> get_secondary_rook_masks(){
        std::array<Bitboard, 64> masks = {};
        for (uint8_t square = 0; square < 64; square++) {
            masks[square] = generate_secondary_rook_mask(square);
        }
        return masks;
    }



    constexpr std::array<std::array<Bitboard, 4096>, 64> primary_rook_masks = get_primary_rook_masks();
    constexpr std::array<Bitboard, 64> secondary_rook_masks = get_secondary_rook_masks();




}