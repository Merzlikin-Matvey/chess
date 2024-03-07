#include <iostream>
#include "engine/src/board.cpp"
#include "engine/src/figure.cpp"

using namespace std;

int main() {
    Board board;
    board.load_default_positions();

    for (auto fig : board.figures) {
        for (auto move : fig->available_moves()) {
           cout << board.move_to_chess_notation(move) << endl;
        }
    }
}
