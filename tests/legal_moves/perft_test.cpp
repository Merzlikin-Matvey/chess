#include <gtest/gtest.h>
#include <string>
#include <vector>
#include "chess-lib.hpp"

namespace {

uint64_t perft(chess::Board& board, int depth) {
    if (depth == 0) return 1;

    uint64_t nodes = 0;
    board.get_legal_moves();
    chess::MoveArray moves = board.legal_moves;
    chess::PositionState state;
    for (int i = 0; i < moves.size(); i++) {
        board.make_move(moves.moves[i], state);
        nodes += perft(board, depth - 1);
        board.unmake_move(moves.moves[i], state);
    }
    return nodes;
}

struct PerftCase {
    std::string fen;
    std::vector<uint64_t> expected;
    std::string name;
};

// Reference values from https://www.chessprogramming.org/Perft_Results
std::vector<PerftCase> get_perft_cases() {
    return {
        {
            "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1",
            {20, 400, 8902, 197281, 4865609, 119060324},
            "Starting position"
        },
        {
            "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1",
            {48, 2039, 97862},
            "Kiwipete"
        },
        {
            "8/2p5/3p4/KP5r/1R3p1k/8/4P1P1/8 w - - 0 1",
            {14, 191, 2812, 43238, 674624},
            "Position 3"
        },
        {
            "r3k2r/Pppp1ppp/1b3nbN/nP6/BBP1P3/q4N2/Pp1P2PP/R2Q1RK1 w kq - 0 1",
            {6, 264, 9467, 422333},
            "Position 4"
        },
        {
            "rnbq1k1r/pp1Pbppp/2p5/8/2B5/8/PPP1NnPP/RNBQK2R w KQ - 1 8",
            {44, 1486, 62379, 2103487},
            "Position 5"
        },
        {
            "r4rk1/1pp1qppp/p1np1n2/2b1p1B1/2B1P1b1/P1NP1N2/1PP1QPPP/R4RK1 w - - 0 10",
            {46, 2079, 89890, 3894594},
            "Position 6"
        },
    };
}

class PerftTest : public testing::TestWithParam<std::tuple<size_t, int>> {};

TEST_P(PerftTest, NodeCount) {
    auto [case_idx, depth_idx] = GetParam();
    auto cases = get_perft_cases();
    const auto& tc = cases[case_idx];

    chess::Board board(tc.fen);
    uint64_t result = perft(board, depth_idx + 1);
    EXPECT_EQ(result, tc.expected[depth_idx])
        << tc.name << " at depth " << depth_idx + 1;
}

std::vector<std::tuple<size_t, int>> generate_params() {
    std::vector<std::tuple<size_t, int>> params;
    auto cases = get_perft_cases();
    for (size_t i = 0; i < cases.size(); i++) {
        for (int d = 0; d < (int)cases[i].expected.size(); d++) {
            params.emplace_back(i, d);
        }
    }
    return params;
}

std::string param_name(const testing::TestParamInfo<std::tuple<size_t, int>>& info) {
    auto [case_idx, depth_idx] = info.param;
    auto cases = get_perft_cases();
    std::string name = cases[case_idx].name;
    for (auto& c : name) {
        if (!isalnum(c)) c = '_';
    }
    return name + "_depth" + std::to_string(depth_idx + 1);
}

INSTANTIATE_TEST_SUITE_P(Perft, PerftTest,
    ::testing::ValuesIn(generate_params()),
    param_name);

}
