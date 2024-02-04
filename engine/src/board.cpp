#include "main.h"

#include <iostream>
#include <vector>

using namespace std;


Figure Board::figure_by_position(std::pair<int, int> position) {
    for (auto figure : figures) {
        if (figure.position == position) {
            return figure;
        }
    }
}

