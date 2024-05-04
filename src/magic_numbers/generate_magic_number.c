#include "headers/C functions/magic_numbers.h"

#include <math.h>
#include <stdio.h>

Bitboard _generate_magic_number(Bitboard board, uint8_t num_bits) {
    uint64_t number = 0;
    uint64_t magic = 0;
    do {
        magic = _generate_random_64bit() & _generate_random_64bit() & _generate_random_64bit();
        number = (magic * board) >> (64 - num_bits);
    } while (number != pow(2, num_bits) - 1);

    // Выведем number
    printf("Number: %llu\n", number);
    // Выведем num_bits
    printf("Num bits: %d\n", num_bits);

    return magic;
}