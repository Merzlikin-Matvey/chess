#include "chess-engine/chess-engine.h"

#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <filesystem>
#include "../dependencies/nlohmann/json/json-master/single_include/nlohmann/json.hpp"

using namespace std;
using json = nlohmann::json;
namespace fs = std::filesystem;
using namespace chess;

Figure* Board::figure_by_position(pair<int, int> position) {
    for (auto figure : figures) {
        if (figure->position == position) {
            return figure;
        }
    }
    return new NullFigure(this);
}

void Board::clear_null_figures() {
    figures.erase(remove_if(figures.begin(), figures.end(), [](Figure* figure) { return figure->name == "null"; }), figures.end());
}

void Board::print(){
    clear_null_figures();
    vector<vector<string>> board(8, vector<string>(8, "."));
    for (Figure* figure : figures) {
        board[figure->position.first][figure->position.second] = figure->symbol;
    }
    for (const auto &row : board) {
        for (const auto &cell : row) {
            cout << cell << ' ';
        }
        cout << '\n';
    }
}

void Board::info() {
    clear_null_figures();
    for (auto figure : figures) {
        cout << figure->name << " " << figure->color << " " << position_to_chess_notation(figure->position) << endl;
    }
}

void Board::change_turn(){
    if (this->turn == "white"){
        this->turn = "black";
    }
    else {
        this->turn = "white";
    }
}

void Board::kill(std::pair<int, int> position) {
    auto fig = figure_by_position(position);

    if (not fig->is_null()) {
        auto it = std::find(figures.begin(), figures.end(), fig);
        if (it != figures.end()) {
            delete *it;
            figures.erase(it);
        }
    }
}

bool Board::is_сastling(pair<int, int> pos1, pair<int, int> pos2) {
    auto king = dynamic_cast<King*>(figure_by_position(pos1));
    if (king) {
        return abs(pos1.second - pos2.second) == 2;
    }
    return false;
}

string Board::move(pair<int, int> pos1, pair<int, int> pos2){
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
                pawn->move(pos2);
            } else {
                cout << "Invalid move" << endl;
            }
        }
        else if (rook) {
            auto available_moves = rook->available_moves();
            if (not available_moves.empty() and find(available_moves.begin(), available_moves.end(), pos2) != available_moves.end()) {
                rook->move(pos2);
            } else {
                cout << "Invalid move" << endl;
            }
        }
        else if (knight) {
            auto available_moves = knight->available_moves();
            if (not available_moves.empty() and find(available_moves.begin(), available_moves.end(), pos2) != available_moves.end()) {
                knight->move(pos2);
            } else {
                cout << "Invalid move" << endl;
            }
        }
        else if (bishop) {
            auto available_moves = bishop->available_moves();
            if (not available_moves.empty() and find(available_moves.begin(), available_moves.end(), pos2) != available_moves.end()) {
                bishop->move(pos2);
            } else {
                cout << "Invalid move" << endl;
            }
        }
        else if (queen) {
            auto available_moves = queen->available_moves();
            if (not available_moves.empty() and find(available_moves.begin(), available_moves.end(), pos2) != available_moves.end()) {
                queen->move(pos2);
            } else {
                cout << "Invalid move" << endl;
            }
        }
        else if (king) {
            auto available_moves = king->available_moves();
            if (not available_moves.empty() and find(available_moves.begin(), available_moves.end(), pos2) != available_moves.end()) {
                king->move(pos2);
                // Если рокировка, то двинем и башенку
                if (is_сastling(pos1, pos2)) {
                    if (pos2.first == 0) {
                        auto rook = dynamic_cast<Rook*>(figure_by_position(make_pair(0, 0)));
                        rook->move(make_pair(0, 3));
                    } else {
                        auto rook = dynamic_cast<Rook*>(figure_by_position(make_pair(7, 0)));
                        rook->move(make_pair(7, 3));
                    }
                }



            } else {
                cout << "Invalid move" << endl;
            }
        }
        else {
            cout << "figure not found" << endl;
        }
        this->change_turn();
    }
    else{
        cout << "Not your turn" << endl;
    }
    return "moved";
}


// Импортируем JSON файл с позициями фигур
void Board::import_json(std::string path) {
    auto abs_path = fs::absolute(path);
    cout << abs_path << endl;
    ifstream file(abs_path);
    json data;
    Board& Board = *this;
    file >> data;
    file.close();

    for (auto figure : data["figures"]){
        if (figure["name"] == "pawn"){
            this->figures.push_back(new Pawn(&Board, position_to_number_notation(figure["position"]), figure["color"]));
        }
        else if (figure["name"] == "rook"){
            this->figures.push_back(new Rook(&Board, position_to_number_notation(figure["position"]), figure["color"]));
        }
        else if (figure["name"] == "knight"){
            this->figures.push_back(new Knight(&Board, position_to_number_notation(figure["position"]), figure["color"]));
        }
        else if (figure["name"] == "bishop"){
            this->figures.push_back(new Bishop(&Board, position_to_number_notation(figure["position"]), figure["color"]));
        }
        else if (figure["name"] == "queen"){
            this->figures.push_back(new Queen(&Board, position_to_number_notation(figure["position"]), figure["color"]));
        }
        else if (figure["name"] == "king"){
            this->figures.push_back(new King(&Board, position_to_number_notation(figure["position"]), figure["color"]));
        }
        else {
            cout << "Invalid figure name" << endl;
        }

    }
}

// Дефолтные позиции фигур
void Board::load_default_positions() {
    this->import_json("chess_default_positions.json");
}

// Является ли позиция пустой
bool Board::is_empty(pair<int, int> position) {
    return figure_by_position(position)->name == "null";
}

// Перевод в шахматную нотацию
string Board::position_to_chess_notation(pair<int, int> position) {
    string letters = "abcdefgh";
    string numbers = "87654321";
    return string(1, letters[position.second]) + string(1, numbers[position.first]);
}

string Board::move_to_chess_notation(pair<int, int> position1, pair<int, int> position2) {
    return position_to_chess_notation(position1) + position_to_chess_notation(position2);
}

string Board::move_to_chess_notation(pair<pair<int, int>, pair<int, int>> move) {
    return move_to_chess_notation(move.first, move.second);
}

pair<int, int> Board::position_to_number_notation(string notation) {
    string letters = "abcdefgh";
    string numbers = "87654321";
    return make_pair(numbers.find(notation[1]), letters.find(notation[0]));
}

// Перевод в численную нотацию
pair<pair<int, int>, pair<int, int>> Board::move_to_number_notation(string notation1, string notation2) {
    return make_pair(position_to_number_notation(notation1), position_to_number_notation(notation2));
}

vector<string> Board::available_moves() {
    vector<string> moves;
    for (auto figure : figures) {
        if (figure->color == turn) {
            for (auto move : figure->available_moves()) {
                moves.push_back(move_to_chess_notation(figure->position, move));
            }
        }
    }
    return moves;
}