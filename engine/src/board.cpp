#include "main.h"

#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <nlohmann/json.hpp>

using namespace std;
using json = nlohmann::json;


Figure* Board::figure_by_position(pair<int, int> position) {
    for (auto figure : figures) {
        if (figure->position == position) {
            return figure;
        }
    }
    return new NullFigure(*this);
}

void Board::print(){
    vector<vector<string>> board(8, vector<string>(8, "."));

    for (auto figure : figures){
        if (figure->name != "null"){
            board[figure->position.first][figure->position.second] = figure->symbol;
        }
    }

    int i = 8;
    for (auto row : board) {
        cout << i-- << " ";
        for (auto elem : row) {
            cout << elem << " ";
        }
        cout << endl;
    }

    cout << " ";
    for (auto letter : "abcdefgh") {
        cout << " " << letter;
    }

}

void Board::info(){
    cout << figures.size() << endl;
    for (auto figure : figures){
        cout << figure->name << endl;
        cout << figure->position.first << '-' << figure->position.second << endl;
        cout << endl;
    }
}

void Board::change_turn(){
    if (this->turn == "white"){
        this->turn = "black";
    }
    else {
        this->turn = "white";
    }
}

void Board::kill(std::pair<int, int> position) {
    auto fig = figure_by_position(position);

    if (not fig->is_null()) {
        auto it = std::find(figures.begin(), figures.end(), fig);
        if (it != figures.end()) {
            delete *it;
            figures.erase(it);
        }
    }
}

string Board::move(pair<int, int> pos1, pair<int, int> pos2, bool castling){
    if (turn == figure_by_position(pos1)->color){
        Figure* figure = figure_by_position(pos1);
        auto pawn = dynamic_cast<Pawn*>(figure);
        auto rook = dynamic_cast<Rook*>(figure);
        auto knight = dynamic_cast<Knight*>(figure);
        auto bishop = dynamic_cast<Bishop*>(figure);
        auto queen = dynamic_cast<Queen*>(figure);
        auto king = dynamic_cast<King*>(figure);

        if (pawn) {
            auto available_moves = pawn->available_moves();
            if (not available_moves.empty() and find(available_moves.begin(), available_moves.end(), pos2) != available_moves.end()) {
                pawn->move(pos2);
            } else {
                return "Invalid move";
            }
        }
        else if (rook) {
            auto available_moves = rook->available_moves();
            if (not available_moves.empty() and find(available_moves.begin(), available_moves.end(), pos2) != available_moves.end()) {
                rook->move(pos2);
            } else {
                return "Invalid move";
            }
        }
        else if (knight) {
            auto available_moves = knight->available_moves();
            if (not available_moves.empty() and find(available_moves.begin(), available_moves.end(), pos2) != available_moves.end()) {
                knight->move(pos2);
            } else {
                return "Invalid move";
            }
        }
        else if (bishop) {
            auto available_moves = bishop->available_moves();
            if (not available_moves.empty() and find(available_moves.begin(), available_moves.end(), pos2) != available_moves.end()) {
                bishop->move(pos2);
            } else {
                return "Invalid move";
            }
        }
        else if (queen) {
            auto available_moves = queen->available_moves();
            if (not available_moves.empty() and find(available_moves.begin(), available_moves.end(), pos2) != available_moves.end()) {
                queen->move(pos2);
            } else {
                return "Invalid move";
            }
        }
        else if (king) {
            auto available_moves = king->available_moves();
            if (not available_moves.empty() and find(available_moves.begin(), available_moves.end(), pos2) != available_moves.end()) {
                king->move(pos2);
            } else {
                return "Invalid move";
            }
        }
        else {
            return "Figure not found";
        }

        this->change_turn();
        return "Move";
    }
}

void Board::put_figure(Figure* figure){
    figures.push_back(figure);
}

void Board::encode_from_json(std::string path, Board& board) {
    ifstream file(path);
    json data;
    file >> data;
    file.close();

    Pawn* pawn;
    Rook* rook;
    Knight* knight;
    Bishop* bishop;
    Queen* queen;
    King* king;

    for (auto figure : data["figures"]){
        if (figure["name"] == "pawn"){
            pawn = new Pawn(board, to_number_notation(figure["position"]), figure["color"]);
            put_figure(pawn);
        }
        else if (figure["name"] == "rook"){
            rook = new Rook(board, to_number_notation(figure["position"]), figure["color"]);
            put_figure(rook);
        }
        else if (figure["name"] == "knight"){
            knight = new Knight(board, to_number_notation(figure["position"]), figure["color"]);
            put_figure(knight);
        }
        else if (figure["name"] == "bishop"){
            bishop = new Bishop(board, to_number_notation(figure["position"]), figure["color"]);
            put_figure(bishop);
        }
        else if (figure["name"] == "queen"){
            queen = new Queen(board, to_number_notation(figure["position"]), figure["color"]);
            put_figure(queen);
        }
        else if (figure["name"] == "king"){
            king = new King(board, to_number_notation(figure["position"]), figure["color"]);
            put_figure(king);
        }
    }

}

bool Board::is_empty(pair<int, int> position) {
    return figure_by_position(position)->name != "null";
}

string Board::to_chess_notation(pair<int, int> position) {
    string letters = "abcdefgh";
    string numbers = "87654321";
    return string() + letters[position.second] + numbers[position.first];
}

string Board::to_chess_notation(pair<int, int> position1, pair<int, int> position2) {
    return to_chess_notation(position1) + to_chess_notation(position2);
}

pair<int, int> Board::to_number_notation(string notation) {
    string letters = "abcdefgh";
    string numbers = "87654321";
    return make_pair(numbers.find(notation[1]), letters.find(notation[0]));
}

pair<pair<int, int>, pair<int, int>> Board::to_number_notation(string notation1, string notation2) {
    return make_pair(to_number_notation(notation1), to_number_notation(notation2));
}






