#include "main.h"

#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <nlohmann/json.hpp>

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

void Board::move(pair<int, int> pos1, pair<int, int> pos2, bool castling){
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
                return;
            }
        }
        else if (rook) {
            auto available_moves = rook->available_moves();
            if (not available_moves.empty() and find(available_moves.begin(), available_moves.end(), pos2) != available_moves.end()) {
                rook->move(pos2);
            } else {
                cout << "Invalid move" << endl;
                return;
            }
        }
        else if (knight) {
            auto available_moves = knight->available_moves();
            if (not available_moves.empty() and find(available_moves.begin(), available_moves.end(), pos2) != available_moves.end()) {
                knight->move(pos2);
            } else {
                cout << "Invalid move" << endl;
                return;
            }
        }
        else if (bishop) {
            auto available_moves = bishop->available_moves();
            if (not available_moves.empty() and find(available_moves.begin(), available_moves.end(), pos2) != available_moves.end()) {
                bishop->move(pos2);
            } else {
                cout << "Invalid move" << endl;
                return;
            }
        }
        else if (queen) {
            auto available_moves = queen->available_moves();
            if (not available_moves.empty() and find(available_moves.begin(), available_moves.end(), pos2) != available_moves.end()) {
                queen->move(pos2);
            } else {
                cout << "Invalid move" << endl;
                return;
            }
        }
        else if (king) {
            auto available_moves = king->available_moves();
            if (not available_moves.empty() and find(available_moves.begin(), available_moves.end(), pos2) != available_moves.end()) {
                king->move(pos2);
            } else {
                cout << "Invalid move" << endl;
                return;
            }
        }
        else {
            cout << "Figure not found" << endl;
            return;
        }

        this->change_turn();
    }
}


void Board::put_figure(Figure& figure){
    figures.push_back(&figure);
}

void Board::encode_from_json(std::string path, Board& board) {
    ifstream file(path);
    json data;
    file >> data;
    file.close();

    for (auto figure : data["figures"]){
        if (figure["name"] == "pawn"){
            cout << "abobaS" << endl;
            Pawn(&board, make_pair(1, 1), "white");
        }
    }
}

bool Board::is_empty(pair<int, int> position) {
    return figure_by_position(position)->name != "null";
}







