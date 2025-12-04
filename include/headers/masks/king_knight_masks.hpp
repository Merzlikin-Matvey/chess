#pragma once

#include <array>
#include <memory>

typedef uint64_t Bitboard;

namespace chess::masks {
    static consteval std::array<Bitboard, 64> get_knight_masks() {
        std::array<Bitboard, 64> masks{};
        for (int i = 0; i < 64; i++) {
            Bitboard mask = 0;
            if (i % 8 < 7) {
                if (i / 8 < 6) {
                    bitboard_operations::set_1(mask, i + 17);
                }
                if (i / 8 > 1) {
                    bitboard_operations::set_1(mask, i - 15);
                }
            }
            if (i % 8 < 6) {
                if (i / 8 < 7) {
                    bitboard_operations::set_1(mask, i + 10);
                }
                if (i / 8 > 0) {
                    bitboard_operations::set_1(mask, i - 6);
                }
            }
            if (i % 8 > 1) {
                if (i / 8 < 7) {
                    bitboard_operations::set_1(mask, i + 6);
                }
                if (i / 8 > 0) {
                    bitboard_operations::set_1(mask, i - 10);
                }
            }
            if (i % 8 > 0) {
                if (i / 8 < 6) {
                    bitboard_operations::set_1(mask, i + 15);
                }
                if (i / 8 > 1) {
                    bitboard_operations::set_1(mask, i - 17);
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

} // namespace chess::masks
