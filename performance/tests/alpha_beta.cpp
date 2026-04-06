#include "../main.h"

#include <iostream>
#include <chrono>
#include <vector>
#include <string>
#include <numeric>

#include "chess-lib.hpp"
#include "headers/ai.hpp"

void  run_alpha_beta() {
    const std::vector<std::string> positions = {
        "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1",
        "r1bqkbnr/pppppppp/2n5/8/4P3/8/PPPP1PPP/RNBQKBNR w KQkq - 1 2",
        "rnbqkb1r/pppppppp/5n2/8/4P3/8/PPPP1PPP/RNBQKBNR w KQkq - 1 2",
        "rnbqkbnr/pppp1ppp/8/4p3/4P3/8/PPPP1PPP/RNBQKBNR w KQkq e6 0 2",
        "r1bqkbnr/pppp1ppp/2n5/4p3/4P3/5N2/PPPP1PPP/RNBQKB1R w KQkq - 2 3",
        "rnbqkb1r/pp1ppppp/5n2/2p5/4P3/5N2/PPPP1PPP/RNBQKB1R w KQkq c6 0 3",
        "r1bqkbnr/pppppppp/2n5/8/3PP3/8/PPP2PPP/RNBQKBNR b KQkq d3 0 2",
        "rnbqkb1r/pppppp1p/5np1/8/4P3/5N2/PPPP1PPP/RNBQKB1R w KQkq - 0 3",
        "r1bqk2r/pppp1ppp/2n2n2/2b1p3/2B1P3/5N2/PPPP1PPP/RNBQK2R w KQkq - 4 4",
        "rnbqk2r/pppp1ppp/4pn2/8/1bPP4/2N5/PP2PPPP/R1BQKBNR w KQkq - 2 4",
        "r1bqk2r/ppppbppp/2n2n2/4p3/4P3/2N2N2/PPPP1PPP/R1BQKB1R w KQkq - 4 4",
        "rnbqk2r/ppp1ppbp/3p1np1/8/2PPP3/2N5/PP3PPP/R1BQKBNR w KQkq - 0 5",
        "r1bq1rk1/pppnbppp/4pn2/3p4/2PP4/2NBPN2/PP3PPP/R1BQK2R w KQ - 4 7",
        "r2q1rk1/pp2ppbp/2np1np1/8/2PNP3/2N1BP2/PP4PP/R2QKB1R w KQ - 0 9",
        "r1bqr1k1/ppp2ppp/2np1n2/2b1p3/2B1P3/2NP1N2/PPP2PPP/R1BQ1RK1 w - - 0 7",
        "2r2rk1/pp2bppp/2n1pn2/q7/2B5/P1N2N2/1PP2PPP/R2QR1K1 w - - 0 12",
        "r4rk1/1ppqbppp/p1n1pn2/3p4/2PP4/2NBPN2/PP2QPPP/R4RK1 w - - 0 10",
        "r1b2rk1/2q1bppp/p2ppn2/1p4B1/3NP3/2N5/PPPQ1PPP/2KR1B1R w - - 0 11",
        "3r2k1/pp2rppp/2p2n2/4q3/4P3/2N5/PPP2PPP/R2QR1K1 w - - 0 15",
        "r4rk1/pp3ppp/2p5/8/4Pb2/2N2N2/PPP2PPP/R4RK1 w - - 0 13",
    };

    chess::engine::AI ai(1, 10);
    std::vector<double> times_ms;

    for (int i = 0; i < positions.size(); i++) {
        chess::Board board(positions[i]);
        board.get_legal_moves();

        auto start = std::chrono::high_resolution_clock::now();
        std::string best_move = ai.search(board);
        auto end = std::chrono::high_resolution_clock::now();

        double ms = std::chrono::duration<double, std::milli>(end - start).count();
        times_ms.push_back(ms);

        std::cout << "[" << (i + 1) << "/" << positions.size() << "] "
             << positions[i].substr(0, 40) << "...  "
             << "move: " << best_move << "  "
             << "time: " << pretty_time(end - start) << " "
             << "nodes searched: " << pretty_number(ai.nodes_searched) << "  "
             << "NPS: " << pretty_number(ai.nodes_searched / (ms / 1000) )<< std::endl;
    }

    const double total = std::accumulate(times_ms.begin(), times_ms.end(), 0.0);
    const double avg = total / times_ms.size();
    const double min_t = *std::ranges::min_element(times_ms);
    const double max_t = *std::ranges::max_element(times_ms);

    std::cout << "-----------------------------------" << std::endl;
    std::cout << "Total:   " << pretty_time(std::chrono::duration<double, std::milli>(total)) << std::endl;
    std::cout << "Average: " << pretty_time(std::chrono::duration<double, std::milli>(avg)) << std::endl;
    std::cout << "Min:     " << pretty_time(std::chrono::duration<double, std::milli>(min_t)) << std::endl;
    std::cout << "Max:     " << pretty_time(std::chrono::duration<double, std::milli>(max_t)) << std::endl;
}