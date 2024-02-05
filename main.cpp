#include <iostream>

#include "engine/src/board.cpp"
#include "engine/src/figure.cpp"

using namespace std;

int main() {
    Board board;
    Figure figure(&board, "Figure", pair<int, int> {1, 1}, "white");

    board.figures.push_back(figure);
    cout << figure.is_empty(make_pair(1, 1));
}
