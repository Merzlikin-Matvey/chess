#pragma once

#include "chess-lib.hpp"


namespace chess::engine {
    double evaluate_position(Board& board, uint8_t color);
}
