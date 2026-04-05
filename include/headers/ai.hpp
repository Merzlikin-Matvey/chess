#pragma once

#include <string>

#include "chess-lib.hpp"
#include "transposition_table.hpp"

namespace chess::engine {
    class AI{
    public:
        AI (int begin_depth, int end_depth, size_t tt_size_mb = 1024) : tt(tt_size_mb), begin_depth(begin_depth), end_depth(end_depth) {}
        AI () : AI(3, 5, 3) {}

        std::string search(Board& board);
        std::string root_search(Board& board, int depth);

        double max(Board& board, int depth, double alpha, double beta);
        double min(Board& board, int depth, double alpha, double beta);

        double quiescence_max(Board& board, double alpha, double beta);
        double quiescence_min(Board& board, double alpha, double beta);

        void sort_moves(MoveArray* moves) const;

        static int evaluate_move(Move move);

        uint64_t nodes_searched = 0;
        TranspositionTable tt;

    private:
        static const std::array<int, 6> MVV_LVA_values;

        int begin_depth, end_depth;
        int sort_max_depth = 3;
    };

}
