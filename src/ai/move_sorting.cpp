#include "chess-lib.hpp"
#include "headers/evaluating_constants.hpp"
#include "headers/ai.hpp"

#include <algorithm>
#include <unordered_map>
#include <memory>

namespace chess::engine {
    const std::array<int, 6> AI::MVV_LVA_values= {1, 5, 3, 3, 9, 100};


    double AI::evaluate_move( chess::Move move) {
        if (move.second_type() == 255) {
            return 0;
        }

        double score = 5 * MVV_LVA_values.at(move.second_type()) - MVV_LVA_values.at(move.piece_type());
        return score;

    }

    void AI::sort_moves(MoveArray* moves) {
        std::stable_sort(moves->begin(), moves->end(), [this](Move a, Move b) {
            return evaluate_move(a) > evaluate_move(b);
        });
    }
}