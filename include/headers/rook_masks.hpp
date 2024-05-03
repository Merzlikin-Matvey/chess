#pragma once

#include <array>
#include <memory>
#include <string>
#include <map>
#include <iostream>
#include <cmath>


#include "headers/board.hpp"
#include "headers/magic_numbers.hpp"
#include "headers/bitboard_lines.hpp"


typedef uint64_t Bitboard;

namespace chess::masks {
    static constexpr bool _get_bit(int n, int i) {
        return (n & (1 << i)) != 0;
    }
    static constexpr std::array<uint8_t, 64> up_bits = {
            6, 6, 6, 6, 6, 6, 6, 6,
            5, 5, 5, 5, 5, 5, 5, 5,
            4, 4, 4, 4, 4, 4, 4, 4,
            3, 3, 3, 3, 3, 3, 3, 3,
            2, 2, 2, 2, 2, 2, 2, 2,
            1, 1, 1, 1, 1, 1, 1, 1,
            0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0
    };

    static constexpr std::array<uint8_t, 64> down_bits {
            0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0,
            1, 1, 1, 1, 1, 1, 1, 1,
            2, 2, 2, 2, 2, 2, 2, 2,
            3, 3, 3, 3, 3, 3, 3, 3,
            4, 4, 4, 4, 4, 4, 4, 4,
            5, 5, 5, 5, 5, 5, 5, 5,
            6, 6, 6, 6, 6, 6, 6, 6,
    };

    static constexpr std::array<uint8_t, 64> right_bits {
            6, 5, 4, 3, 2, 1, 0, 0,
            6, 5, 4, 3, 2, 1, 0, 0,
            6, 5, 4, 3, 2, 1, 0, 0,
            6, 5, 4, 3, 2, 1, 0, 0,
            6, 5, 4, 3, 2, 1, 0, 0,
            6, 5, 4, 3, 2, 1, 0, 0,
            6, 5, 4, 3, 2, 1, 0, 0,
            6, 5, 4, 3, 2, 1, 0, 0
    };

    static constexpr std::array<uint8_t, 64> left_bits {
        0, 0, 1, 2, 3, 4, 5, 6,
        0, 0, 1, 2, 3, 4, 5, 6,
        0, 0, 1, 2, 3, 4, 5, 6,
        0, 0, 1, 2, 3, 4, 5, 6,
        0, 0, 1, 2, 3, 4, 5, 6,
        0, 0, 1, 2, 3, 4, 5, 6,
        0, 0, 1, 2, 3, 4, 5, 6,
        0, 0, 1, 2, 3, 4, 5, 6
    };

     int get_rook_hash(Bitboard mask, uint8_t position){
        Bitboard magic_number = chess::magic_numbers::rook_magic_numbers[position];
        int num_bits = up_bits[position] + down_bits[position] + right_bits[position] + left_bits[position];
        return (mask * magic_number) >> (64 - num_bits);
    }


    int _pow2(uint8_t num){
        return 1 << num;
    }


    std::array<std::array<Bitboard, 4096>, 64> generate_rook_masks(){
        std::array<std::array<Bitboard, 4096>, 64> masks{};
        uint8_t num_up_bits, num_down_bits, num_right_bits, num_left_bits, num_bits;
        int hash;
        bool flag;

        for (int position = 0; position < 64; position++){
            num_up_bits = up_bits[position];
            num_down_bits = down_bits[position];
            num_right_bits = right_bits[position];
            num_left_bits = left_bits[position];
            num_bits = num_up_bits + num_down_bits + num_right_bits + num_left_bits;

            for (int blockers = 0; blockers < _pow2(num_bits); blockers++){
                Bitboard board = 0, mask = 0;
                flag = true;
                for (uint8_t bit = 0; bit < num_up_bits; bit++){
                   if (_get_bit(blockers, bit)) {
                       if (flag) {
                           flag = false;
                           mask |= chess::masks::lines[position + 8 * (bit + 1)][position];
                       }
                       bitboard_operations::set_1(board, position + 8 * (bit + 1));
                   }
               }
               if (flag and (position + 8 * (num_up_bits + 1)) < 64) {
                   mask |= chess::masks::lines[position + 8 * (num_up_bits + 1)][position];
               }

               flag = true;
               for (uint8_t bit = 0; bit < num_down_bits; bit++){
                   if (_get_bit(blockers, bit + num_up_bits)) {
                       if (flag) {
                           flag = false;
                           mask |= chess::masks::lines[position - 8 * (bit + 1)][position];
                       }
                       bitboard_operations::set_1(board, position - 8 * (bit + 1));
                   }
               }

               if (flag and (position - 8 * (num_down_bits + 1)) >= 0) {
                   mask |= chess::masks::lines[position - 8 * (num_down_bits + 1)][position];
               }

               flag = true;
               for (uint8_t bit = 0; bit < num_right_bits; bit++){
                    if (_get_bit(blockers, bit + num_up_bits + num_down_bits)) {
                        if (flag) {
                            flag = false;
                            mask |= chess::masks::lines[position + (bit + 1)][position];
                        }
                        bitboard_operations::set_1(board, position + (bit + 1));
                    }
               }

               if (flag and (position % 8) != 7) {
                    mask |= chess::masks::lines[position + (num_right_bits + 1)][position];
               }

               flag = true;
               for (uint8_t bit = 0; bit < num_left_bits; bit++){
                    if (_get_bit(blockers, bit + num_up_bits + num_down_bits + num_right_bits)) {
                        if (flag) {
                            flag = false;
                            mask |= chess::masks::lines[position - (bit + 1)][position];
                        }
                        bitboard_operations::set_1(board, position - (bit + 1));
                    }
               }

               if (flag and position % 8 > 0) {
                   mask |= chess::masks::lines[position - (num_left_bits + 1)][position];
               }

               hash = get_rook_hash(board, position);
               masks[position][hash] = mask;





            }
        }
        return masks;
    }

    // static constexpr std::array<std::array<Bitboard, 4096>, 64> rook_masks = generate_rook_masks();
}