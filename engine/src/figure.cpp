#include "main.h"

#include <string>
#include <iostream>

using namespace std;


Figure::Figure(Board *initialBoard, string initialName, pair<int, int> initialPosition, string initialColor, string initialSymbol) {
    board = initialBoard;
    name = initialName;
    position = initialPosition;
    color = initialColor;
    symbol = initialSymbol;
}

void Figure::move(pair<int, int> new_position) {
    position = new_position;
}

void Figure::kill() {
    board->kill(this->position);
}

bool Figure::is_empty(pair<int, int> position) {
    return (board->figure_by_position(position)->name == "null");
}

bool Figure::is_teammate(pair<int, int> position){
    return (board->figure_by_position(position)->color == this->color);
}

bool Figure::is_opponent(pair<int, int> position) {
    auto figure = board->figure_by_position(position);
    return (figure->color != this->color and figure->name != "null");
}

vector<pair<int, int>> Figure::available_moves() {
    cout << "Bad" << endl;
    return vector<pair<int, int>> {};
}


NullFigure::NullFigure(Board *initialBoard) :
Figure(initialBoard, "null", make_pair(-1, -1), "null", "0") {}

Pawn::Pawn(Board *initialBoard, pair<int, int> position, string color) :
Figure(initialBoard, "pawn", position, color, (color == "white") ? "p" : "P") {}

vector<pair<int, int>> Pawn::available_moves() {
    cout << "Я тут" << endl;
    vector<pair<int, int>> moves;
    if (color == "white"){
        if (is_opponent(make_pair(this->position.first + 1, this->position.second + 1))){
            moves.push_back(make_pair(this->position.first + 1, this->position.second + 1));
        }
        if (is_opponent(make_pair(this->position.first + 1, this->position.second - 1))){
            moves.push_back(make_pair(this->position.first + 1, this->position.second + 1));
        }
        if (is_empty(make_pair(this->position.first + 1, this->position.second))){
            moves.push_back(make_pair(this->position.first + 1, this->position.second));
            if (not already_moved){
                if (is_empty(make_pair(this->position.first + 2, this->position.second))){
                    moves.push_back(make_pair(this->position.first + 2, this->position.second));
                }
            }
        }
    }

    else if (color == "black"){
        if (is_opponent(make_pair(this->position.first - 1, this->position.second + 1))){
            moves.push_back(make_pair(this->position.first - 1, this->position.second + 1));
        }
        if (is_opponent(make_pair(this->position.first - 1, this->position.second - 1))){
            moves.push_back(make_pair(this->position.first - 1, this->position.second + 1));
        }
        if (is_empty(make_pair(this->position.first - 1, this->position.second))){
            moves.push_back(make_pair(this->position.first - 1, this->position.second));
            if (not already_moved){
                if (is_empty(make_pair(this->position.first - 2, this->position.second))){
                    moves.push_back(make_pair(this->position.first - 2, this->position.second));
                }
            }
        }
    }
    return moves;
}

void Pawn::move(pair<int, int> new_position){
    already_moved = false;
    position = new_position;
    cout << position.first << ' ' << position.second << endl;
}
