#include <iostream>
#include <vector>
#include <numeric>
#include <cmath>

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



void perft_ci(const Board& board, int depth, int iterations = 10) {
    std::cout << "\nPerft CI benchmark (depth " << depth << ", " << iterations << " iterations)" << std::endl;
    std::cout << "-----------------------------------------------" << std::endl;

    std::vector<double> nps_samples;
    nps_samples.reserve(iterations);

    for (int i = 0; i < iterations; i++) {
        Board copy = board;

        auto start = std::chrono::high_resolution_clock::now();
        long long nodes = perft(copy, depth);
        auto end = std::chrono::high_resolution_clock::now();

        double seconds = std::chrono::duration<double>(end - start).count();
        double nps = seconds > 0 ? nodes / seconds : 0;
        nps_samples.push_back(nps);

        std::cout << "  Run " << (i + 1) << ": " << pretty_number(static_cast<long long>(nps)) << " NPS" << std::endl;
    }

    double mean = std::accumulate(nps_samples.begin(), nps_samples.end(), 0.0) / iterations;

    double sq_sum = 0.0;
    for (double v : nps_samples) {
        sq_sum += (v - mean) * (v - mean);
    }
    double stddev = std::sqrt(sq_sum / iterations);

    // 95% confidence interval: mean ± 1.96 * (stddev / sqrt(n))
    double margin = 1.96 * (stddev / std::sqrt(static_cast<double>(iterations)));

    std::cout << "\nResults:" << std::endl;
    std::cout << "  Mean NPS:    " << pretty_number(static_cast<long long>(mean)) << std::endl;
    std::cout << "  Std Dev:     " << pretty_number(static_cast<long long>(stddev)) << std::endl;
    std::cout << "  95% CI:      [" << pretty_number(static_cast<long long>(mean - margin))
              << " .. " << pretty_number(static_cast<long long>(mean + margin)) << "]" << std::endl;
}


int main() {
    auto  board = Board("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
    constexpr int max_depth = 7;
    constexpr int ci_depth = 6;
    benchmark_perft(board, max_depth);
    perft_ci(board, ci_depth);
}