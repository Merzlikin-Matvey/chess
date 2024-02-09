#include "main.h"

using namespace std;

#include <string>


Figure::Figure(Board *initialBoard, string initialName, pair<int, int> initialPosition, string initialColor) {
    board = initialBoard;
    name = initialName;
    position = initialPosition;
    color = initialColor;
}

void Figure::move(pair<int, int> new_position) {
    position = new_position;
}

void Figure::kill() const {
    board->kill(this->position);
}

bool Figure::is_empty(pair<int, int> position) {
    return (board->figure_by_position(position).name == "null");
}

bool Figure::is_teamate(pair<int, int> position){
    return (board->figure_by_position(position).color == this->color);
}

bool Figure::is_opponent(pair<int, int> position) {
    return (board->figure_by_position(position).color != this->color);
}


NullFigure::NullFigure(Board *initialBoard) : Figure(initialBoard, "null", make_pair(-1, -1), "null") {}