#include <iostream>
#include "board.cpp"
#include "figure.cpp"

using namespace std;

int main() {
    Board board;
    board.load_default_positions();

    string move;
    while (true){
        board.print();
        cin >> move;
        if (move == "exit") {
            break;
        }
        board.move(board.position_to_number_notation(move.substr(0, 2)), board.position_to_number_notation(move.substr(2, 2)));
    }
}
