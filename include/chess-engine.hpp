#pragma once

#include <string>
#include <vector>
#include <utility>

using namespace std;

namespace chess {
    string get_path_to_res(string file_name);

    class Figure;

    class Board {
    public:
        std::vector<Figure *> figures;
        string turn = "white";
        int num_of_history = 7;

        vector<Board> history;


        void info();
        void save();
        void print();
        Board copy();
        void change_turn();
        void update_history();
        string move(string move);
        void clear_null_figures();
        void import_json(string path);
        void load_default_positions();
        vector <string> available_moves();
        bool is_empty(pair<int, int> position);
        void kill(std::pair<int, int> position);
        string move(pair<int, int> pos1, pair<int, int> pos2);
        Figure *figure_by_position(std::pair<int, int> position);
        string position_to_chess_notation(pair<int, int> position);
        bool is_сastling(pair<int, int> pos1, pair<int, int> pos2);
        pair<int, int> position_to_number_notation(string notation);
        string move_to_chess_notation(pair <pair<int, int>, pair<int, int>> move);
        string move_to_chess_notation(pair<int, int> position1, pair<int, int> position2);
        pair <pair<int, int>, pair<int, int>> move_to_number_notation(string notation1, string notation2);

    };

    class Figure {
    public:
        Figure(Board *initialBoard, string initialName, pair<int, int> initialPosition, string initialColor,
                    string initialSymbol);


        Board *board;
        bool already_moved = false;
        bool double_moved = false;
        string name;
        string color;
        string symbol;
        pair<int, int> position;

        void move(pair<int, int> new_position);

        bool is_empty(pair<int, int> position);

        bool is_teammate(pair<int, int> position);

        bool is_opponent(pair<int, int> position);

        bool is_null();

        virtual vector <pair<int, int>> available_moves();
    };

    class NullFigure : public Figure {
    public:
        explicit NullFigure(Board *initialBoard);
    };

    class Pawn : public Figure {
    public:
        explicit Pawn(Board *initialBoard, pair<int, int> position, string color);

        void change_figure(string new_name);
        vector <pair<int, int>> available_moves() override;

    };

    class Rook : public Figure {
    public:
        explicit Rook(Board *initialBoard, pair<int, int> position, string color);

        vector <pair<int, int>> available_moves() override;
    };

    class Knight : public Figure {
    public:
        explicit Knight(Board *initialBoard, pair<int, int> position, string color);

        vector <pair<int, int>> available_moves() override;
    };

    class Bishop : public Figure {
    public:
        explicit Bishop(Board *initialBoard, pair<int, int> position, string color);

        vector <pair<int, int>> available_moves() override;
    };

    class Queen : public Figure {
    public:
        explicit Queen(Board *initialBoard, pair<int, int> position, string color);

        vector <pair<int, int>> available_moves() override;
    };

    class King : public Figure {
    public:
        explicit King(Board *initialBoard, pair<int, int> position, string color);

        vector <pair<int, int>> available_moves() override;
    };

}