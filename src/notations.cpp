#include "headers/notations.hpp"

std::string chess::position_to_chess_notation(uint8_t position) {
    std::string notation = "";
    notation += (char)('a' + (position % 8));
    notation += (char)('1' + (position / 8));
    return notation;
}

std::string chess::move_to_chess_notation(uint8_t first, uint8_t second) {
    return position_to_chess_notation(first) + position_to_chess_notation(second);
}

uint8_t chess::position_to_number_notation(std::string notation) {
    return (notation[0] - 'a') + 8 * (notation[1] - '1');
}

uint8_t chess::move_to_number_notation(std::string notation) {
    return position_to_number_notation(notation.substr(0, 2)) + 8 * position_to_number_notation(notation.substr(2, 2));
}
