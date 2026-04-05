#include "chess-lib.hpp"
#include "headers/evaluate_position.hpp"
#include "headers/ai.hpp"

double chess::engine::AI::quiescence_max(Board& board, double alpha, double beta) {
    nodes_searched++;

    double standard_eval = evaluate_position(board, White);
    if (standard_eval >= beta) return beta;
    if (alpha < standard_eval) alpha = standard_eval;

    auto moves = board.legal_moves;

    for (int i = 0; i < moves.size(); i++) {
        Move move = moves.moves[i];
        if (move.second_type() == 255) continue;

        PositionState state;
        board.make_move(move, state);
        board.get_legal_moves();
        double score = quiescence_min(board, alpha, beta);
        board.unmake_move(move, state);

        if (score >= beta) return beta;
        if (score > alpha) alpha = score;
    }

    return alpha;
}

double chess::engine::AI::quiescence_min(Board& board, double alpha, double beta) {
    nodes_searched++;

    double standard_eval = evaluate_position(board, White);
    if (standard_eval <= alpha) return alpha;
    if (beta > standard_eval) beta = standard_eval;

    auto moves = board.legal_moves;

    for (int i = 0; i < moves.size(); i++) {
        Move move = moves.moves[i];
        if (move.second_type() == 255) continue;

        PositionState state;
        board.make_move(move, state);
        board.get_legal_moves();
        double score = quiescence_max(board, alpha, beta);
        board.unmake_move(move, state);

        if (score <= alpha) return alpha;
        if (score < beta) beta = score;
    }

    return beta;
}
