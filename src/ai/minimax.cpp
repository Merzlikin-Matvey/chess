#include "chess-lib.hpp"
#include "headers/ai.hpp"
#include "headers/evaluate_position.hpp"
#include "headers/evaluating_constants.hpp"

double chess::engine::AI::max(Board& board, const int depth, double alpha, double beta, const bool allow_null) {
    nodes_searched++;

    if (depth <= 0 or board.legal_moves.size() == 0) {
        if (depth <= 0 and board.legal_moves.size() > 0) {
            return quiescence_max(board, alpha, beta);
        }
        return evaluate_position(board, White);
    }

    const double original_alpha = alpha;
    const double original_beta = beta;

    uint32_t tt_move_data = 0;
    const TTEntry* entry = tt.probe(board.current_hash);
    if (entry) {
        tt_move_data = entry->best_move;
        if (entry->depth >= depth) {
            if (entry->flag == TTFlag::EXACT)
                return entry->score;
            if (entry->flag == TTFlag::LOWER_BOUND)
                alpha = std::max(alpha, entry->score);
            if (entry->flag == TTFlag::UPPER_BOUND)
                beta = std::min(beta, entry->score);
            if (alpha >= beta)
                return entry->score;
        }
    }

    if (allow_null and depth >= nmp_min_depth and board.check_status == 0) {
        NullMoveState null_state;
        board.make_null_move(null_state);
        board.get_legal_moves();
        const double null_score = min(board, depth - 1 - 2, alpha, beta, false);
        board.unmake_null_move(null_state);
        if (null_score >= beta) {
            return beta;
        }
        board.get_legal_moves();
    }

    auto moves = board.legal_moves;
    if (sort_max_depth <= depth and sort_max_depth != -1) {
        sort_moves(&moves);
    }

    if (tt_move_data != 0) {
        for (int i = 1; i < moves.size(); i++) {
            if (moves.moves[i].data == tt_move_data) {
                std::swap(moves.moves[0], moves.moves[i]);
                break;
            }
        }
    }

    Move best_move = moves.moves[0];
    double max_score = constants::minimum;
    for (int i = 0; i < moves.size(); i++) {
        PositionState state;
        const Move move = moves.moves[i];
        board.make_move(move, state);
        board.get_legal_moves();
        double score = min(board, depth - 1, alpha, beta);
        board.unmake_move(move, state);
        if (score > max_score) {
            max_score = score;
            best_move = move;
        }
        alpha = std::max(alpha, score);
        if (alpha >= beta) {
            break;
        }
    }

    TTFlag flag;
    if (max_score <= original_alpha)
        flag = TTFlag::UPPER_BOUND;
    else if (max_score >= original_beta)
        flag = TTFlag::LOWER_BOUND;
    else
        flag = TTFlag::EXACT;
    tt.store(board.current_hash, max_score, depth, flag, best_move.data);

    return max_score;
}

double chess::engine::AI::min(Board& board, int depth, double alpha, double beta, bool allow_null) {
    nodes_searched++;

    if (depth <= 0 or board.legal_moves.size() == 0) {
        if (depth <= 0 and board.legal_moves.size() > 0) {
            return quiescence_min(board, alpha, beta);
        }
        return evaluate_position(board, White);
    }

    const double original_alpha = alpha;
    const double original_beta = beta;

    uint32_t tt_move_data = 0;
    const TTEntry* entry = tt.probe(board.current_hash);
    if (entry) {
        tt_move_data = entry->best_move;
        if (entry->depth >= depth) {
            if (entry->flag == TTFlag::EXACT)
                return entry->score;
            if (entry->flag == TTFlag::LOWER_BOUND)
                alpha = std::max(alpha, entry->score);
            if (entry->flag == TTFlag::UPPER_BOUND)
                beta = std::min(beta, entry->score);
            if (alpha >= beta)
                return entry->score;
        }
    }

    if (allow_null and depth >= nmp_min_depth and board.check_status == 0) {
        NullMoveState null_state;
        board.make_null_move(null_state);
        board.get_legal_moves();
        const double null_score = max(board, depth - 1 - 2, alpha, beta, false);
        board.unmake_null_move(null_state);
        if (null_score <= alpha) {
            return alpha;
        }
        board.get_legal_moves();
    }

    auto moves = board.legal_moves;
    if (sort_max_depth <= depth and sort_max_depth != -1) {
        sort_moves(&moves);
    }
    if (tt_move_data != 0) {
        for (int i = 1; i < moves.size(); i++) {
            if (moves.moves[i].data == tt_move_data) {
                std::swap(moves.moves[0], moves.moves[i]);
                break;
            }
        }
    }

    Move best_move = moves.moves[0];
    double min_score = constants::maximum;
    for (int i = 0; i < moves.size(); i++) {
        PositionState state;
        const Move move = moves.moves[i];
        board.make_move(move, state);
        board.get_legal_moves();
        double score = max(board, depth - 1, alpha, beta);
        board.unmake_move(move, state);
        if (score < min_score) {
            min_score = score;
            best_move = move;
        }
        beta = std::min(beta, score);
        if (alpha >= beta) {
            break;
        }
    }

    TTFlag flag;
    if (min_score >= original_beta)
        flag = TTFlag::LOWER_BOUND;
    else if (min_score <= original_alpha)
        flag = TTFlag::UPPER_BOUND;
    else
        flag = TTFlag::EXACT;
    tt.store(board.current_hash, min_score, depth, flag, best_move.data);

    return min_score;
}
