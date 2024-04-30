#pragma once

#include <memory>
#include <cstdint>

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

    static constexpr uint8_t bitScanForward(Bitboard bb) {
    #if defined(__GNUC__) || defined(__clang__)
            return __builtin_ffsll(bb) - 1;
    #elif defined(_MSC_VER)
            unsigned long index;
        _BitScanForward64(&index, bb);
        return index;
    #else
    #error "Unsupported compiler"
    #endif
    }

    static constexpr uint8_t bitScanReverse(Bitboard bb) {
    #if defined(__GNUC__) || defined(__clang__)
            return 63 - __builtin_clzll(bb);
    #elif defined(_MSC_VER)
            unsigned long index;
        _BitScanReverse64(&index, bb);
        return index;
    #else
    #error "Unsupported compiler"
    #endif
    }

    static consteval std::array<Bitboard, 8> get_rows(){
        std::array<Bitboard, 8> rows{};
        for (int i = 0; i < 8; i++){
            rows[i] = 0;
            for (int j = 0; j < 8; j++){
                rows[i] |= (1ull << (i * 8 + j));
            }
        }
        return rows;
    }

    static consteval std::array<Bitboard, 8> get_inverse_rows(){
        std::array<Bitboard, 8> rows{};
        for (int i = 0; i < 8; i++){
            rows[i] = 0;
            for (int j = 0; j < 8; j++){
                rows[i] |= (1ull << (i * 8 + j));
            }
            rows[i] = ~rows[i];
        }
        return rows;
    }



    static consteval std::array<Bitboard, 8> get_columns(){
        std::array<Bitboard, 8> columns{};
        for (int i = 0; i < 8; i++){
            columns[i] = 0;
            for (int j = 0; j < 8; j++){
                columns[i] |= (1ull << (j * 8 + i));
            }
        }
        return columns;
    }

    static consteval std::array<Bitboard, 8> get_inverse_columns(){
        std::array<Bitboard, 8> columns{};
        for (int i = 0; i < 8; i++){
            columns[i] = 0;
            for (int j = 0; j < 8; j++){
                columns[i] |= (1ull << (j * 8 + i));
            }
            columns[i] = ~columns[i];
        }
        return columns;
    }







}

