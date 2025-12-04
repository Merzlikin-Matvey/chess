#pragma once

#include <memory>

namespace chess::masks {
    constexpr bool _get_bit(int n, int i) { return (n & (1 << i)) != 0; }

    constexpr uint16_t _pow2(uint8_t num) { return 1 << num; }
} // namespace chess::masks
