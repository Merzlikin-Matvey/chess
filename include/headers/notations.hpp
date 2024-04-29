#pragma once

#include <memory>
#include <string>

namespace chess{
    std::string position_to_chess_notation(uint8_t position);
    uint8_t position_to_number_notation(std::string notation);
}
