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
    string turn = "white";

    Figure* figure_by_position(std::pair<int, int> position);
    void kill(std::pair<int, int> position);
    void change_turn();
    void move(pair<int, int> pos1, pair<int, int> pos2, bool castling);
    void print();
    void put_figure(Figure figure);
    bool is_empty(pair<int, int> position);

};

class Figure {
public:
    Figure(Board *initialBoard, string initialName, pair<int, int> initialPosition, string initialColor, string initialSymbol);


    Board *board;
    string name;
    string color;
    string symbol;
    pair<int, int> position;

    virtual void move(pair<int, int> new_position);
    void kill();
    bool is_empty(pair<int, int> position);
    bool is_teammate(pair<int, int> position);
    bool is_opponent(pair<int, int> position);
    virtual vector<pair<int, int>> available_moves();
};

class NullFigure : public Figure{
public:
    explicit NullFigure(Board *initialBoard);
};

class Pawn : public Figure{
public:
    explicit Pawn(Board *initialBoard, pair<int, int> position, string color);

    void move(pair<int, int> new_position);
    bool already_moved = false;
    vector<pair<int, int>> available_moves() override;

};

#endif
