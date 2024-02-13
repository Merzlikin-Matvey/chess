#include <iostream>

#include "engine/src/board.cpp"
#include "engine/src/figure.cpp"

using namespace std;

int main() {
    Board board;
    Rook rook(&board, make_pair(1, 1), "black");
    Knight knight (&board, make_pair(2, 3), "white");
    board.put_figure(rook);
    board.put_figure(knight);

    board.print();

    for (auto move : board.figure_by_position(make_pair(2, 3))->available_moves()){
        cout << move.first << '-' << move.second << ' ';
    }
    cout << endl;

    board.move(make_pair(2, 3), make_pair(1, 1), false);
    board.print();

}
