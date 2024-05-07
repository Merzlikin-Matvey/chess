#pragma once

#include "headers/magic_numbers.hpp"
#include "headers/bitboard_lines.hpp"
#include "headers/bitboard_operations.hpp"
#include "headers/masks/masks_utils.hpp"
#include "headers/board.hpp"
#include "headers/constants.hpp"
#include "headers/masks/number_of_bits.hpp"

namespace chess::masks {
    constexpr int get_down_right_pin_hash(Bitboard board, uint8_t square) {
        Bitboard magic_number = magic_numbers::down_right_pin_magic_numbers[square];
        int num_bits = down_right_bits[square] + up_left_bits[square];
        if (num_bits == 0){
            return 0;
        }
        return (board * magic_number) >> (64 - num_bits);
    }

    static constexpr std::array<Bitboard, 128> generate_bishop_or_queen_down_right_pin_masks(uint8_t square) {
        std::array<Bitboard, 128> masks = {};
        Bitboard board, mask;
        uint8_t num_down_right_bits = down_right_bits[square];
        uint8_t num_up_left_bits = up_left_bits[square];
        uint16_t num_of_permutations = 1 << (num_down_right_bits + num_up_left_bits);
        int hash;
        bool flag;

        for (uint16_t blockers = 0; blockers < num_of_permutations; blockers++) {
            board = 0;
            mask = 0;

            flag = true;
            for (int bit = 0; bit < num_up_left_bits; bit++) {
                if (_get_bit(blockers, bit)) {
                    if (flag) {
                        mask |= lines[square + 7 * (bit + 1)][square];
                        flag = false;
                    }
                    bitboard_operations::set_1(board, square + 7 * (bit + 1));
                }
            }

            flag = true;
            for (int bit = 0; bit < num_down_right_bits; bit++) {
                if (_get_bit(blockers, bit + num_up_left_bits)) {
                    if (flag) {
                        mask |= lines[square - 7 * (bit + 1)][square];
                        flag = false;
                    }
                    bitboard_operations::set_1(board, square - 7 * (bit + 1));
                }
            }

            hash = get_down_right_pin_hash(board, square);
            masks[hash] = mask;
        }
        return masks;
    }

    static constexpr std::array<std::array<Bitboard, 128>, 64> get_bishop_or_queen_down_right_pin_masks() {
        std::array<std::array<Bitboard, 128>, 64> masks = {};
        for (uint8_t square = 0; square < 64; square++) {
            masks[square] = generate_bishop_or_queen_down_right_pin_masks(square);
        }
        return masks;
    }

    static constexpr std::array<Bitboard, 128> generate_opposite_down_right_pin_masks(uint8_t square){
        std::array<Bitboard, 128> masks = {};
        Bitboard board, mask;
        uint8_t num_down_right_bits = down_right_bits[square];
        uint8_t num_up_left_bits = up_left_bits[square];
        uint16_t num_of_permutations = 1 << (num_down_right_bits + num_up_left_bits);
        int hash;
        int count;

        for (uint16_t blockers = 0; blockers < num_of_permutations; blockers++) {
            board = 0;
            mask = 0;

            count = 0;
            for (int bit = 0; bit < num_up_left_bits; bit++) {
                if (_get_bit(blockers, bit)) {
                    mask |= lines[square + 7 * (bit + 1)][square];
                    bitboard_operations::set_1(board, square + 7 * (bit + 1));
                    count++;
                }
            }

            if (count < 2) {
                mask |= lines[square + 7 * std::max(0, (std::min(square % 8, 8 - square / 8) - 1))][square];
            }


            count = 0;
            for (int bit = 0; bit < num_down_right_bits; bit++) {
                if (_get_bit(blockers, bit + num_up_left_bits)) {
                    mask |= lines[square - 7 * (bit + 1)][square];
                    bitboard_operations::set_1(board, square - 7 * (bit + 1));
                    count++;
                }
            }

            if (count < 2) {
                mask |= lines[square - 7 * std::max(0, (std::min(8 - square % 8, square / 8) - 1))][square];
            }

            hash = get_down_right_pin_hash(board, square);
            masks[hash] = mask;
        }

        return masks;
    }

