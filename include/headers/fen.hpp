#pragma once

#include <array>
#include <memory>

typedef uint64_t Bitboard;

namespace chess {
    std::array<std::array<Bitboard, 6>, 2> convert_fen_to_bitboards(std::string fen);
    std::array<std::array<Bitboard, 6>, 2> convert_default_positions();

    std::string bitboards_to_fen(std::array<std::array<Bitboard, 6>, 2> piece_bitboards);
} // namespace chess
