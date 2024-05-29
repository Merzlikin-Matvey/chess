#include "chess-lib.hpp"

std::string chess::engine::AI::search(Board& board) {
    board.get_legal_moves();
    double max_score = constants::minimum;
    double score;
    Move best_move;
    Board copy;
    double alpha = constants::minimum;
    double beta = constants::maximum;

    auto moves = board.legal_moves;
    sort_moves(&moves);

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
    return best_move.to_string();
}

