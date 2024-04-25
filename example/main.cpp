#include <iostream>
#include <chess-engine.hpp>

int main() {
    chess::Board board;
    board.load_default_positions();
    std::string move;

    while(board.is_game_going() and move != "exit") {
        board.print();
        if (board.is_checkmate()) {
            std::cout << "Checkmate!" << std::endl;
            break;
        }
        if (board.is_check()) {
            std::cout << "Check!" << std::endl;
        }

        std::cout << "Enter your move: ";
        std::cin >> move;
        board.move(move);
    }
    board.save();
}