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
    already_moved = true;
    position = new_position;
}

bool Figure::is_null(){
    return this->name == "null";
}

bool Figure::is_empty(pair<int, int> position) {
    if (position.first > 7 or position.second > 7 or position.first < 0 or position.second < 0){
        return false;
    }
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

vector<pair<int, int>> Pawn::available_moves(){
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


Rook::Rook(Board *initialBoard, pair<int, int> position, string color) :
        Figure(initialBoard, "rook", position, color, (color == "white") ? "r" : "R") {}

vector<pair<int, int>> Rook::available_moves(){
    vector<pair<int, int>> moves {};
    int i;

    i = 1;
    while (is_empty(make_pair(position.first + i, position.second))){
        moves.push_back(make_pair(position.first + i, position.second));
        i++;
    }
    if (is_opponent(make_pair(position.first + i, position.second))){
        moves.push_back(make_pair(position.first + i, position.second));
    }

    i = 1;
    while (is_empty(make_pair(position.first - i, position.second))){
        moves.push_back(make_pair(position.first - i, position.second));
        i++;
    }




    return moves;

}