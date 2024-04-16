#include <iostream>
#include <chess-engine.hpp>

int main() {
    chess::Board board;
    board.load_default_positions();
    board.print();
    board.move("e2e4");
    board.print();
}