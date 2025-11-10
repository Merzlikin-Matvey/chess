#include "headers/uci.hpp"

#include <fstream>
#include <iostream>
#include <sstream>

#include "headers/board.hpp"

chess::uci::UCI::UCI() {
    ai_ = engine::AI(7);
    logs_path = "logs.txt";
}

void chess::uci::UCI::start_handle() {
    std::string command;
    while (std::cin >> command) {
        add_log(command);
        if (command == "uci") {
            command_uci();
        } else if (command == "isready") {
            command_isready();
        } else if (command == "position") {
            command_position();
        } else if (command == "go") {
            command_go();
        } else if (command == "quit") {
            break;
        }
    }
}

void chess::uci::UCI::command_uci() {
    std::cout << "id name ChessLib" << std::endl;
    std::cout << "id author Matvey Merzlikin" << std::endl;
    std::cout << "uciok" << std::endl;
}

void chess::uci::UCI::command_isready() {
    std::cout << "readyok" << std::endl;
}

void chess::uci::UCI::command_position() {
    std::string type;
    std::cin >> type;

    if (type == "startpos") {
        board_ = Board();
    } else if (type == "fen") {
        std::string fen;
        std::string token;
        for (int i = 0; i < 6; ++i) {
            std::cin >> token;
            fen += token + " ";
        }
        board_ = Board(fen);
    }

    if (std::cin.peek() == '\n') {
        std::cout << "No moves provided" << std::endl;
        std::cin.ignore();
        return;
    }


    std::string rest_of_line;
    std::getline(std::cin, rest_of_line);

    std::istringstream iss(rest_of_line);
    std::string move_str;

    while (iss >> move_str) {
        if (move_str == "moves") {
            continue;
        }
        board_.get_legal_moves();
        board_.move(move_str);
    }

    std::cout << "That's all" << std::endl;
}

void chess::uci::UCI::command_go() {
    std::cout << "searching..." << std::endl;
    auto move = ai_.search(board_);
    std::cout << "bestmove " << move << std::endl;

    if (std::cin.peek() == '\n') {
        return;
    }

    std::string rest_of_line;
    std::getline(std::cin, rest_of_line);
}

void chess::uci::UCI::add_log(std::string log) const {
    std::ofstream file(logs_path, std::ios::app);
    file << log << std::endl;
    file.close();
    file.flush();
}