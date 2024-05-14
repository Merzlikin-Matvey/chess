#pragma once

#include "headers/magic_numbers.hpp"
#include "headers/bitboard_lines.hpp"
#include "headers/bitboard_operations.hpp"
#include "headers/masks/masks_utils.hpp"
#include "headers/board.hpp"
#include "headers/constants.hpp"
#include "headers/masks/number_of_bits.hpp"
#include "headers/magic_numbers_constants.hpp"


namespace chess::masks {
    constexpr int get_vertical_pin_hash(Bitboard board, uint8_t square) {
        Bitboard magic_number = chess::magic_numbers::vertical_pin_magic_numbers[square];
        int num_bits = up_bits[square] + down_bits[square];
        return (board * magic_number) >> (64 - num_bits);
    }

     static constexpr std::array<Bitboard, 128> generate_rook_or_queen_vertical_pin_masks(uint8_t square) {
        std::array<Bitboard, 128> masks = {};
        Bitboard board, mask;
        uint8_t num_up_bits = up_bits[square];
        uint8_t num_down_bits = down_bits[square];
        int hash;
        bool flag;

        for (uint8_t blockers = 0; blockers < 128; blockers++) {
            board = 0;
            mask = 0;

            flag = true;
            for (int bit = 0; bit < num_up_bits; bit++) {
                if (_get_bit(blockers, bit)) {
                    if (flag) {
                        mask |= chess::masks::lines[square + 8 * (bit + 1)][square];
                        flag = false;
                    }
                    bitboard_operations::set_1(board, square + 8 * (bit + 1));
                }
            }

            flag = true;
            for (int bit = 0; bit < num_down_bits; bit++) {
                if (_get_bit(blockers, bit + num_up_bits)) {
                    if (flag) {
                        mask |= chess::masks::lines[square - 8 * (bit + 1)][square];
                        flag = false;
                    }
                    bitboard_operations::set_1(board, square - 8 * (bit + 1));
                }
            }

            hash = get_vertical_pin_hash(board, square);
            masks[hash] = mask;
        }
        return masks;
    }

    static consteval std::array<std::array<Bitboard, 128>, 64> get_rook_or_queen_vertical_pin_masks() {
        std::array<std::array<Bitboard, 128>, 64> masks = {};

        for (uint8_t square = 0; square < 64; square++) {
            masks[square] = generate_rook_or_queen_vertical_pin_masks(square);
        }

        return masks;
    }

    static constexpr std::array<Bitboard, 128> generate_opposite_vertical_pin_masks(uint8_t square) {
        std::array<Bitboard, 128> masks = {};
        Bitboard board, mask;
        uint8_t num_up_bits = up_bits[square];
        uint8_t num_down_bits = down_bits[square];
        int hash;
        int count = 0;

        for (uint8_t blockers = 0; blockers < 128; blockers++) {
            board = 0;
            mask = 0;

            count = 0;
            for (uint8_t bit = 0; bit < num_up_bits; bit++){
                if (_get_bit(blockers, bit)){
                    count++;
                    bitboard_operations::set_1(board, square + 8 * (bit + 1));
                }
            }

            if (count < 2){
                mask |= lines[56 + square % 8][square];
            }

            count = 0;
            for (uint8_t bit = 0; bit < num_down_bits; bit++){
                if (_get_bit(blockers, bit + num_up_bits)){
                    count++;
                    bitboard_operations::set_1(board, square - 8 * (bit + 1));
                }
            }

            if (count < 2){
                mask |= lines[square % 8][square];
            }


            hash = get_vertical_pin_hash(board, square);
            masks[hash] = mask;
        }
        return masks;
    }

    static consteval std::array<std::array<Bitboard, 128>, 64> get_opposite_vertical_pin_masks() {
        std::array<std::array<Bitboard, 128>, 64> masks = {};

        for (uint8_t square = 0; square < 64; square++) {
            masks[square] = generate_opposite_vertical_pin_masks(square);
        }

        return masks;
    }

    static constexpr std::array<Bitboard, 128> generate_vertical_teammate_pin_masks(uint8_t square) {
        std::array<Bitboard, 128> masks = {};
        Bitboard board, mask;
        uint8_t num_up_bits = up_bits[square];
        uint8_t num_down_bits = down_bits[square];
        int hash;
        int count = 0;

        for (uint8_t blockers = 0; blockers < 128; blockers++) {
            board = 0;
            mask = 0;

            count = 0;
            for (uint8_t bit = 0; bit < num_up_bits; bit++){
                if (_get_bit(blockers, bit)){
                    count++;
                    bitboard_operations::set_1(board, square + 8 * (bit + 1));
                }
            }

            if (count == 1){
                mask |= lines[56 + square % 8][square];
            }

            count = 0;
            for (uint8_t bit = 0; bit < num_down_bits; bit++){
                if (_get_bit(blockers, bit + num_up_bits)){
                    count++;
                    bitboard_operations::set_1(board, square - 8 * (bit + 1));
                }
            }

            if (count == 1){
                mask |= lines[square % 8][square];
            }

            hash = get_vertical_pin_hash(board, square);
            masks[hash] = mask;
        }
        return masks;
    }

    static consteval std::array<std::array<Bitboard, 128>, 64> get_teammate_vertical_pin_masks() {
        std::array<std::array<Bitboard, 128>, 64> masks = {};
        for (uint8_t square = 0; square < 64; square++) {
            masks[square] = generate_vertical_teammate_pin_masks(square);
        }
        return masks;
    }

    static constexpr Bitboard generate_secondary_vertical_pin_mask(uint8_t square) {
        Bitboard column = bitboard_operations::columns[square % 8];
        bitboard_operations::set_0(column, square);
        return column;
    }

    static consteval std::array<Bitboard, 64> get_secondary_vertical_pin_masks() {
        std::array<Bitboard, 64> masks = {};
        for (uint8_t square = 0; square < 64; square++) {
            masks[square] = generate_secondary_vertical_pin_mask(square);
        }
        return masks;
    }

    constexpr std::array<Bitboard, 64> secondary_vertical_pin_masks = get_secondary_vertical_pin_masks();
    constexpr std::array<std::array<Bitboard, 128>, 64> rook_or_queen_vertical_pin_masks = get_rook_or_queen_vertical_pin_masks();
    constexpr std::array<std::array<Bitboard, 128>, 64> opposite_vertical_pin_masks = get_opposite_vertical_pin_masks();
    constexpr std::array<std::array<Bitboard, 128>, 64> teammate_vertical_pin_masks = get_teammate_vertical_pin_masks();

    inline Bitboard get_vertical_pin_mask(Board& board, uint8_t square, uint8_t color) {
        int rook_or_queen_hash = get_vertical_pin_hash(secondary_vertical_pin_masks[square] & (
                board.piece_bitboards[!color][chess::Rook] | board.piece_bitboards[!color][chess::Queen]), square);
        Bitboard rook_or_queen = rook_or_queen_vertical_pin_masks[square][rook_or_queen_hash];

        int opposite_hash = get_vertical_pin_hash(board.side_bitboards[!color] & rook_or_queen, square);
        Bitboard opposite = rook_or_queen & opposite_vertical_pin_masks[square][opposite_hash];

        int teammate_hash = get_vertical_pin_hash(board.side_bitboards[color] & opposite, square);
        Bitboard teammate = opposite & teammate_vertical_pin_masks[square][teammate_hash];


        return  teammate;
    }
}