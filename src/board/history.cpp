#include "headers/board.hpp"

void chess::Board::add_hash_to_history(const zobrist::ZobristHash hash) {
    hashes.push_back(hash);
}

void chess::Board::add_hash_to_history() {
    hashes.push_back(zobrist::ZobristHash(*this));
}

void chess::Board::clear_history() {
    hashes.clear();
}

uint8_t chess::Board::get_num_of_repetitions()const {
    const zobrist::ZobristHash current = hashes.back();
    int repetitions = 0;
    for (auto hash : hashes) {
        if (hash == current) {
            repetitions++;
        }
    }
    return repetitions;
}