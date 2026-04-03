#include "headers/uci.hpp"

#include <fstream>
#include <iostream>
#include <sstream>

#include "headers/board.hpp"

chess::uci::UCI::UCI() {
    ai_ = engine::AI(5);
    logs_path = "logs.txt";
    clear_logs();

    input_stream_ = &std::cin;
    output_stream_ = &std::cout;
}

std::string trim(const std::string &str) {
    size_t first = str.find_first_not_of(' ');
    if (std::string::npos == first) {
        return str;
    }
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}

void chess::uci::UCI::start_handle() {
    std::string line;
    while (true) {
        std::string command;
        *input_stream_ >> command;
        std::getline(*input_stream_, line);
        line = trim(line);
        add_log(command + " " + line, INPUT);

        if (command == "uci") {
            command_uci(line);
        } else if (command == "isready") {
            command_isready(line);
        } else if (command == "position") {
            command_position(line);
        } else if (command == "go") {
            command_go(line);
        } else if (command == "quit") {
            break;
        }
    }
}

void chess::uci::UCI::command_uci(std::string line) {
    send("id name ChessLib");
    send("id author Matvey Merzlikin");
    send("uciok");
}

void chess::uci::UCI::command_isready(std::string line) {
    send("readyok");
}

std::vector<std::string> split(const std::string &str, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(str);
    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

chess::uci::PositionCommandArgs parse_position_command(std::string line) {
    chess::uci::PositionCommandArgs args;

    std::vector<std::string> words = split(line, ' ');
    if (words[0] == "startpos") {
        args.type = "startpos";
        args.fen_string = "";
    } else if (words[0] == "fen") {
        args.type = "fen";
        args.fen_string = words[1] + " " + words[2] + " " + words[3] + " " + words[4] + " " + words[5] + " " + words[6];
    }
    
    for (size_t i = 0; i < words.size(); ++i) {
        if (words[i] == "moves") {
            args.moves_string = std::vector<std::string>(words.begin() + i + 1, words.end());
            break;
        }
    }
    return args;
}

void chess::uci::UCI::command_position(std::string line) {
    const auto args = parse_position_command(line);

    if (args.type == "startpos") {
        board_ = Board();
    } else if (args.type == "fen") {
        std::string fen;
        std::string token;
        for (int i = 0; i < 6; ++i) {
            *input_stream_ >> token;
            fen += token + " ";
        }
        board_ = Board(fen);
    }


    for (auto move_str : args.moves_string) {
        board_.get_legal_moves();
        board_.move(move_str);
        add_log(std::to_string(board_.white_turn) + " " + move_str, DEBUG);
    }
}

void chess::uci::UCI::command_go(std::string line) {
    add_log("searching move", DEBUG);
    auto move = ai_.search(board_);
    send("bestmove " + move);
}

std::string get_time() {
    std::time_t now = std::time(nullptr);
    std::tm* local_time = std::localtime(&now);
    char buffer[80];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", local_time);
    return std::string(buffer);
}

void chess::uci::UCI::send(std::string message) const {
    *output_stream_ << message << std::endl << std::flush;
    add_log(message, OUTPUT);
}


void chess::uci::UCI::add_log(std::string message, UCI_LOG_TYPE type) const {
    std::string time = get_time();
    std::string type_str;

    switch (type) {
        case DEBUG:
            type_str = "[DEBUG]";
            break;
        case INPUT:
            type_str = "[INPUT]";
            break;
        case OUTPUT:
            type_str = "[OUTPUT]";
            break;
    }
    std::string log = time + " " + type_str + " " + message;

    std::ofstream file(logs_path, std::ios::app);
    file << log << std::endl;
    file.close();
    file.flush();
}

void chess::uci::UCI::clear_logs() const{
    std::ofstream file(logs_path, std::ios::trunc);
    file.close();
}