    static consteval std::array<std::array<Bitboard, 128>, 64> get_opposite_down_right_pin_masks() {
        std::array<std::array<Bitboard, 128>, 64> masks = {};

        for (uint8_t square = 0; square < 64; square++) {
            masks[square] = generate_opposite_down_right_pin_masks(square);
        }

        return masks;
    }

    static constexpr std::array<Bitboard, 128> generate_teammate_down_right_pin_masks(int square) {
        std::array<Bitboard, 128> masks = {};
        Bitboard board, mask;
        uint8_t num_down_right_bits = down_right_bits[square];
        uint8_t num_up_left_bits = up_left_bits[square];
        uint16_t num_of_permutations = 1 << (num_down_right_bits + num_up_left_bits);
        int hash;
        int count;

        for (uint16_t blockers = 0; blockers < num_of_permutations; blockers++) {
            board = 0;
            mask = 0;

            count = 0;
            for (int bit = 0; bit < num_up_left_bits; bit++) {
                if (_get_bit(blockers, bit)) {
                    bitboard_operations::set_1(board, square + 7 * (bit + 1));
                    count++;
                }
            }

            if (count == 1) {
                mask |= lines[square + 7 * std::max(0, (std::min(square % 8, 8 - square / 8) - 1))][square];
            }

            count = 0;
            for (int bit = 0; bit < num_down_right_bits; bit++) {
                if (_get_bit(blockers, bit + num_up_left_bits)) {
                    bitboard_operations::set_1(board, square - 7 * (bit + 1));
                    count++;
                }
            }

            if (count == 1) {
                mask |= lines[square - 7 * std::max(0, (std::min(8 - square % 8, square / 8) - 1))][square];

            }

            hash = get_down_right_pin_hash(board, square);
            masks[hash] = mask;
        }

        return masks;
    }

    static consteval std::array<std::array<Bitboard, 128>, 64> get_teammate_down_right_pin_masks() {
        std::array<std::array<Bitboard, 128>, 64> masks = {};

        for (uint8_t square = 0; square < 64; square++) {
            masks[square] = generate_teammate_down_right_pin_masks(square);
        }

        return masks;
    }

    static constexpr Bitboard generate_secondary_down_right_pin_mask(uint8_t square) {
        Bitboard mask = 0;
        mask |= lines[square + 7 * std::min(0, (std::min(square % 8, 8 - square / 8 - 1)))][square];
        mask |= lines[square - 7 * std::max(0, (std::min(8 - square % 8, square / 8)))][square];
        return mask;
    }

    static consteval std::array<Bitboard, 64> get_secondary_down_right_pin_masks() {
        std::array<Bitboard, 64> masks = {};
        for (uint8_t square = 0; square < 64; square++) {
            masks[square] = generate_secondary_down_right_pin_mask(square);
        }
        return masks;
    }

    constexpr std::array<Bitboard, 64> secondary_down_right_pin_masks = get_secondary_down_right_pin_masks();
    constexpr std::array<std::array<Bitboard, 128>, 64> teammate_down_right_pin_masks = get_teammate_down_right_pin_masks();
    constexpr std::array<std::array<Bitboard, 128>, 64> opposite_down_right_pin_masks = get_opposite_down_right_pin_masks();
    constexpr std::array<std::array<Bitboard, 128>, 64> bishop_or_queen_down_right_pin_masks = get_bishop_or_queen_down_right_pin_masks();

    Bitboard get_down_right_pin_mask(Board& board, uint8_t square, uint8_t color) {
        int bishop_or_queen_hash = get_down_right_pin_hash(secondary_down_right_pin_masks[square] & (
                board.piece_bitboards[!color][chess::Bishop] | board.piece_bitboards[!color][chess::Queen]), square);
        Bitboard bishop_or_queen = bishop_or_queen_down_right_pin_masks[square][bishop_or_queen_hash];

        int opposite_hash = get_down_right_pin_hash(board.side_bitboards[!color] & secondary_down_right_pin_masks[square], square);
        Bitboard opposite = bishop_or_queen & opposite_down_right_pin_masks[square][opposite_hash];

        int teammate_hash = get_down_right_pin_hash(board.side_bitboards[color], square);
        Bitboard teammate = opposite & teammate_down_right_pin_masks[square][teammate_hash];

        return teammate;
    }

}