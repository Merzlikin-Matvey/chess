#pragma once

#include <memory>
#include <array>
#include <vector>

#include "headers/zobrist.hpp"
#include "headers/move.hpp"

typedef uint64_t Bitboard;

namespace chess {

    class Board {
    public:
        Board(std::array<std::array<Bitboard, 6>, 2> board);
        Board(std::string fen);
        Board();

        Bitboard all;
        std::array<std::array<Bitboard, 6>, 2> piece_bitboards{};
        std::array<Bitboard, 2> side_bitboards;

        std::vector<zobrist::ZobristHash> _hashes;

        bool white_turn = true;
        bool w_l_castling = true;
        bool w_s_castling = true;
        bool b_l_castling = true;
        bool b_s_castling = true;

        MoveArray& legal_moves = *new MoveArray();


        void add_hash_to_history(zobrist::ZobristHash hash);
        void add_hash_to_history();
        void clear_history();
        uint8_t get_num_of_repetitions();

        void move(Move move);

        MoveArray& get_legal_moves();

        void pawn_mask_to_moves(Bitboard mask, int delta, MoveArray* moves);
        void mask_to_moves(Bitboard mask, MoveArray* moves);

        bool operator==(const Board &board) const;
        bool operator!=(const Board &board) const;

        int8_t get_piece_type(const chess::Board &board, uint8_t x, uint8_t y);
        int8_t get_piece_type(const chess::Board &board, uint8_t x);

    };

    std::ostream& operator<<(std::ostream &ostream, chess::Board board);
    void print_bitboard(Bitboard bitboard);
}