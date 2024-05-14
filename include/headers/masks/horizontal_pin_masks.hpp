#pragma once

#include "headers/magic_numbers.hpp"
#include "headers/bitboard_lines.hpp"
#include "headers/bitboard_operations.hpp"
#include "headers/masks/masks_utils.hpp"
#include "headers/board.hpp"
#include "headers/constants.hpp"
#include "headers/masks/number_of_bits.hpp"


namespace chess::masks {
    constexpr int get_horizontal_pin_hash(Bitboard board, uint8_t square) {
        Bitboard magic_number = chess::magic_numbers::horizontal_pin_magic_numbers[square];
        int num_bits = right_bits[square] + left_bits[square];
        return (board * magic_number) >> (64 - num_bits);
    }

    static constexpr std::array<Bitboard, 128> generate_rook_or_queen_horizontal_pin_masks(uint8_t square) {
        std::array<Bitboard, 128> masks = {};
        Bitboard board, mask;
        uint8_t num_right_bits = right_bits[square];
        uint8_t num_left_bits = left_bits[square];
        int hash;
        bool flag;

        for (uint8_t blockers = 0; blockers < 128; blockers++) {
            board = 0;
            mask = 0;

            flag = true;
            for (int bit = 0; bit < num_right_bits; bit++) {
                if (_get_bit(blockers, bit)) {
                    if (flag) {
                        mask |= chess::masks::lines[square + (bit + 1)][square];
                        flag = false;
                    }
                    bitboard_operations::set_1(board, square + (bit + 1));
                }
            }

            flag = true;
            for (int bit = 0; bit < num_left_bits; bit++) {
                if (_get_bit(blockers, bit + num_right_bits)) {
                    if (flag) {
                        mask |= chess::masks::lines[square - (bit + 1)][square];
                        flag = false;
                    }
                    bitboard_operations::set_1(board, square - (bit + 1));
                }
            }

            hash = get_horizontal_pin_hash(board, square);
            masks[hash] = mask;
        }

        return masks;
    }

    static consteval std::array<std::array<Bitboard, 128>, 64> get_rook_or_queen_horizontal_pin_masks() {
        std::array<std::array<Bitboard, 128>, 64> masks = {};

        for (uint8_t square = 0; square < 64; square++) {
            masks[square] = generate_rook_or_queen_horizontal_pin_masks(square);
        }

        return masks;
    }

    static constexpr std::array<Bitboard, 128> generate_opposite_horizontal_pin_masks(uint8_t square) {
        std::array<Bitboard, 128> masks = {};
        Bitboard board, mask;
        uint8_t num_right_bits = right_bits[square];
        uint8_t num_left_bits = left_bits[square];
        int hash;
        int count = 0;

        for (uint8_t blockers = 0; blockers < 128; blockers++) {
            board = 0;
            mask = 0;

            count = 0;
            for (uint8_t bit = 0; bit < num_right_bits; bit++){
                if (_get_bit(blockers, bit)){
                    count++;
                    bitboard_operations::set_1(board, square + (bit + 1));
                }
            }

            if (count < 2){
                mask |= lines[(square / 8) * 8 + 7][square];
            }

            count = 0;
            for (uint8_t bit = 0; bit < num_left_bits; bit++){
                if (_get_bit(blockers, bit + num_right_bits)){
                    count++;
                    bitboard_operations::set_1(board, square - (bit + 1));
                }
            }

            if (count < 2){
                mask |= lines[(square / 8) * 8][square];
            }



            hash = get_horizontal_pin_hash(board, square);

            masks[hash] = mask;
        }

        return masks;
    }

    static consteval std::array<std::array<Bitboard, 128>, 64> get_opposite_horizontal_pin_masks() {
        std::array<std::array<Bitboard, 128>, 64> masks = {};

        for (uint8_t square = 0; square < 64; square++) {
            masks[square] = generate_opposite_horizontal_pin_masks(square);
        }

        return masks;
    }

