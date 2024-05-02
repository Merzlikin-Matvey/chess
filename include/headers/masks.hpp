#pragma once

#include <array>
#include <memory>
#include <string>
#include <map>
#include <iostream>
#include <cmath>


#include "headers/board.hpp"
#include "headers/bitboard_operations.hpp"
#include "headers/magic_numbers.hpp"


typedef uint64_t Bitboard;

namespace masks {

    bool static constexpr _get_bit(int num, int bit) {
        return (num & (1 << bit)) != 0;
    }

    static constexpr std::array<std::array<Bitboard, 1024>, 64> generate_rook_masks(){
        std::array<std::array<Bitboard, 1024>, 64> masks{};
        std::array<Bitboard, 64> magic_numbers = chess::magic_numbers::rook_magic_numbers;
        Bitboard magic;


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

    constexpr auto rook_masks = generate_rook_masks();

}



