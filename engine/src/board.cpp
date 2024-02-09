#include "main.h"

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


Figure Board::figure_by_position(std::pair<int, int> position) {
    for (auto figure : figures) {
        if (figure.position == position) {
            return figure;
        }
    }
    return NullFigure(this);
}

void Board::kill(std::pair<int, int> position) {
    auto it = find_if(figures.begin(), figures.end(), [position](const Figure& figure) {
        return figure.position == position;
    });

    if (it != figures.end()) {
        figures.erase(it);
    }
}




