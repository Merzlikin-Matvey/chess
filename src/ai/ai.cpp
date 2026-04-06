#include "headers/ai.hpp"
#include "headers/constants.hpp"
#include "headers/evaluating_constants.hpp"

std::string chess::engine::AI::search(Board& board) {
    nodes_searched = 0;
    std::memset(killers, 0, sizeof(killers));
    std::memset(history, 0, sizeof(history));
    board.get_legal_moves();

    std::string best_move = "";
    for (int depth = begin_depth; depth <= end_depth; depth++) {
        best_move = root_search(board, depth);
    }

    return best_move;
}

std::string chess::engine::AI::root_search(Board& board, const int depth) {
    board.get_legal_moves();
    double score;
    double alpha = constants::minimum;
    double beta = constants::maximum;

    auto moves = board.legal_moves;
    if (moves.size() == 0) {
        return "";
    }

    uint32_t tt_move_data = 0;
    const TTEntry* entry = tt.probe(board.current_hash);
    if (entry) {
        tt_move_data = entry->best_move;
    }
    sort_moves(&moves, 0, tt_move_data);

    Move best_move = moves.moves[0];

    if (board.white_turn) {
        double max_score = constants::minimum;
        for (int i = 0; i < moves.size(); i++) {
            PositionState state;
            const Move move = moves.moves[i];
            board.make_move(move, state);
            board.get_legal_moves();
            score = min(board, depth - 1, 1, alpha, beta);
            board.unmake_move(move, state);
            if (score > max_score) {
                max_score = score;
                best_move = move;
                alpha = std::max(alpha, score);
                if (alpha >= beta) {
                    break;
                }
            }
        }
    } else {
        double min_score = constants::maximum;
        for (int i = 0; i < moves.size(); i++) {
            PositionState state;
            const Move move = moves.moves[i];
            board.make_move(move, state);
            board.get_legal_moves();
            score = max(board, depth - 1, 1, alpha, beta);
            board.unmake_move(move, state);
            if (score < min_score) {
                min_score = score;
                best_move = move;
                beta = std::min(beta, score);
                if (alpha >= beta) {
                    break;
                }
            }
        }
    }

    return best_move.to_string();
}
