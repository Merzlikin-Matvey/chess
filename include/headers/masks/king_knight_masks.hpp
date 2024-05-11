#pragma once

#include <array>
#include <memory>

typedef uint64_t Bitboard;

namespace chess::masks {
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

    static constexpr std::array<Bitboard, 64> knight_masks = get_knight_masks();
    static constexpr std::array<Bitboard, 64> king_masks = get_king_masks();

    Bitboard get_knight_mask(uint8_t square) {
        return knight_masks[square];
    }

    Bitboard get_king_mask(uint8_t square) {
        return king_masks[square];
    }
}