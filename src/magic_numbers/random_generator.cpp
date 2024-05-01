#include "headers/C functions/magic_numbers.h"

#include <stdlib.h>


const uint64_t _generate_random_64bit() {
    uint64_t number = 0;
    for (int i = 0; i < 4; ++i) {
        number <<= 16;
        number |= rand();
    }
    return number;
}