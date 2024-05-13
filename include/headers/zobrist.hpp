#pragma once

#include <memory>
#include <array>
#include <cstdint>

namespace chess {
    class Board;
}

namespace zobrist {
    static constexpr uint64_t Seed = 0x98f107;
    static constexpr uint64_t Multiplier = 0x71abc9;
    static constexpr uint64_t Summand = 0xff1b3f;

    static constexpr uint64_t next_random(uint64_t previous) {
        return (previous * zobrist::Multiplier + zobrist::Summand);
    }

    static constexpr std::array<std::array<std::array<uint64_t, 6>, 2>, 64> generate_constants() {
        std::array<std::array<std::array<uint64_t, 6>, 2>, 64> constants{};
        uint64_t random = zobrist::Seed;
        for (int i = 0; i < 64; i++) {
            for (int j = 0; j < 2; j++) {
                for (int k = 0; k < 6; k++) {
                    constants[i][j][k] = random;
                    random = zobrist::next_random(random);
                }
            }
        }
        return constants;
    }
    static constexpr std::array<std::array<std::array<uint64_t, 6>, 2>, 64> Constants = generate_constants();
    static constexpr uint64_t BlackMove = next_random(Constants[63][1][5]);
    static constexpr uint64_t WhiteLongCastling = next_random(BlackMove);
    static constexpr uint64_t WhiteShortCastling = next_random(WhiteLongCastling);
    static constexpr uint64_t BlackLongCastling = next_random(WhiteShortCastling);
    static constexpr uint64_t BlackShortCastling = next_random(BlackLongCastling);


    class ZobristHash{
    public:
        ZobristHash(chess::Board board);

        uint64_t hash;

        bool operator==(const ZobristHash& other) const {
            return this->hash == other.hash;
        }

        bool operator!=(const ZobristHash& other) const {
            return this->hash != other.hash;
        }

        bool operator<(const ZobristHash& other) const {
            return this->hash < other.hash;
        }

        bool operator>(const ZobristHash& other) const {
            return this->hash > other.hash;
        }

        bool operator<=(const ZobristHash& other) const {
            return this->hash <= other.hash;
        }

        bool operator>=(const ZobristHash& other) const {
            return this->hash >= other.hash;
        }

        ZobristHash operator^(const uint64_t& other) const {
            ZobristHash result = *this;
            result.hash = result.hash ^ other;
            return result;
        }

        ZobristHash operator^(const ZobristHash& other) const {
            ZobristHash result = *this;
            result.hash = result.hash ^ other.hash;
            return result;
        }
    };

    std::ostream& operator<<(std::ostream &ostream, zobrist::ZobristHash hash);
}