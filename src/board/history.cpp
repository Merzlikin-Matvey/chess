#include "headers/board.hpp"

void chess::Board::add_hash_to_history(zobrist::ZobristHash hash) { hashes.push_back(hash); }

void chess::Board::add_hash_to_history() { hashes.push_back(zobrist::ZobristHash(*this)); }

void chess::Board::clear_history() { hashes.clear(); }

uint8_t chess::Board::get_num_of_repetitions() {
    zobrist::ZobristHash current_hash = hashes.back();
    int repetitions = 0;
    for (auto hash : hashes) {
        if (hash == current_hash) {
            repetitions++;
        }
    }
    return repetitions;
}
