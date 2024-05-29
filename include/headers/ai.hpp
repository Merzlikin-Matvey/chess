#pragma once

#include <string>

#include "chess-lib.hpp"

namespace chess::engine {
    class AI{
    public:
        AI (int max_depth, int begin_depth, int end_depth) :  max_depth(max_depth), begin_depth(begin_depth), end_depth(end_depth) {}
        AI (int max_depth) :  max_depth(max_depth), begin_depth(max_depth), end_depth(max_depth) {}
        AI () :  max_depth(4), begin_depth(4), end_depth(4) {}
        int max_depth;
        int begin_depth;
        int end_depth;
        int sort_max_depth = 3;
        std::string search(Board& board);
        double max(Board board, int depth, double alpha, double beta);
        double min(Board board, int depth, double alpha, double beta);
        void sort_moves(MoveArray* moves);
        double evaluate_move(Move move);
    };

    class AlphaAI : public AI {
    public:
        AlphaAI() : AI(2) {}
    };

}
