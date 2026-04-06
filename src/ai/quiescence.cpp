#include "chess-lib.hpp"
#include "headers/ai.hpp"
#include "headers/evaluate_position.hpp"

double chess::engine::AI::quiescence_max(Board& board, double alpha, const double beta) {
    nodes_searched++;

    const double standard_eval = evaluate_position(board, White);
    if (standard_eval >= beta)
        return beta;
    if (alpha < standard_eval)
        alpha = standard_eval;

    constexpr double big_delta = 9;
    if (standard_eval + big_delta < alpha)
        return alpha;

    auto moves = board.legal_moves;

    // TODO: get_legal_captures
    int capture_count = 0;
    for (int i = 0; i < moves.size(); i++) {
        if (moves.moves[i].second_type() != 255) {
            moves.moves[capture_count++] = moves.moves[i];
        }
    }
    if (capture_count == 0)
        return alpha;
    moves.resize(capture_count);
    sort_moves(&moves);

    for (int i = 0; i < capture_count; i++) {
        PositionState state;
        board.make_move(moves.moves[i], state);
        board.get_legal_moves();
        const double score = quiescence_min(board, alpha, beta);
        board.unmake_move(moves.moves[i], state);

        if (score >= beta)
            return beta;
        if (score > alpha)
            alpha = score;
    }

    return alpha;
}

double chess::engine::AI::quiescence_min(Board& board, const double alpha, double beta) {
    nodes_searched++;

    const double standard_eval = evaluate_position(board, White);
    if (standard_eval <= alpha)
        return alpha;
    if (beta > standard_eval)
        beta = standard_eval;

    constexpr double big_delta = 9;
    if (standard_eval - big_delta > beta)
        return beta;

    // TODO: get_legal_captures
    auto moves = board.legal_moves;
    int capture_count = 0;
    for (int i = 0; i < moves.size(); i++) {
        if (moves.moves[i].second_type() != 255) {
            moves.moves[capture_count++] = moves.moves[i];
        }
    }
    if (capture_count == 0)
        return beta;
    moves.resize(capture_count);
    sort_moves(&moves);

    for (int i = 0; i < capture_count; i++) {
        PositionState state;
        board.make_move(moves.moves[i], state);
        board.get_legal_moves();
        const double score = quiescence_max(board, alpha, beta);
        board.unmake_move(moves.moves[i], state);

        if (score <= alpha)
            return alpha;
        if (score < beta)
            beta = score;
    }

    return beta;
}
