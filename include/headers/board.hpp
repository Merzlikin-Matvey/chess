#pragma once

#include <memory>
#include <array>
#include <vector>

#include "headers/zobrist.hpp"
#include "headers/move.hpp"

typedef uint64_t Bitboard;

namespace chess {

    struct PositionState {
        uint8_t  captured_type = 255;
        uint8_t  captured_side = 255;
        int8_t   prev_en_passant = -1;
        uint16_t prev_halfmove = 0;
        bool     prev_w_l_castling = false;
        bool     prev_w_s_castling = false;
        bool     prev_b_l_castling = false;
        bool     prev_b_s_castling = false;
    };

    class Board {
    public:
        Board(std::array<std::array<Bitboard, 6>, 2> board);
        Board(std::string fen);
        Board();

        ~Board() {}

        Board(const Board& other)
                : all(other.all),
                  piece_bitboards(other.piece_bitboards),
                  side_bitboards(other.side_bitboards),
                  hashes(other.hashes),
                  white_turn(other.white_turn),
                  w_l_castling(other.w_l_castling),
                  w_s_castling(other.w_s_castling),
                  b_l_castling(other.b_l_castling),
                  b_s_castling(other.b_s_castling),
                  en_passant_square(other.en_passant_square),
                  halfmove_clock(other.halfmove_clock),
                  num_of_moves(other.num_of_moves),
                  legal_moves(other.legal_moves),
                  move_history(other.move_history) {
        }

        Board& operator=(const Board& other);

        Bitboard all;
        std::array<std::array<Bitboard, 6>, 2> piece_bitboards{};
        std::array<Bitboard, 2> side_bitboards;

        std::vector<zobrist::ZobristHash> hashes;

        bool white_turn = true;
        bool w_l_castling = false;
        bool w_s_castling = false;
        bool b_l_castling = false;
        bool b_s_castling = false;

        int8_t en_passant_square = -1;
        uint16_t halfmove_clock = 0;
        double num_of_moves = 0;

        MoveArray legal_moves;

        void add_hash_to_history(zobrist::ZobristHash hash);
        void add_hash_to_history();
        void clear_history();
        uint8_t get_num_of_repetitions();

        void move(Move move);
        void move(std::string move);

        void make_move(Move move, PositionState& state);
        void unmake_move(Move move, const PositionState& state);

        MoveArray& get_legal_moves();
        MoveArray get_legal_moves_for_position(uint8_t x);
        static MoveArray distil_pawn_moves(MoveArray moves);
        std::vector<std::string> move_history;

        bool is_begin();
        bool is_end();

        void pawn_mask_to_moves(Bitboard mask, int delta, MoveArray* moves, bool en_passant);
        void mask_to_moves(Bitboard mask, uint8_t attacker_index, uint8_t attacker_color, uint8_t attacker_type, MoveArray* moves);

        bool is_position_attacked(uint8_t x);
        bool is_check();
        bool is_checkmate();
        bool is_double_check();
        bool is_draw();

        int get_winner();

        Bitboard get_king_legal_moves_mask();
        Bitboard get_check_mask();

        void castling(MoveArray* moves);

        bool operator==(const Board &board) const;
        bool operator!=(const Board &board) const;

        int8_t get_piece_type(const chess::Board &board, uint8_t x, uint8_t y);
        int8_t get_piece_type(const chess::Board &board, uint8_t x);

        std::string to_fen();
    };

    std::ostream& operator<<(std::ostream &ostream, chess::Board board);
    void print_bitboard(Bitboard bitboard);


}