#pragma once

#include <memory>

typedef uint64_t Bitboard;

namespace bitboard_operations {
    static constexpr void set_1(Bitboard &bb, uint8_t square) {
        bb = bb | (1ull << square);
    }
    static constexpr void set_0(Bitboard &bb, uint8_t square) {
        bb = bb & (~(1ull << square));
    }

    static constexpr bool get_bit(Bitboard bb, uint8_t square) {
        return (bb & (1ull << square));
    }

    static constexpr uint8_t count_1(Bitboard bb) {
    #if defined(__GNUC__) || defined(__clang__)
            return __builtin_popcountll(bb);
    #elif defined(_MSC_VER)
            return _mm_popcnt_u64(bb);
    #else
    #error "Unsupported compiler"
    #endif
    }

}

