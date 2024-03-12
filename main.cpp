#include <iostream>
#include "engine/src/board.cpp"
#include "engine/src/figure.cpp"

using namespace std;

void game(){
    Board board;
    board.load_default_positions();

    string move;
    while (board.going){
        board.print();
        cin >> move;
        if (move == "exit") {
            break;
        }
        if (move == "save"){
            board.save_json(board.generate_id());
        }
        board.move(board.position_to_number_notation(move.substr(0, 2)), board.position_to_number_notation(move.substr(2, 2)));
    }
}

int main() {
   game();
}
