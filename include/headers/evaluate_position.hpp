#pragma once

#include <cstdint>

#include "board.hpp"

namespace chess::engine {
    double evaluate_position(Board& board, uint8_t color);
}