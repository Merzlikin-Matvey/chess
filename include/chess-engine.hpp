#pragma once

#include <string>
#include <vector>
#include <utility>

namespace chess {
    std::string get_path_to_res(std::string file_name);

    class Figure;

    class Board {
    public:
        Board();

        std::vector<Figure *> figures;
        std::string turn = "white";
        int num_of_history = 2;
        int max_num_of_moves = 100;
        int num_of_moves = 0;

        std::vector<Board> history;
        std::vector<std::string> moves;


        void info();
        void clear();
        void copy(Board* board);
        void save();
        void print();

        bool is_draw();
        std::string winner();
        bool is_check();
        bool is_checkmate();
        bool is_game_going();
        bool is_castling(std::pair<int, int> pos1, std::pair<int, int> pos2);

        void change_turn();
        void update_history();
        void clear_null_figures();

        std::string save_to_json(std::string path);
        void import_json(std::string path);
        void load_default_positions();

        std::string move(std::string move);
        std::vector <std::string> available_moves();
        void kill(std::pair<int, int> position);

        bool is_empty(std::pair<int, int> position);
        std::string move(std::pair<int, int> pos1, std::pair<int, int> pos2);

        Figure *figure_by_position(std::pair<int, int> position);

        std::string position_to_chess_notation(std::pair<int, int> position);
        std::pair<int, int> position_to_number_notation(std::string notation);
        std::string move_to_chess_notation(std::pair<std::pair<int, int>, std::pair<int, int>> move);
        std::string move_to_chess_notation(std::pair<int, int> position1, std::pair<int, int> position2);
        std::pair<std::pair<int, int>, std::pair<int, int>> move_to_number_notation(std::string notation1, std::string notation2);

    };

    class Figure {
    public:
        Figure(Board *initialBoard, std::string initialName, std::pair<int, int> initialPosition, std::string initialColor,
               std::string initialSymbol);


        Board *board;
        bool already_moved = false;
        bool double_moved = false;
        std::string name;
        std::string color;
        std::string symbol;
        std::pair<int, int> position;

        void move(std::pair<int, int> new_position);

        bool is_empty(std::pair<int, int> position);

        bool is_teammate(std::pair<int, int> position);

        bool is_opponent(std::pair<int, int> position);

        bool is_null();

        virtual std::vector<std::pair<int, int>> available_moves();
    };

    class NullFigure : public Figure {
    public:
        explicit NullFigure(Board *initialBoard);
    };

    class Pawn : public Figure {
    public:
        explicit Pawn(Board *initialBoard, std::pair<int, int> position, std::string color);

        void change_figure(std::string new_name);
        std::vector<std::pair<int, int>> available_moves() override;

    };

    class Rook : public Figure {
    public:
        explicit Rook(Board *initialBoard, std::pair<int, int> position, std::string color);

        std::vector<std::pair<int, int>> available_moves() override;
    };

    class Knight : public Figure {
    public:
        explicit Knight(Board *initialBoard, std::pair<int, int> position, std::string color);

        std::vector<std::pair<int, int>> available_moves() override;
    };

    class Bishop : public Figure {
    public:
        explicit Bishop(Board *initialBoard, std::pair<int, int> position, std::string color);

        std::vector<std::pair<int, int>> available_moves() override;
    };

    class Queen : public Figure {
    public:
        explicit Queen(Board *initialBoard, std::pair<int, int> position, std::string color);

        std::vector<std::pair<int, int>> available_moves() override;
    };

    class King : public Figure {
    public:
        explicit King(Board *initialBoard, std::pair<int, int> position, std::string color);

        std::vector<std::pair<int, int>> available_moves() override;
    };

}