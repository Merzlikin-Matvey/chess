#pragma once

#include <memory>
#include <string>

namespace chess{
    std::string position_to_chess_notation(uint8_t position);
    std::string move_to_chess_notation(uint8_t first, uint8_t second);
    uint8_t position_to_number_notation(std::string notation);
    uint8_t move_to_number_notation(std::string notation);
}
