#include "chess-lib.hpp"

std::string chess::engine::AI::search(Board& board) {
    board.get_legal_moves();
    double score;
    Move best_move;
    Board copy;
    double alpha = constants::minimum;
    double beta = constants::maximum;

    auto moves = board.legal_moves;
    sort_moves(&moves);

    if (board.white_turn){
        double max_score = constants::minimum;
        for (int i = 0; i < moves.size(); i++) {
            copy = board;
            Move move = moves.moves[i];
            copy.move(move);
            copy.get_legal_moves();
            score = min(copy, max_depth - 1, alpha, beta);
            if (score > max_score) {
                max_score = score;
                best_move = move;
                alpha = std::max(alpha, score);
                if (alpha >= beta){
                    break;
                }
            }
        }
    }
    else {
        double min_score = constants::maximum;
        for (int i = 0; i < moves.size(); i++) {
            copy = board;
            Move move = moves.moves[i];
            copy.move(move);
            copy.get_legal_moves();
            score = max(copy, max_depth - 1, alpha, beta);
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

