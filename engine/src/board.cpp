#include "main.h"

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


Figure* Board::figure_by_position(std::pair<int, int> position) {
    for (Figure& figure : figures) {
        if (figure.position == position) {
            return &figure;
        }
    }
    return new NullFigure(this);
}

void Board::print(){
    vector<vector<string>> board(8, vector<string>(8, "."));
    for (auto figure : figures) {
        board[figure.position.first][figure.position.second] = figure.symbol;
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
    auto it = find_if(figures.begin(), figures.end(), [position](const Figure& figure) {
        return figure.position == position;
    });

    if (it != figures.end()) {
        figures.erase(it);
    }
}

void Board::move(pair<int, int> pos1, pair<int, int> pos2, bool castling){
    if (turn == figure_by_position(pos1)->color){
        auto available_moves = figure_by_position(pos1)->available_moves();
        for (auto move : available_moves){
            cout << move.first << ' ' << move.second << endl;
        }
        cout << endl;
        if (find(available_moves.begin(), available_moves.end(), pos2) != available_moves.end()){
            if (figure_by_position(pos2)->name != "null"){
                figure_by_position(pos2)->kill();
            }
            figure_by_position(pos1)->move(pos2);
        }
        this->change_turn();
    }
}

void Board::put_figure(Figure figure){
    this->figures.push_back(figure);
}

bool Board::is_empty(pair<int, int> position) {
    return figure_by_position(position)->name != "null";
}





