#include <iostream>

#include "engine/src/board.cpp"
#include "engine/src/figure.cpp"

using namespace std;

int main() {
    Board board;
    board.encode_from_json("C:\\Users\\merzl\\CLionProjects\\chess\\saves\\data.json", board);
    Pawn(&board, make_pair(2, 2), "black");
    cout << board.figure_by_position(make_pair(2, 2))->position.second;
}
