#include <gtest/gtest.h>
#include <nlohmann/json.hpp>
#include <fstream>
#include <set>
#include <string>
#include "chess-lib.hpp"

using json = nlohmann::json;

namespace {

struct LegalMovesTestData {
    std::string fen;
    std::string comment;
    std::set<std::string> expected_moves;
};

LegalMovesTestData parse_entry(const json& j) {
    LegalMovesTestData data;
    data.fen = j["board"];

    if (j.contains("comment")) {
        data.comment = j["comment"].get<std::string>();
    }

    for (const auto& move : j["moves"]) {
        data.expected_moves.insert(move.get<std::string>());
    }

    return data;
}

std::vector<LegalMovesTestData> load_test_data(const std::string& filename) {
    std::ifstream file(std::string(TEST_DATA_DIR) + "/" + filename);
    EXPECT_TRUE(file.is_open()) << "Cannot open " << filename;
    json j = json::parse(file);

    std::vector<LegalMovesTestData> result;
    for (const auto& entry : j) {
        result.push_back(parse_entry(entry));
    }
    return result;
}

std::set<std::string> get_move_strings(chess::Board& board) {
    auto& moves = board.get_legal_moves();
    std::set<std::string> result;
    for (int i = 0; i < moves.size(); i++) {
        result.insert(moves[i].to_string());
    }
    return result;
}

chess::Board make_board(const LegalMovesTestData& data) {
    return chess::Board(data.fen);
}

std::string case_info(const size_t i, const LegalMovesTestData& c) {
    std::string info = "Case " + std::to_string(i) + ", FEN: " + c.fen;
    if (!c.comment.empty()) info += " (" + c.comment + ")";
    return info;
}

}

#define LEGAL_MOVES_TESTS(suite, json_file)                                    \
TEST(suite, MoveCount) {                                                       \
    auto cases = load_test_data(json_file);                                    \
    for (size_t i = 0; i < cases.size(); i++) {                                \
        auto board = make_board(cases[i]);                                     \
        auto actual = get_move_strings(board);                                 \
        EXPECT_EQ(actual.size(), cases[i].expected_moves.size())               \
            << case_info(i, cases[i]);                                         \
    }                                                                          \
}                                                                              \
TEST(suite, AllExpectedMovesPresent) {                                         \
    auto cases = load_test_data(json_file);                                    \
    for (size_t i = 0; i < cases.size(); i++) {                                \
        auto board = make_board(cases[i]);                                     \
        auto actual = get_move_strings(board);                                 \
        for (const auto& move : cases[i].expected_moves) {                     \
            EXPECT_TRUE(actual.count(move))                                    \
                << case_info(i, cases[i])                                      \
                << " — expected move " << move << " not found";                \
        }                                                                      \
    }                                                                          \
}                                                                              \
TEST(suite, NoUnexpectedMoves) {                                               \
    auto cases = load_test_data(json_file);                                    \
    for (size_t i = 0; i < cases.size(); i++) {                                \
        auto board = make_board(cases[i]);                                     \
        auto actual = get_move_strings(board);                                 \
        for (const auto& move : actual) {                                      \
            EXPECT_TRUE(cases[i].expected_moves.count(move))                   \
                << case_info(i, cases[i])                                      \
                << " — unexpected move " << move;                              \
        }                                                                      \
    }                                                                          \
}

LEGAL_MOVES_TESTS(StartingPosition, "starting_position.json")
LEGAL_MOVES_TESTS(SimpleOpenings, "simple_openings.json")
LEGAL_MOVES_TESTS(Castling, "castling.json")
LEGAL_MOVES_TESTS(Checkmates, "checkmates.json")
LEGAL_MOVES_TESTS(Pawns, "pawns.json")
LEGAL_MOVES_TESTS(Promotions, "promotions.json")
LEGAL_MOVES_TESTS(Stalemates, "stalemates.json")
LEGAL_MOVES_TESTS(Standard, "standard.json")
LEGAL_MOVES_TESTS(Taxing, "complex.json")