#include <chess-engine.hpp>
#include <string>


chess::Figure::Figure(Board* initialBoard, std::string initialName, std::pair<int, int> initialPosition, std::string initialColor,
                      std::string initialSymbol)
        : board(initialBoard), name(initialName), position(initialPosition), color(initialColor), symbol(initialSymbol) {
}


void chess::Figure::move(std::pair<int, int> new_position) {
    already_moved = true;
    position = new_position;
}

bool chess::Figure::is_null(){
    return this->name == "null";
}

bool chess::Figure::is_empty(std::pair<int, int> position) {
    if (position.first > 7 or position.second > 7 or position.first < 0 or position.second < 0){
        return false;
    }
    return (board->figure_by_position(position)->name == "null");
}

bool chess::Figure::is_teammate(std::pair<int, int> position){
    return (this->color == board->figure_by_position(position)->color);
}

bool chess::Figure::is_opponent(std::pair<int, int> position) {
    auto figure = board->figure_by_position(position);
    return (figure->color != this->color and not figure->is_null());
}

std::vector<std::pair<int, int>> chess::Figure::available_moves() {
    return std::vector<std::pair<int, int>> {};
}

chess::NullFigure::NullFigure(Board* initialBoard) :
Figure(initialBoard, "null", std::make_pair(-1, -1), "null", "0") {}

chess::Pawn::Pawn(Board* initialBoard, std::pair<int, int> position, std::string color) :
Figure(initialBoard, "pawn", position, color, (color == "white") ? "P" : "p") {}

void chess::Pawn::change_figure(std::string new_name) {
    if (new_name == "queen"){
        board->figures.push_back(new Queen(board, position, color));
    }
    if (new_name == "rook"){
        board->figures.push_back(new Rook(board, position, color));
    }
    if (new_name == "bishop"){
        board->figures.push_back(new Bishop(board, position, color));
    }
    if (new_name == "knight"){
        board->figures.push_back(new Knight(board, position, color));
    }
    board->kill(position);
}

std::vector<std::pair<int, int>> chess::Pawn::available_moves(){
    std::vector<std::pair<int, int>> moves {};
    int direction = (color == "white") ? -1 : 1;

    if (is_empty(std::make_pair(position.first + direction, position.second))){
        moves.push_back(std::make_pair(position.first + direction, position.second));
    }

    if ((position.first == 6 and color == "white") or (position.first == 1 and color == "black")){
        if (is_empty(std::make_pair(position.first + 2 * direction, position.second))){
            moves.push_back(std::make_pair(position.first + 2 * direction, position.second));
        }
    }

    if (is_opponent(std::make_pair(position.first + direction, position.second + 1))){
        moves.push_back(std::make_pair(position.first + direction, position.second + 1));
    }
    if (is_opponent(std::make_pair(position.first + direction, position.second - 1))){
        moves.push_back(std::make_pair(position.first + direction, position.second - 1));
    }

    // Взятие в проходе
    if (is_opponent(std::make_pair(position.first, position.second + 1)) and
        board->figure_by_position(std::make_pair(position.first, position.second + 1))->name == "pawn" and
        dynamic_cast<Pawn*>(board->figure_by_position(std::make_pair(position.first, position.second + 1)))->double_moved and
            (this->position.first == 3 and this->color == "white") or (this->position.first == 4 and this->color == "black")){
        moves.push_back(std::make_pair(position.first + direction, position.second + 1));
    }

    if (is_opponent(std::make_pair(position.first, position.second - 1)) and
        board->figure_by_position(std::make_pair(position.first, position.second - 1))->name == "pawn" and
        dynamic_cast<Pawn*>(board->figure_by_position(std::make_pair(position.first, position.second - 1)))->double_moved and
            (this->position.first == 3 and this->color == "white") or (this->position.first == 4 and this->color == "black")){
        moves.push_back(std::make_pair(position.first + direction, position.second - 1));
    }
    return moves;
}


chess::Rook::Rook(Board* initialBoard, std::pair<int, int> position, std::string color) :
        Figure(initialBoard, "rook", position, color, (color == "white") ? "R" : "r") {}

std::vector<std::pair<int, int>> chess::Rook::available_moves(){
    std::vector<std::pair<int, int>> moves {};
    int i;

    i = 1;
    while (is_empty(std::make_pair(position.first + i, position.second))){
        moves.push_back(std::make_pair(position.first + i, position.second));
        i++;
    }
    if (is_opponent(std::make_pair(position.first + i, position.second))){
        moves.push_back(std::make_pair(position.first + i, position.second));
    }

    i = 1;
    while (is_empty(std::make_pair(position.first - i, position.second))){
        moves.push_back(std::make_pair(position.first - i, position.second));
        i++;
    }
    if (is_opponent(std::make_pair(position.first - i, position.second))){
        moves.push_back(std::make_pair(position.first - i, position.second));
    }

    i = 1;
    while (is_empty(std::make_pair(position.first, position.second + i))){
        moves.push_back(std::make_pair(position.first, position.second + i));
        i++;
    }
    if (is_opponent(std::make_pair(position.first, position.second + i))){
        moves.push_back(std::make_pair(position.first, position.second + i));
    }

    i = 1;
    while (is_empty(std::make_pair(position.first, position.second - i))){
        moves.push_back(std::make_pair(position.first, position.second - i));
        i++;
    }
    if (is_opponent(std::make_pair(position.first, position.second - i))){
        moves.push_back(std::make_pair(position.first, position.second - i));
    }

    return moves;

}

