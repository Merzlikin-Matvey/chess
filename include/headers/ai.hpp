#pragma once

#include <string>

#include "chess-lib.hpp"
#include "transposition_table.hpp"

namespace chess::engine {
    class AI{
    public:
        AI (int max_depth, int begin_depth, int end_depth, size_t tt_size_mb = 1024) :  max_depth(max_depth), begin_depth(begin_depth), end_depth(end_depth), tt(tt_size_mb) {}
        AI (int max_depth, size_t tt_size_mb = 64) :  max_depth(max_depth), begin_depth(max_depth), end_depth(max_depth), tt(tt_size_mb) {}
        AI () :  max_depth(4), begin_depth(4), end_depth(4) {}
        int max_depth;
        int begin_depth;
        int end_depth;
        int sort_max_depth = 3;
        std::string search(Board& board);
        double max(Board& board, int depth, double alpha, double beta);
        double min(Board& board, int depth, double alpha, double beta);
        void sort_moves(MoveArray* moves)const;
        static int evaluate_move(Move move);

        uint64_t nodes_searched = 0;
        TranspositionTable tt;

    private:
        static const std::array<int, 6> MVV_LVA_values;
    };

    class AlphaAI : public AI {
    public:
        AlphaAI() : AI(2) {}
    };

    class BetaAI : public AI {
    public:
        BetaAI() : AI(3) {}
    };

    class GammaAI : public AI {
    public:
        GammaAI() : AI(4) {}
    };

    class DeltaAI : public AI {
    public:
        DeltaAI() : AI(5) {}
    };

}
