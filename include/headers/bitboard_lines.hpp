#pragma once

#include <array>
#include <memory>

typedef uint64_t Bitboard;

namespace masks {
    static constexpr Bitboard _get_line(uint8_t x, uint8_t y) {
        Bitboard mask = 0;
        if (x == y) {
            return mask;
        } else if (x / 8 == y / 8) {
            if (x > y) {
                for (int i = y + 1; i <= x; i++) {
                    bitboard_operations::set_1(mask, i);
                }
            } else {
                for (int i = x; i <= y - 1; i++) {
                    bitboard_operations::set_1(mask, i);
                }
            }
            return mask;
        } else if (x % 8 == y % 8) {
            if (x > y) {
                for (int i = y + 8; i <= x; i += 8) {
                    bitboard_operations::set_1(mask, i);
                }
            } else {
                for (int i = x; i <= y - 8; i += 8) {
                    bitboard_operations::set_1(mask, i);
                }
            }
            return mask;
        } else if ((x % 8 - y % 8) == (x / 8 - y / 8)) {
            if (x > y) {
                for (int i = y + 9; i <= x; i += 9) {
                    bitboard_operations::set_1(mask, i);
                }
            } else {
                for (int i = x; i <= y - 9; i += 9) {
                    bitboard_operations::set_1(mask, i);
                }
            }
            return mask;
        } else if ((x % 8 - y % 8) == (y / 8 - x / 8)) {
            if (x > y) {
                for (int i = y + 7; i <= x; i += 7) {
                    bitboard_operations::set_1(mask, i);
                }
            } else {
                for (int i = x; i <= y - 7; i += 7) {
                    bitboard_operations::set_1(mask, i);
                }
            }
            return mask;
        } else {
            bitboard_operations::set_1(mask, x);
            return mask;

            return mask;
        }
    }

    static consteval std::array<std::array<Bitboard, 64>, 64> get_lines(){
        std::array<std::array<Bitboard, 64>, 64> masks{};
        for (int i = 0; i < 64; i++) {
            for (int j = 0; j < 64; j++) {
                masks[i][j] = _get_line(i, j);
            }
        }
        return masks;
    }
}
