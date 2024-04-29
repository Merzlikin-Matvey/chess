#include "headers/board.hpp"

void chess::Board::add_hash_to_history(zobrist::ZobristHash hash) {
    _hashes.push_back(hash);
}

void chess::Board::add_hash_to_history() {
    _hashes.push_back(zobrist::ZobristHash(*this));
}

void chess::Board::clear_history() {
    _hashes.clear();
}

uint8_t chess::Board::get_num_of_repetitions() {
    zobrist::ZobristHash current_hash = zobrist::ZobristHash(*this);
    int repetitions = 0;
    for (auto hash : _hashes) {
        if (hash == current_hash) {
            repetitions++;
        }
    }
    return repetitions;
}