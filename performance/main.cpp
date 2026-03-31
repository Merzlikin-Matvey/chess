#include <iostream>

#include "chess-lib.hpp"

using namespace chess;

std::string pretty_number(long long n) {
    if (n < 10'000) {
        return std::to_string(n);
    }
    if (n < 10'000'000) {
        return std::to_string(n / 1'000) + "K";
    }
    if (n < 10'000'000'000) {
        return std::to_string(n / 1'000'000) + "M";
    }
    return std::to_string(n / 1'000'000'000) + "B";
}


long long perft(Board& board, int depth) {
    if (depth == 0) {
        return 1;
    }

    if (depth == 1) {
        return board.count_legal_moves();
    }

    board.get_legal_moves();

    long long count = 0;
    MoveArray moves = board.legal_moves;
    PositionState state;
    for (int i = 0; i < moves.size(); i++) {
        board.make_move(moves.moves[i], state);
        count += perft(board, depth - 1);
        board.unmake_move(moves.moves[i], state);
    }

    return count;
}


void benchmark_perft(const Board& board, int max_depth) {
    std::cout << "Perft benchmark from starting position" << std::endl;
    std::cout << "---------------------------------------" << std::endl;

    for (int depth = 1; depth <= max_depth; depth++) {
        Board copy = board;

        auto start = std::chrono::high_resolution_clock::now();
        long long nodes = perft(copy, depth);
        auto end = std::chrono::high_resolution_clock::now();

        double ms = std::chrono::duration<double, std::milli>(end - start).count();
        long long nps = ms > 0 ? static_cast<long long>(nodes / (ms / 1000.0)) : 0;

        std::cout << "Depth " << depth
             << "  Nodes: " << pretty_number(nodes)
             << "  Time: " << static_cast<long long>(ms) << " ms"
             << "  NPS: " << pretty_number(nps) << std::endl;
    }
}



int main() {
    auto  board = Board("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
    constexpr int max_depth = 7;
    benchmark_perft(board, max_depth);
}