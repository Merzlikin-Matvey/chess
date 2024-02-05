#ifndef MAIN_H
#define MAIN_H

#include <string>
#include <vector>
#include <utility>

using namespace std;

class Figure;

class Board {
public:
    std::vector<Figure> figures;

    Figure figure_by_position(std::pair<int, int> position);
    void kill(std::pair<int, int> position);
};

class Figure {
public:
    Figure(Board *initialBoard, std::string initialName, std::pair<int, int> initialPosition, string initialColor);

    Board *board;
    string name;
    string color;
    pair<int, int> position;


    void move(pair<int, int> new_position);
    void kill() const;
    bool is_empty(pair<int, int> position);
    bool is_teamate(pair<int, int> position);
    bool is_opponent(pair<int, int> position);
};

class NullFigure : public Figure{
public:
    explicit NullFigure(Board *initialBoard);
};

#endif
