#include "headers/move.hpp"

chess::MoveArray::MoveArray() { this->_size = 0; }

void chess::MoveArray::push_back(chess::Move move) {
    this->moves[this->_size] = move;
    this->_size++;
}

void chess::MoveArray::clear() {
    for (int i = 0; i < size(); i++) {
        moves[i] = chess::Move();
    }
    _size = 0;
}

chess::Move& chess::MoveArray::operator[](int index) {
    if (index >= size() || index < 0) {
        throw std::out_of_range("Index out of range");
    }
    return moves[index];
}

const chess::Move& chess::MoveArray::operator[](int index) const {
    if (index >= size() || index < 0) {
        throw std::out_of_range("Index out of range");
    }
    return moves[index];
}