chess::Knight::Knight(Board* initialBoard, std::pair<int, int> position, std::string color) :
        Figure(initialBoard, "knight", position, color, (color == "white") ? "N" : "n") {}

std::vector<std::pair<int, int>> chess::Knight::available_moves(){
    std::vector<std::pair<int, int>> moves {};

    if (is_opponent(std::make_pair(position.first + 2, position.second + 1)) or
        is_empty(std::make_pair(position.first + 2, position.second + 1))){
        moves.push_back(std::make_pair(position.first + 2, position.second + 1));
    }
    if (is_opponent(std::make_pair(position.first + 2, position.second - 1)) or
        is_empty(std::make_pair(position.first + 2, position.second - 1))){
        moves.push_back(std::make_pair(position.first + 2, position.second - 1));
    }
    if (is_opponent(std::make_pair(position.first - 2, position.second + 1)) or
        is_empty(std::make_pair(position.first - 2, position.second + 1))){
        moves.push_back(std::make_pair(position.first - 2, position.second + 1));
    }
    if (is_opponent(std::make_pair(position.first - 2, position.second - 1)) or
        is_empty(std::make_pair(position.first - 2, position.second - 1))){
        moves.push_back(std::make_pair(position.first - 2, position.second - 1));
    }
    if (is_opponent(std::make_pair(position.first + 1, position.second + 2)) or
        is_empty(std::make_pair(position.first + 1, position.second + 2))){
        moves.push_back(std::make_pair(position.first + 1, position.second + 2));
    }
    if (is_opponent(std::make_pair(position.first + 1, position.second - 2)) or
        is_empty(std::make_pair(position.first + 1, position.second - 2))){
        moves.push_back(std::make_pair(position.first + 1, position.second - 2));
    }
    if (is_opponent(std::make_pair(position.first - 1, position.second + 2)) or
        is_empty(std::make_pair(position.first - 1, position.second + 2))){
        moves.push_back(std::make_pair(position.first - 1, position.second + 2));
    }
    if (is_opponent(std::make_pair(position.first - 1, position.second - 2)) or
        is_empty(std::make_pair(position.first - 1, position.second - 2))){
        moves.push_back(std::make_pair(position.first - 1, position.second - 2));
    }

    return moves;
}

chess::Bishop::Bishop(Board* initialBoard, std::pair<int, int> position, std::string color) :
        Figure(initialBoard, "bishop", position, color, (color == "white") ? "B" : "b") {}

std::vector<std::pair<int, int>> chess::Bishop::available_moves(){
    std::vector<std::pair<int, int>> moves {};
    int i;

    i = 1;
    while (is_empty(std::make_pair(position.first + i, position.second + i))){
        moves.push_back(std::make_pair(position.first + i, position.second + i));
        i++;
    }
    if (is_opponent(std::make_pair(position.first + i, position.second + i))){
        moves.push_back(std::make_pair(position.first + i, position.second + i));
    }

    i = 1;
    while (is_empty(std::make_pair(position.first + i, position.second - i))){
        moves.push_back(std::make_pair(position.first + i, position.second - i));
        i++;
    }
    if (is_opponent(std::make_pair(position.first + i, position.second - i))){
        moves.push_back(std::make_pair(position.first + i, position.second - i));
    }

    i = 1;
    while (is_empty(std::make_pair(position.first - i, position.second + i))){
        moves.push_back(std::make_pair(position.first - i, position.second + i));
        i++;
    }
    if (is_opponent(std::make_pair(position.first - i, position.second + i))){
        moves.push_back(std::make_pair(position.first - i, position.second + i));
    }

    i = 1;
    while (is_empty(std::make_pair(position.first - i, position.second - i))){
        moves.push_back(std::make_pair(position.first - i, position.second - i));
        i++;
    }
    if (is_opponent(std::make_pair(position.first - i, position.second - i))){
        moves.push_back(std::make_pair(position.first - i, position.second - i));
    }


    return moves;
}

chess::Queen::Queen(Board* initialBoard, std::pair<int, int> position, std::string color) :
        Figure(initialBoard, "queen", position, color, (color == "white") ? "Q" : "q") {}


