#include <iostream>

#include "engine/src/board.cpp"
#include "engine/src/figure.cpp"

using namespace std;

int main() {
    Board board;
    Figure give_me_a_name(&board, "name", make_pair(2, 2), "black", "f");
    cout << board.figures[0]->position.first;
}
