#include <iostream>

#include "engine/src/board.cpp"
#include "engine/src/figure.cpp"

using namespace std;

int main() {
    Board board;
    cout << board.position_to_number_notation(board.position_to_chess_notation(make_pair(1, 1))).first;
    cout << board.position_to_number_notation(board.position_to_chess_notation(make_pair(1, 1))).second;
}
