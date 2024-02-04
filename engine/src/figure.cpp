#include "main.h"

Figure::Figure(Board *initialBoard, std::string initialName, std::pair<int, int> initialPosition, string initialColor) {
    board = initialBoard;
    name = initialName;
    position = initialPosition;
    color = initialColor;
}

void Figure::move(std::pair<int, int> new_position) {
    position = new_position;
}

void Figure::kill() {

}


