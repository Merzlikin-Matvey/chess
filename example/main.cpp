#include <iostream>
#include <chess-engine/chess-engine.hpp>

int main() {
    chess::Board board;
    board.load_default_positions();
    board.print();
}