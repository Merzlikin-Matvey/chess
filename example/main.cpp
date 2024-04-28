#include <iostream>
#include <chess-engine.hpp>

using namespace std;

int main() {
    chess::Board board;
    board.load_default_positions();

    auto moves = {
            "h2h4",
            "g7g5",
    };

    for (auto move : moves) {
        board.move(move);
        board.print();
    }

    auto available_moves = board.available_moves();
    for (auto move : available_moves) {
        cout << move << endl;
    }

}