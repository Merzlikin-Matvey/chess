#include <chess-engine.hpp>

#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <filesystem>
#include <json/json.hpp>

namespace fs = std::filesystem;
using namespace std;
using json = nlohmann::json;


chess::Figure* chess::Board::figure_by_position(std::pair<int, int> position) {
    for (auto figure : figures) {
        if (figure->position == position) {
            return figure;
        }
    }
    return new NullFigure(this);
}

void chess::Board::clear_null_figures() {
    figures.erase(remove_if(figures.begin(), figures.end(), [](Figure* figure) { return figure->name == "null"; }), figures.end());
}

void chess::Board::print(){
    clear_null_figures();
    std::vector<std::vector<std::string>> board(8, std::vector<std::string>(8, "."));
    for (Figure* figure : figures) {
        board[figure->position.first][figure->position.second] = figure->symbol;
    }
    for (const auto &row : board) {
        for (const auto &cell : row) {
            std::cout << cell << ' ';
        }
        std::cout << '\n';
    }
}

void chess::Board::info() {
    for (auto figure : figures) {
        std::cout << figure->name << " " << figure->color << " " << position_to_chess_notation(figure->position) << std::endl;
    }
}

void chess::Board::change_turn(){
    if (this->turn == "white"){
        this->turn = "black";
    }
    else {
        this->turn = "white";
    }
}

void chess::Board::kill(std::pair<int, int> position) {
    auto fig = figure_by_position(position);

    if (not fig->is_null()) {
        auto it = std::find(figures.begin(), figures.end(), fig);
        if (it != figures.end()) {
            delete *it;
            figures.erase(it);
        }
    }
}

bool chess::Board::is_castling(std::pair<int, int> pos1, std::pair<int, int> pos2) {
    auto king = dynamic_cast<King*>(figure_by_position(pos1));
    if (king){
        if (king->already_moved) {
            return false;
        }
        if (pos1.first == 0 and pos1.second == 4 and pos2.first == 0 and pos2.second == 2) {
            auto rook = dynamic_cast<Rook*>(figure_by_position(std::make_pair(0, 0)));
            if (rook and not rook->already_moved) {
                return true;
            }
        }
        if (pos1.first == 0 and pos1.second == 4 and pos2.first == 0 and pos2.second == 6) {
            auto rook = dynamic_cast<Rook*>(figure_by_position(std::make_pair(0, 7)));
            if (rook and not rook->already_moved) {
                return true;
            }
        }
        if (pos1.first == 7 and pos1.second == 4 and pos2.first == 7 and pos2.second == 2) {
            auto rook = dynamic_cast<Rook*>(figure_by_position(std::make_pair(7, 0)));
            if (rook and not rook->already_moved) {
                return true;
            }
        }
        if (pos1.first == 7 and pos1.second == 4 and pos2.first == 7 and pos2.second == 6) {
            auto rook = dynamic_cast<Rook*>(figure_by_position(std::make_pair(7, 7)));
            if (rook and not rook->already_moved) {
                return true;
            }
        }
    }
    return false;
}