    static constexpr std::array<Bitboard, 128> generate_teammate_horizontal_pin_masks(uint8_t square) {
        std::array<Bitboard, 128> masks = {};
        Bitboard board, mask;
        uint8_t num_right_bits = right_bits[square];
        uint8_t num_left_bits = left_bits[square];
        int hash;
        int count = 0;

        for (uint8_t blockers = 0; blockers < 128; blockers++) {
            board = 0;
            mask = 0;

            count = 0;
            for (uint8_t bit = 0; bit < num_right_bits; bit++) {
                if (_get_bit(blockers, bit)) {
                    count++;
                    bitboard_operations::set_1(board, square + (bit + 1));
                }
            }

            if (count == 1) {
                mask |= lines[(square / 8) * 8 + 7][square];
            }

            count = 0;
            for (uint8_t bit = 0; bit < num_left_bits; bit++) {
                if (_get_bit(blockers, bit + num_right_bits)) {
                    count++;
                    bitboard_operations::set_1(board, square - (bit + 1));
                }
            }

            if (count == 1) {
                mask |= lines[(square / 8) * 8][square];
            }

            hash = get_horizontal_pin_hash(board, square);
            masks[hash] = mask;
        }

        return masks;
    }

    static consteval std::array<std::array<Bitboard, 128>, 64> get_horizontal_teammate_pin_masks() {
        std::array<std::array<Bitboard, 128>, 64> masks = {};

        for (uint8_t square = 0; square < 64; square++) {
            masks[square] = generate_teammate_horizontal_pin_masks(square);
        }

        return masks;
    }

    static constexpr Bitboard generate_secondary_horizontal_pin_mask(uint8_t square) {
        Bitboard mask = 0;
        uint8_t num_right_bits = right_bits[square];
        uint8_t num_left_bits = left_bits[square];

        for (uint8_t i = 0; i < num_right_bits; i++) {
            bitboard_operations::set_1(mask, square + (i + 1));
        }

        for (uint8_t i = 0; i < num_left_bits; i++) {
            bitboard_operations::set_1(mask, square - (i + 1));
        }



        return mask;
    }

    static  consteval  std::array<Bitboard, 64> get_secondary_horizontal_pin_masks() {
        std::array<Bitboard, 64> masks = {};

        for (uint8_t square = 0; square < 64; square++) {
            masks[square] = generate_secondary_horizontal_pin_mask(square);
        }

        return masks;
    }

    constexpr std::array<Bitboard, 64> secondary_horizontal_pin_masks = get_secondary_horizontal_pin_masks();
    constexpr std::array<std::array<Bitboard, 128>, 64> rook_or_queen_horizontal_pin_masks = get_rook_or_queen_horizontal_pin_masks();
    constexpr std::array<std::array<Bitboard, 128>, 64> opposite_horizontal_pin_masks = get_opposite_horizontal_pin_masks();
    constexpr std::array<std::array<Bitboard, 128>, 64> teammate_horizontal_pin_masks = get_horizontal_teammate_pin_masks();

    inline Bitboard get_horizontal_pin_mask(Board& board, uint8_t square, uint8_t color) {
        int rook_or_queen_hash = get_horizontal_pin_hash(secondary_horizontal_pin_masks[square] & (
                board.piece_bitboards[!color][chess::Rook] | board.piece_bitboards[!color][chess::Queen]), square);
        Bitboard rook_or_queen = rook_or_queen_horizontal_pin_masks[square][rook_or_queen_hash];

        int opposite_hash = get_horizontal_pin_hash(board.side_bitboards[!color] & rook_or_queen, square);
        Bitboard opposite = rook_or_queen & opposite_horizontal_pin_masks[square][opposite_hash];

        int teammate_hash = get_horizontal_pin_hash(board.side_bitboards[color] & opposite, square);
        Bitboard teammate = opposite & teammate_horizontal_pin_masks[square][teammate_hash];

        return teammate;
    }

}