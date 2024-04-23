// Magnus Carlsen vs Alberto Santos Flores 2024.01.2

#include <iostream>
#include <chess-engine.hpp>

int main() {
    chess::Board board;
    board.load_default_positions();
    vector<string> moves = {
            "e2e4",
            "e6e7",
            "b2b3",
            "d7d5",
            "c1b2",
            "d5e4",
            "b1c3",
            "g8f6",
            "g2g4",
            "h7h6",
            "d1e2",
            "f8b4",
            "e1c1",
            "d8e7",
            "c1b1",
            "b4a3",
            "b1a1",
            "a7a5",
            "c3e4",
            "f6e4",
            "e2e4",
            "a5a4",
            "e1g7",
            "a4b3",
            "g7h8",
            "b3a2",
            "b1a1",
            "b8c6",
            "f1b5",
            "c8d7",
            "g1f3",
            "e7c5",
            "e4c4",
            "c5f2",
            "h1f1",
            "f2g2",
            "f3e5",
            "c6e5",
            "h8e5",
            "c7c6",
            "c4f4",
            "e8c8",
            "f4a4"
    };

    int i = 0;
    while(game.is_game_going()) {
        board.move(moves[i]);
        i++;
    }
    cout << board.winner() << endl;
}