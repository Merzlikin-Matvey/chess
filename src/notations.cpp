#include "headers/notations.hpp"

std::string chess::position_to_chess_notation(uint8_t position){
    std::string notation = "";
    notation += (char)('a' + (position % 8));
    notation += (char)('1' + (position / 8));
    return notation;
}

uint8_t chess::position_to_number_notation(std::string notation){
    return (notation[0] - 'a') + 8 * (notation[1] - '1');
}