#pragma once

#include <cstring>
#include <string>

#include "board.hpp"
#include "transposition_table.hpp"

namespace chess::engine {
    class AI {
    public:
        static constexpr int MAX_PLY = 64;

        AI(const int begin_depth, const int end_depth, const size_t tt_size_mb = 1024)
            : tt(tt_size_mb), begin_depth(begin_depth), end_depth(end_depth) {}
        AI() : AI(3, 5, 3) {}

        std::string search(Board& board);
        std::string root_search(Board& board, int depth);

        double max(Board& board, int depth, int ply, double alpha, double beta, bool allow_null = true);
        double min(Board& board, int depth, int ply, double alpha, double beta, bool allow_null = true);

        double quiescence_max(Board& board, double alpha, double beta);
        double quiescence_min(Board& board, double alpha, double beta);

        void sort_moves(MoveArray* moves, int ply, uint32_t tt_move_data) const;

        static int evaluate_move(Move move);

        uint64_t nodes_searched = 0;
        TranspositionTable tt;

    private:
        static const std::array<int, 6> MVV_LVA_values;

        int begin_depth, end_depth;
        int sort_max_depth = 3, nmp_min_depth = 3, lmr_threshold = 3;
        uint32_t killers[MAX_PLY][2]{};
        
        int history[2][6][64]{};

        void store_killer(int ply, uint32_t move_data);
        bool is_killer(int ply, uint32_t move_data) const;
        void update_history(uint8_t color, uint8_t piece_type, uint8_t to, int depth);
        int get_history(uint8_t color, uint8_t piece_type, uint8_t to) const;
    };

}  // namespace chess::engine