std::vector<std::pair<int, int>> chess::Queen::available_moves(){
    std::vector<std::pair<int, int>> moves {};
    int i;

    i = 1;
    while (is_empty(std::make_pair(position.first + i, position.second))){
        moves.push_back(std::make_pair(position.first + i, position.second));
        i++;
    }
    if (is_opponent(std::make_pair(position.first + i, position.second))){
        moves.push_back(std::make_pair(position.first + i, position.second));
    }

    i = 1;
    while (is_empty(std::make_pair(position.first - i, position.second))){
        moves.push_back(std::make_pair(position.first - i, position.second));
        i++;
    }
    if (is_opponent(std::make_pair(position.first - i, position.second))){
        moves.push_back(std::make_pair(position.first - i, position.second));
    }

    i = 1;
    while (is_empty(std::make_pair(position.first, position.second + i))){
        moves.push_back(std::make_pair(position.first, position.second + i));
        i++;
    }
    if (is_opponent(std::make_pair(position.first, position.second + i))){
        moves.push_back(std::make_pair(position.first, position.second + i));
    }

    i = 1;
    while (is_empty(std::make_pair(position.first, position.second - i))){
        moves.push_back(std::make_pair(position.first, position.second - i));
        i++;
    }
    if (is_opponent(std::make_pair(position.first, position.second - i))){
        moves.push_back(std::make_pair(position.first, position.second - i));
    }

    i = 1;
    while (is_empty(std::make_pair(position.first + i, position.second + i))){
        moves.push_back(std::make_pair(position.first + i, position.second + i));
        i++;
    }
    if (is_opponent(std::make_pair(position.first + i, position.second + i))){
        moves.push_back(std::make_pair(position.first + i, position.second + i));
    }

    i = 1;
    while (is_empty(std::make_pair(position.first + i, position.second - i))){
        moves.push_back(std::make_pair(position.first + i, position.second - i));
        i++;
    }
    if (is_opponent(std::make_pair(position.first + i, position.second - i))){
        moves.push_back(std::make_pair(position.first + i, position.second - i));
    }

    i = 1;
    while (is_empty(std::make_pair(position.first - i, position.second + i))){
        moves.push_back(std::make_pair(position.first - i, position.second + i));
        i++;
    }
    if (is_opponent(std::make_pair(position.first - i, position.second - i))){
        moves.push_back(std::make_pair(position.first - i, position.second - i));
    }

    return moves;
}

chess::King::King(Board* initialBoard,std:: pair<int, int> position, std::string color) :
        Figure(initialBoard, "king", position, color, (color == "white") ? "K" : "k") {}


std::vector<std::pair<int, int>> chess::King::available_moves(){
    std::vector<std::pair<int, int>> moves {};

    if (is_opponent(std::make_pair(position.first + 1, position.second)) or
        is_empty(std::make_pair(position.first + 1, position.second))){
        moves.push_back(std::make_pair(position.first + 1, position.second));
    }
    if (is_opponent(std::make_pair(position.first - 1, position.second)) or
        is_empty(std::make_pair(position.first - 1, position.second))){
        moves.push_back(std::make_pair(position.first - 1, position.second));
    }
    if (is_opponent(std::make_pair(position.first, position.second + 1)) or
        is_empty(std::make_pair(position.first, position.second + 1))){
        moves.push_back(std::make_pair(position.first, position.second + 1));
    }
    if (is_opponent(std::make_pair(position.first + 1, position.second + 1)) or
        is_empty(std::make_pair(position.first + 1, position.second + 1))){
        moves.push_back(std::make_pair(position.first + 1, position.second + 1));
    }
    if (is_opponent(std::make_pair(position.first + 1, position.second - 1)) or
        is_empty(std::make_pair(position.first + 1, position.second - 1))){
        moves.push_back(std::make_pair(position.first + 1, position.second - 1));
    }
    if (is_opponent(std::make_pair(position.first - 1, position.second + 1)) or
        is_empty(std::make_pair(position.first - 1, position.second + 1))){
        moves.push_back(std::make_pair(position.first - 1, position.second + 1));
    }
    if (is_opponent(std::make_pair(position.first - 1, position.second - 1)) or
        is_empty(std::make_pair(position.first - 1, position.second - 1))){
        moves.push_back(std::make_pair(position.first - 1, position.second - 1));
    }
    if (is_opponent(std::make_pair(position.first, position.second - 1)) or
        is_empty(std::make_pair(position.first, position.second - 1))){
        moves.push_back(std::make_pair(position.first, position.second - 1));
    }

    // Рокировки

    if (not already_moved){
        if (is_empty(std::make_pair(position.first, position.second + 1)) and
            is_empty(std::make_pair(position.first, position.second + 2)) and
            board->figure_by_position(std::make_pair(position.first, position.second + 3))->name == "rook" and
            not board->figure_by_position(std::make_pair(position.first, position.second + 3))->already_moved){
            moves.push_back(std::make_pair(position.first, position.second + 2));
        }
        if (is_empty(std::make_pair(position.first, position.second - 1)) and
            is_empty(std::make_pair(position.first, position.second - 2)) and
            is_empty(std::make_pair(position.first, position.second - 3)) and
            board->figure_by_position(std::make_pair(position.first, position.second - 4))->name == "rook" and
            not board->figure_by_position(std::make_pair(position.first, position.second - 4))->already_moved){
            moves.push_back(std::make_pair(position.first, position.second - 2));
        }
    }

    return moves;
}
