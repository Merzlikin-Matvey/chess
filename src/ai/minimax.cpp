#include "chess-lib.hpp"
#include "headers/evaluate_position.hpp"
#include "headers/evaluating_constants.hpp"
#include "headers/ai.hpp"

double chess::engine::AI::max(Board board, int depth, double alpha, double beta){
    auto moves = board.legal_moves;
    if (sort_max_depth <= depth and sort_max_depth != -1){
        sort_moves(&moves);
    }
    if (depth == 0 or board.is_checkmate()){
        return evaluate_position(board, White);
    }

    double max_score = constants::minimum;
    Board copy;
    for (int i = 0; i < moves.size(); i++){
        copy = board;
        Move move = moves.moves[i];
        copy.move(move);
        copy.get_legal_moves();
        double score = min(copy, depth - 1, alpha, beta);
        max_score = std::max(max_score, score);
        alpha = std::max(alpha, score);
        if (alpha >= beta){
            break;
        }
    }

    return max_score;
}

double chess::engine::AI::min(Board board, int depth, double alpha, double beta){
    auto moves = board.legal_moves;
    if (sort_max_depth <= depth and sort_max_depth != -1){
        sort_moves(&moves);
    }
    if (depth == 0 or board.is_checkmate()){
        return evaluate_position(board, White);
    }

    double min_score = constants::maximum;
    Board copy;
    for (int i = 0; i < moves.size(); i++){
        copy = board;
        Move move = moves.moves[i];
        copy.move(move);
        copy.get_legal_moves();
        double score = max(copy, depth - 1, alpha, beta);
        min_score = std::min(min_score, score);
        beta = std::min(beta, score);
        if (alpha >= beta){
            break;
        }
    }

    return min_score;
}


