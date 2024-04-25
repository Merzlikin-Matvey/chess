#include <iostream>
#include <chess-engine.hpp>

int main() {
    chess::Board board;
    board.load_default_positions();

    std::string move;
    std::cin >> move;
    board.move(move);
    board.print();

    chess::Board copy;
    copy.copy(&board);

    copy.print();
    auto moves = copy.available_moves();
    for (auto &move : moves) {
        std::cout << move << std::endl;
    }




}