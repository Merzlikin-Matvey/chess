#pragma once

#include <cstdint>

#include "board.hpp"

namespace chess::engine {
    int evaluate_position(Board& board, uint8_t color);
}
