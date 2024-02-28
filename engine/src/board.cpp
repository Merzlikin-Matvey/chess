#include "main.h"

#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include "../dependencies/json.hpp"

using namespace std;
using json = nlohmann::json;


Figure* Board::figure_by_position(pair<int, int> position) {
    for (auto figure : figures) {
        if (figure->position == position) {
            return figure;
        }
    }
    return new NullFigure(this);
}
void Board::print(){
    Pawn(this, make_pair(2, 2), "black");
    vector<vector<string>> board(8, vector<string>(8, "."));
    for (auto figure : figures) {
        cout << figure->color << endl;
    }

    for (auto row : board){
        for (auto sym : row){
            cout << sym << ' ';
        }
        cout << endl;
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

string Board::move(pair<int, int> pos1, pair<int, int> pos2){
    if (turn == figure_by_position(pos1)->color){
        Figure* figure = figure_by_position(pos1);
        auto pawn = dynamic_cast<Pawn*>(figure);
        auto rook = dynamic_cast<Rook*>(figure);
        auto knight = dynamic_cast<Knight*>(figure);
        auto bishop = dynamic_cast<Bishop*>(figure);
        auto queen = dynamic_cast<Queen*>(figure);
        auto king = dynamic_cast<King*>(figure);

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
            } else {
                cout << "Invalid move" << endl;
            }
        }
        else {
            cout << "Figure not found" << endl;
        }

        this->change_turn();
    }
    return "moved";
}


void Board::put_figure(Figure* figure){
    figures.push_back(figure);
}

void Board::encode_from_json(std::string path, Board& board) {
    ifstream file(path);
    json data;
    file >> data;
    file.close();

    for (auto figure : data["figures"]){
        if (figure["name"] == "pawn"){
            Pawn(&board, make_pair(2, 2), "black");
        }
    }
}

bool Board::is_empty(pair<int, int> position) {
    return figure_by_position(position)->name != "null";
}

string Board::position_to_chess_notation(pair<int, int> position) {
    string letters = "abcdefgh";
    string numbers = "87654321";
    return string(1, letters[position.second]) + string(1, numbers[position.first]);
}

string Board::move_to_chess_notation(pair<int, int> position1, pair<int, int> position2) {
    return position_to_chess_notation(position1) + position_to_chess_notation(position2);
}

pair<int, int> Board::position_to_number_notation(string notation) {
    string letters = "abcdefgh";
    string numbers = "87654321";
    return make_pair(numbers.find(notation[1]), letters.find(notation[0]));
}

pair<pair<int, int>, pair<int, int>> Board::move_to_number_notation(string notation1, string notation2) {
    return make_pair(position_to_number_notation(notation1), position_to_number_notation(notation2));
}