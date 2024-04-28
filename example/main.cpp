#include <iostream>
#include <chess-engine.hpp>

using namespace std;
using namespace chess;

int main() {
    Board board(convert_fen_to_bitboards("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"));
    cout << board;
}