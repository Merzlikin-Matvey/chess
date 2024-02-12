#include "main.h"

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


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
        board[figure->position.first][figure->position.second] = figure->symbol;
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
        Pawn* pawn = dynamic_cast<Pawn*>(figure);
        auto available_moves = vector<pair<int, int>> {};

        if (not pawn->is_null()) {
            pawn->move(pos2);
        } else {
            cout << "Figure not found!" << endl;
        }

        this->change_turn();
    }
}

void Board::put_figure(Figure& figure){
    figures.push_back(&figure);
}

bool Board::is_empty(pair<int, int> position) {
    return figure_by_position(position)->name != "null";
}





