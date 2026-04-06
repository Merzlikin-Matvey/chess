#include <algorithm>

#include "headers/ai.hpp"

namespace chess::engine {
    const std::array<int, 6> AI::MVV_LVA_values = {1, 5, 3, 3, 9, 100};

    int AI::evaluate_move(const Move move) {
        if (move.second_type() == 255) {
            return 0;
        }

        return 10 * MVV_LVA_values.at(move.second_type()) - MVV_LVA_values.at(move.piece_type());
    }

    void AI::sort_moves(MoveArray* moves)  {
        const auto begin = moves->begin();
        const auto end = moves->begin() + moves->size();
        const int k = std::min(7, moves->size());
        std::partial_sort(begin, begin + k, end, [](const Move a, const Move b) { return evaluate_move(a) > evaluate_move(b); });
    }
}  // namespace chess::engine