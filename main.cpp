#include <iostream>

#include "engine/src/board.cpp"
#include "engine/src/figure.cpp"

using namespace std;

int main() {
    Board board;

    board.print();
    cout << board.figures[0]->position.second;
}
