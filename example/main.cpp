#include <iostream>

#include "chess-engine.hpp"
#include <iostream>

using namespace std;
using namespace chess;

int main() {
    Board board = Board();
    Move move(8, 0, 0, 63, 1, 1, false, false, false, false, false, false, 0);
    board.move(move);
    cout << board << endl;
}