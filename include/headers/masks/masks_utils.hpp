#pragma once

namespace chess::masks {
    constexpr bool _get_bit(const int n, const int i) {
        return (n & 1 << i) != 0;
    }

    constexpr uint16_t _pow2(const uint8_t num) {
        return 1 << num;
    }
}  // namespace chess::masks