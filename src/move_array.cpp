#include "headers/move.hpp"

chess::MoveArray::MoveArray() {
    this->size = 0;
}

void chess::MoveArray::push_back(chess::Move move) {
    this->moves[this->size] = move;
    this->size++;
}

void chess::MoveArray::clear() {
    this->size = 0;
    this->moves = {};
}

