#include <iostream>

#include "chess-engine.hpp"
#include <iostream>

using namespace std;
using namespace chess;

int main() {
    Board board = Board("8/8/8/8/8/8/8/R3K3");
    Move move = Move(position_to_number_notation("e1"),
                     White,
                     King,
                        position_to_number_notation("c1"),
                     White,
                     255,
                     true,
                     false,
                     false,
                     false,
                     false,
                     false, 0);
    board.move(move);
    cout << board << endl;

}