std::string chess::Board::move(std::pair<int, int> pos1, std::pair<int, int> pos2){
    if (turn == figure_by_position(pos1)->color){
        Figure* figure = figure_by_position(pos1);
        auto pawn = dynamic_cast<Pawn*>(figure);
        auto rook = dynamic_cast<Rook*>(figure);
        auto knight = dynamic_cast<Knight*>(figure);
        auto bishop = dynamic_cast<Bishop*>(figure);
        auto queen = dynamic_cast<Queen*>(figure);
        auto king = dynamic_cast<King*>(figure);

        // Поймем, какой фигурой ходим и сделаем ход
        if (pawn) {
            auto available_moves = pawn->available_moves();
            if (not available_moves.empty() and find(available_moves.begin(), available_moves.end(), pos2) != available_moves.end()) {
                if (abs(pos1.first - pos2.first) == 2) {
                    pawn->double_moved = true;
                }
                if (pos1.second != pos2.second and is_empty(pos2)) {
                    kill(std::make_pair(pos1.first, pos2.second));
                }
                pawn->move(pos2);
                moves.push_back(move_to_chess_notation(pos1, pos2));
                this->num_of_moves += 1;
                // TODO: Добавить изменение фигуры
            } else {
                std::cerr << "Invalid move " <<  move_to_chess_notation(pos1, pos2) <<std::endl;
                auto moves = this->available_moves();
                for (auto move : moves) {
                    std::cerr << move << std::endl;
                }
                this->print();
                return "invalid";
            }
        }
        else if (rook) {
            auto available_moves = rook->available_moves();
            if (not available_moves.empty() and find(available_moves.begin(), available_moves.end(), pos2) != available_moves.end()) {
                rook->move(pos2);
                moves.push_back(move_to_chess_notation(pos1, pos2));
                this->num_of_moves += 1;
            } else {
                std::cerr << "Invalid move " <<  move_to_chess_notation(pos1, pos2) <<std::endl;
                this->print();
                return "invalid";
            }
        }
        else if (knight) {
            auto available_moves = knight->available_moves();
            if (not available_moves.empty() and find(available_moves.begin(), available_moves.end(), pos2) != available_moves.end()) {
                knight->move(pos2);
                moves.push_back(move_to_chess_notation(pos1, pos2));
                this->num_of_moves += 1;
            } else {
                std::cerr << "Invalid move " <<  move_to_chess_notation(pos1, pos2) <<std::endl;
                this->print();
                return "invalid";
            }
        }
        else if (bishop) {
            auto available_moves = bishop->available_moves();
            if (not available_moves.empty() and find(available_moves.begin(), available_moves.end(), pos2) != available_moves.end()) {
                bishop->move(pos2);
                moves.push_back(move_to_chess_notation(pos1, pos2));
                this->num_of_moves += 1;
            } else {
                std::cerr << "Invalid move " <<  move_to_chess_notation(pos1, pos2) <<std::endl;
                this->print();
                return "invalid";
            }
        }
        else if (queen) {
            auto available_moves = queen->available_moves();
            if (not available_moves.empty() and find(available_moves.begin(), available_moves.end(), pos2) != available_moves.end()) {
                queen->move(pos2);
                moves.push_back(move_to_chess_notation(pos1, pos2));
                this->num_of_moves += 1;
            } else {
                std::cerr << "Invalid move " <<  move_to_chess_notation(pos1, pos2) <<std::endl;
                this->print();
                return "invalid";
            }
        }
        else if (king) {
            auto available_moves = king->available_moves();
            if (not available_moves.empty() and find(available_moves.begin(), available_moves.end(), pos2) != available_moves.end()) {
                this->num_of_moves += 1;

                if (is_castling(pos1, pos2)) {
                    if (pos1.first == 0 and pos1.second == 4 and pos2.first == 0 and pos2.second == 2) {
                        auto rook = dynamic_cast<Rook*>(figure_by_position(std::make_pair(0, 0)));
                        rook->move(std::make_pair(0, 3));
                    }
                    else if (pos1.first == 0 and pos1.second == 4 and pos2.first == 0 and pos2.second == 6) {
                        auto rook = dynamic_cast<Rook*>(figure_by_position(std::make_pair(0, 7)));
                        rook->move(std::make_pair(0, 5));
                    }
                    else if (pos1.first == 7 and pos1.second == 4 and pos2.first == 7 and pos2.second == 2) {
                        auto rook = dynamic_cast<Rook*>(figure_by_position(std::make_pair(7, 0)));
                        rook->move(std::make_pair(7, 3));
                    }
                    else if (pos1.first == 7 and pos1.second == 4 and pos2.first == 7 and pos2.second == 6) {
                        auto rook = dynamic_cast<Rook*>(figure_by_position(std::make_pair(7, 7)));
                        rook->move(std::make_pair(7, 5));
                    }
                }
                king->move(pos2);
                moves.push_back(move_to_chess_notation(pos1, pos2));
            } else {
                std::cerr << "Invalid move " <<  move_to_chess_notation(pos1, pos2) <<std::endl;
                this->print();
                return "invalid";

            }
        }
        else {
            std::cerr << "figure not found" << std::endl;
        }
        this->change_turn();
    }
    else{
        std::cerr << "Not your turn" << std::endl;
        std::cerr << "Current turn: " << this->turn << std::endl;
        std::cerr << "Figure color: " << figure_by_position(pos1)->color << std::endl;
        std::cerr << "Move: " << move_to_chess_notation(pos1, pos2) << std::endl;

    }
    return "moved";
}

std::string chess::Board::move(std::string chess_notation){
    return move(position_to_number_notation(chess_notation.substr(0, 2)),
                position_to_number_notation(chess_notation.substr(2, 4)));
}


// Импортируем JSON файл с позициями фигур
void chess::Board::import_json(std::string path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << path << std::endl;
        return;
    }
    json data;
    file >> data;
    file.close();

    for (auto figure : data["figures"]) {
        if (figure["name"] == "pawn") {
            this->figures.push_back(
                    new Pawn(this, this->position_to_number_notation(figure["position"]), figure["color"]));
        } else if (figure["name"] == "rook") {
            this->figures.push_back(
                    new Rook(this, this->position_to_number_notation(figure["position"]), figure["color"]));
        } else if (figure["name"] == "knight") {
            this->figures.push_back(
                    new Knight(this, this->position_to_number_notation(figure["position"]), figure["color"]));
        } else if (figure["name"] == "bishop") {
            this->figures.push_back(
                    new Bishop(this, this->position_to_number_notation(figure["position"]), figure["color"]));
        } else if (figure["name"] == "queen") {
            this->figures.push_back(
                    new Queen(this, this->position_to_number_notation(figure["position"]), figure["color"]));
        } else if (figure["name"] == "king") {
            this->figures.push_back(
                    new King(this, this->position_to_number_notation(figure["position"]), figure["color"]));
        } else {
            std::cerr << "Invalid figure name" << std::endl;
        }
    }
}

// Дефолтные позиции фигур
void chess::Board::load_default_positions() {
    this->import_json(get_path_to_res("chess_default_positions.json"));
}

// Является ли позиция пустой
bool chess::Board::is_empty(pair<int, int> position) {
    return figure_by_position(position)->name == "null";
}

