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

    void AI::sort_moves(MoveArray* moves, const int ply, const uint32_t tt_move_data) const {
        const int n = moves->size();
        if (n <= 1) return;
        
        std::array<int, 218> scores{};
        for (int i = 0; i < n; i++) {
            const Move& move = moves->moves[i];

            if (move.data == tt_move_data && tt_move_data != 0) {
                scores[i] = 1000000; 
            } else if (move.second_type() != 255) {
                scores[i] = 100000 + evaluate_move(move);
            } else if (is_killer(ply, move.data)) {
                scores[i] = 50000;
            } else {
                scores[i] = get_history(move.attacker_color(), move.piece_type(), move.to());
            }
        }
        
        const int k = std::min(n, 16);
        for (int i = 0; i < k; i++) {
            int best = i;
            for (int j = i + 1; j < n; j++) {
                if (scores[j] > scores[best]) best = j;
            }
            if (best != i) {
                std::swap(moves->moves[i], moves->moves[best]);
                std::swap(scores[i], scores[best]);
            }
        }
    }

    void AI::store_killer(const int ply, const uint32_t move_data) {
        if (ply >= MAX_PLY) return;
        if (killers[ply][0] == move_data) return;
        killers[ply][1] = killers[ply][0];
        killers[ply][0] = move_data;
    }

    bool AI::is_killer(const int ply, const uint32_t move_data) const {
        if (ply >= MAX_PLY) return false;
        return killers[ply][0] == move_data || killers[ply][1] == move_data;
    }

    void AI::update_history(const uint8_t color, const uint8_t piece_type, const uint8_t to, const int depth) {
        history[color][piece_type][to] += depth * depth;
        if (history[color][piece_type][to] > 1000000) {
            for (auto& c : history)
                for (auto& p : c)
                    for (auto& s : p)
                        s /= 2;
        }
    }

    int AI::get_history(const uint8_t color, const uint8_t piece_type, const uint8_t to) const {
        return history[color][piece_type][to];
    }

}  // namespace chess::engine