#include <iostream>

#include "engine/src/board.cpp"
#include "engine/src/figure.cpp"

using namespace std;

int main() {
    Board board;
    Pawn pawn1(&board, make_pair(4, 1), "white");
    Pawn pawn2(&board, make_pair(2, 6), "black");
    Rook rook(&board, make_pair(2, 1), "white");

    board.put_figure(pawn1);
    board.put_figure(pawn2);
    board.put_figure(rook);
    board.print();

    for (auto move : rook.available_moves()){
        cout << move.first << '-' << move.second << ' ';
    }

}
