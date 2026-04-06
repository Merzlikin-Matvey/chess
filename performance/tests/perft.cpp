#include "../main.h"

#include <iostream>
#include <vector>
#include <numeric>

long long perft(chess::Board& board, const int depth) {
    if (depth == 0) {
        return 1;
    }

    if (depth == 1) {
        return board.count_legal_moves();
    }

    board.get_legal_moves();

    long long count = 0;
    const chess::MoveArray moves = board.legal_moves;
    chess::PositionState state;
    for (int i = 0; i < moves.size(); i++) {
        board.make_move(moves.moves[i], state);
        count += perft(board, depth - 1);
        board.unmake_move(moves.moves[i], state);
    }

    return count;
}


void benchmark_perft(const chess::Board& board, const int max_depth) {
    std::cout << "Perft benchmark from starting position" << std::endl;
    std::cout << "---------------------------------------" << std::endl;

    for (int depth = 1; depth <= max_depth; depth++) {
        chess::Board copy = board;

        auto start = std::chrono::high_resolution_clock::now();
        const long long nodes = perft(copy, depth);
        auto end = std::chrono::high_resolution_clock::now();

        const double ms = std::chrono::duration<double, std::milli>(end - start).count();
        const long long nps = ms > 0 ? static_cast<long long>(nodes / (ms / 1000.0)) : 0;

        std::cout << "Depth " << depth
             << "  Nodes: " << pretty_number(nodes)
             << "  Time: " << pretty_time(end - start)
             << "  NPS: " << pretty_number(nps) << std::endl;
    }
}



void perft_ci(const chess::Board& board, const int depth, const int iterations = 10) {
    std::cout << "\nPerft CI benchmark (depth " << depth << ", " << iterations << " iterations)" << std::endl;
    std::cout << "-----------------------------------------------" << std::endl;

    std::vector<double> nps_samples;
    nps_samples.reserve(iterations);

    for (int i = 0; i < iterations; i++) {
        chess::Board copy = board;

        auto start = std::chrono::high_resolution_clock::now();
        const long long nodes = perft(copy, depth);
        auto end = std::chrono::high_resolution_clock::now();

        const double seconds = std::chrono::duration<double>(end - start).count();
        double nps = seconds > 0 ? nodes / seconds : 0;
        nps_samples.push_back(nps);

        std::cout << "  Run " << (i + 1) << ": " << pretty_number(static_cast<long long>(nps)) << " NPS" << std::endl;
    }

    const double mean = std::accumulate(nps_samples.begin(), nps_samples.end(), 0.0) / iterations;

    double sq_sum = 0.0;
    for (const double v : nps_samples) {
        sq_sum += (v - mean) * (v - mean);
    }
    const double stddev = std::sqrt(sq_sum / iterations);

    // 95% confidence interval: mean ± 1.96 * (stddev / sqrt(n))
    const double margin = 1.96 * (stddev / std::sqrt(static_cast<double>(iterations)));

    std::cout << "\nResults:" << std::endl;
    std::cout << "  Mean NPS:    " << pretty_number(static_cast<long long>(mean)) << std::endl;
    std::cout << "  Std Dev:     " << pretty_number(static_cast<long long>(stddev)) << std::endl;
    std::cout << "  95% CI:      [" << pretty_number(static_cast<long long>(mean - margin))
              << " .. " << pretty_number(static_cast<long long>(mean + margin)) << "]" << std::endl;
}


void run_perft() {
    const auto  board = chess::Board("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
    constexpr int max_depth = 7;
    constexpr int ci_depth = 6;
    benchmark_perft(board, max_depth);
    perft_ci(board, ci_depth);
}

