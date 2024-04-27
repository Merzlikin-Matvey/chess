#include <iostream>
#include <chess-engine.hpp>

using namespace std;

int main() {
    chess::Board board;
    board.load_default_positions();

    board.print();
    for (auto move : board.available_moves()) {
        cout << move << endl;
    }

}