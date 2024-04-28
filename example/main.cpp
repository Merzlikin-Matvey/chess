#include <iostream>

#include "chess-engine.hpp"

using namespace std;
using namespace chess;

int main() {
    Board board_1 = Board();
    Board board_2 = Board(convert_fen_to_bitboards("Rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"));

    auto hash_1 = zobrist::ZobristHash(board_1, false, false, false, false, false);
    auto hash_2 = zobrist::ZobristHash(board_2, false, false, false, false, false);


    cout << hash_1 << endl;
    cout << hash_2 << endl;
}