#pragma once

#include <memory>
#include <array>


typedef uint64_t Bitboard;

namespace chess {

    class Board {
    public:
        Board(std::array<std::array<Bitboard, 6>, 2> board);

        std::array<std::array<Bitboard, 6>, 2> _piece_bitboards{};
        std::array<Bitboard, 2> _side_bitboards{};
        std::array<Bitboard, 2> _inversion_side_bitboards{};
        Bitboard _all;

        bool operator==(const Board &board) const;

        bool operator!=(const Board &board) const;

        int8_t getPieceType(const chess::Board &board, uint8_t x, uint8_t y);
    }
}