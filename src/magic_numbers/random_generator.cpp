#include "headers/bitboard_operations.hpp"
#include <cstdlib>
#include <cstdint>

namespace chess::magic_numbers {

Bitboard generate_random_64bit() {
    Bitboard number = 0;
    for (int i = 0; i < 4; ++i) {
        number <<= 16;
        number |= rand();
    }
    return number;
}

}  // namespace chess::magic_numbers
