#include "chess-lib.hpp"
#include "headers/ai.hpp"
#include "headers/evaluating_constants.hpp"

#include <algorithm>
#include <memory>
#include <unordered_map>

namespace chess::engine {

    double AI::evaluate_move(chess::Move move) {
        if (move.first == move.second) {
            return -1024;
        } else {
            double score = 0;
            switch (move.first_type) {
            case 0:
                score += 4;
                break;
            case 1:
                score += 12;
                break;
            case 2:
                score += 12;
                break;
            case 3:
                score += 12;
                break;
            case 4:
                score += 25;
                break;
            case 5:
                score += 50;
                break;
            default:
                return 0;
            }

            switch (move.second_type) {
            case 0:
                score -= 3;
                break;
            case 1:
                score -= 8;
                break;
            case 2:
                score -= 8;
                break;
            case 3:
                score -= 8;
                break;
            case 4:
                score -= 15;
                break;
            case 5:
                score -= 40;
                break;
            default:
                return 0;
            }

            return score;
        }
    }

    void AI::sort_moves(MoveArray* moves) {
        std::stable_sort(moves->begin(), moves->end(),
                         [this](Move a, Move b) { return evaluate_move(a) > evaluate_move(b); });
    }
} // namespace chess::engine