// Перевод в шахматную нотацию
std::string chess::Board::position_to_chess_notation(std::pair<int, int> position) {
    std::string letters = "abcdefgh";
    std::string numbers = "87654321";
    return std::string(1, letters[position.second]) + std::string(1, numbers[position.first]);
}

std::string chess::Board::move_to_chess_notation(std::pair<int, int> position1, std::pair<int, int> position2) {
    return position_to_chess_notation(position1) + position_to_chess_notation(position2);
}

std::string chess::Board::move_to_chess_notation(std::pair<std::pair<int, int>, std::pair<int, int>> move) {
    return move_to_chess_notation(move.first, move.second);
}

std::pair<int, int> chess::Board::position_to_number_notation(std::string notation) {
    std::string letters = "abcdefgh";
    std::string numbers = "87654321";
    return std::make_pair(numbers.find(notation[1]), letters.find(notation[0]));
}

// Перевод в численную нотацию
std::pair<std::pair<int, int>, std::pair<int, int>> chess::Board::move_to_number_notation(std::string notation1, std::string notation2) {
    return std::make_pair(position_to_number_notation(notation1), position_to_number_notation(notation2));
}

std::vector<std::string> chess::Board::available_moves() {
    std::vector<std::string> moves;
    for (auto figure : figures) {
        if (figure->color == turn) {
            for (auto move : figure->available_moves()) {
                moves.push_back(move_to_chess_notation(figure->position, move));
            }
        }
    }
    return moves;
}

void chess::Board::save() {
    json data;
    data["turn"] = turn;
    for (auto figure : figures) {
        data["figures"].push_back({
            {"name", figure->name},
            {"color", figure->color},
            {"position", position_to_chess_notation(figure->position)}
        });
    }
    data["num_of_moves"] = num_of_moves;
    data["max_num_of_moves"] = max_num_of_moves;
    data["moves"] = moves;

    ofstream file(get_path_to_res("save.json"));
    file << data.dump(4);
    file.close();
}

void chess::Board::clear(){
    for (auto figure : figures) {
        delete figure;
    }
    this->figures.clear();
    this->moves.clear();
    this->turn = "white";
    this->num_of_moves = 0;
}

void chess::Board::copy(Board* board_to_copy) {
    this->clear();
    this->turn = board_to_copy->turn;
    this->num_of_moves = board_to_copy->num_of_moves;
    this->max_num_of_moves = board_to_copy->max_num_of_moves;

    for (auto figure : board_to_copy->figures) {
        if (!figure){
            continue;
        }
        if (figure->name == "pawn") {
            this->figures.push_back(
                    new Pawn(this, figure->position, figure->color));
        } else if (figure->name == "rook") {
            this->figures.push_back(
                    new Rook(this, figure->position, figure->color));
        } else if (figure->name == "knight") {
            this->figures.push_back(
                    new Knight(this, figure->position, figure->color));
        } else if (figure->name == "bishop") {
            this->figures.push_back(
                    new Bishop(this, figure->position, figure->color));
        } else if (figure->name == "queen") {
            this->figures.push_back(
                    new Queen(this, figure->position, figure->color));
        } else if (figure->name == "king") {
            this->figures.push_back(
                    new King(this, figure->position, figure->color));
        } else {
            std::cerr << "Invalid figure name" << std::endl;
        }
    }
}

void chess::Board::update_history() {
    if (history.size() == num_of_history) {
        history.erase(history.begin());
    }
    Board copy;
    copy.copy(this);
    history.push_back(copy);

}

bool chess::Board::is_check() {
    for (auto figure : figures) {
        if (figure->color != turn) {
            for (auto move : figure->available_moves()) {
                if (figure->name == "king" and is_castling(figure->position, move)) {
                    continue;
                }
                if (figure_by_position(move)->name == "king") {
                    return true;
                }
            }
        }
    }
    return false;
}

bool chess::Board::is_checkmate() {
    if (not is_check()) {
        return false;
    }
    for (auto figure : figures) {
        if (figure->color == turn) {
            for (auto move : figure->available_moves()) {
                Board new_board;
                new_board.copy(this);
                new_board.move(figure->position, move);
                if (not new_board.is_check()) {
                    return false;
                }
            }
        }
    }
    return true;
}

bool chess::Board::is_draw() {
    if (this->num_of_moves >= this->max_num_of_moves) {
        return true;
    }


    if (figures.size() == 2) {
        return true;
    }


    if (figures.size() == 3) {
        for (auto figure : figures) {
            if (figure->name == "knight" or figure->name == "bishop") {
                return true;
            }
        }
    }

    if (figures.size() == 4) {
        for (auto figure : figures) {
            if (figure->name == "knight" or figure->name == "bishop") {
                return true;
            }
        }
    }
    return false;
}

std::string chess::Board::winner() {
    if (is_checkmate()) {
        return turn == "white" ? "black" : "white";
    }
    if (is_draw()) {
        return "draw";
    }
    return "none";
}


bool chess::Board::is_game_going() {
    return winner() == "none";
}

chess::Board::Board() {
    clear();
}