#pragma once

#include <memory>
#include <array>
#include <vector>

#include "headers/zobrist.hpp"

typedef uint64_t Bitboard;

namespace chess {

    class Board {
    public:
        Board(std::array<std::array<Bitboard, 6>, 2> board);
        Board();

        Bitboard _all;
        std::array<std::array<Bitboard, 6>, 2> _piece_bitboards{};
        std::array<Bitboard, 2> _side_bitboards{};
        std::array<Bitboard, 2> _inversion_side_bitboards{};

        std::vector<zobrist::ZobristHash> _hashes;

        bool white_turn = true;
        bool w_l_castling = true;
        bool w_s_castling = true;
        bool b_l_castling = true;
        bool b_s_castling = true;


        void add_hash_to_history(zobrist::ZobristHash hash);
        void add_hash_to_history();
        void clear_history();
        uint8_t get_num_of_repetitions();

        bool operator==(const Board &board) const;
        bool operator!=(const Board &board) const;

        int8_t getPieceType(const chess::Board &board, uint8_t x, uint8_t y);

    };

    std::ostream& operator<<(std::ostream &ostream, chess::Board board);
}