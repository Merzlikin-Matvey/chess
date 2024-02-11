#include <iostream>

#include "engine/src/board.cpp"
#include "engine/src/figure.cpp"

using namespace std;

int main() {
    Board board;
    Pawn pawn(&board, make_pair(1, 1), "white");
    board.put_figure(pawn);
    board.move(make_pair(1, 1), make_pair(2, 1), false);
    board.print();
}
