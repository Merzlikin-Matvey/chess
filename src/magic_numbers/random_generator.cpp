#include "headers/magic_numbers_ganaration/magic_numbers.h"
#include <stdlib.h>

Bitboard _generate_random_64bit() {
    Bitboard number = 0;
    for (int i = 0; i < 4; ++i) {
        number <<= 16;
        number |= rand();
    }
    return number;
}