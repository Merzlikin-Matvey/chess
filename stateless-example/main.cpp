#include "chess-lib.hpp"

std::vector<std::string> getLegalMoves(const std::string &fen, const bool white_turn = true) {
    auto board = chess::Board(fen);
    board.white_turn = white_turn;

    auto moves = board.get_legal_moves();
    std::vector<std::string> legal_moves;
    for (auto move: moves) {
        legal_moves.push_back(move.to_string());
    }
    return legal_moves;
}


std::string getAIMove(const std::string &fen, const bool white_turn = false) {
    auto board = chess::Board(fen);
    board.white_turn = white_turn;

    auto ai = chess::engine::AI(5);
    auto move = ai.search(board);

    return move;
}

std::string makeMove(const std::string &fen, const std::string &move, const bool white_turn = true) {
    auto board = chess::Board(fen);
    board.white_turn = white_turn;

    board.get_legal_moves();
    board.move(move);

    return board.to_fen();
}

std::string getResult(const std::string &fen, const bool white_turn = true) {
    auto board = chess::Board(fen);
    board.white_turn = white_turn;

    if (board.is_checkmate()) {
        if (white_turn) {
            return "Black wins";
        }
        return "White wins";
    }

    if (board.is_draw()) {
        return "Draw";
    }
}

int main() {
    auto fen = "7k/8/8/8/8/q7/3q4/K7";
    std::cout << getResult(fen) << std::endl;
    return 0;
}