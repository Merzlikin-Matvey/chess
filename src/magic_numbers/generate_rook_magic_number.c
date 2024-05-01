#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "headers/C functions/magic_numbers.h"
#include "headers/C functions/bitboard_operations.h"




uint64_t generate_rook_magic_number(uint8_t square) {
    Bitboard board = 0;
    uint8_t start_index = (square / 8) * 8 + 1;
    uint8_t end_index = (square / 8) * 8 + 7;

    for (uint8_t i = start_index; i < end_index; i++) {
        if (i != square) {
            _c_bitboard_operations_set_1(&board, i);
        }
    }

    start_index = square % 8 + 8;
    end_index = 63 - (7 - square % 8);

    for (uint8_t i = start_index; i < end_index; i += 8) {
        if (i != square) {
            _c_bitboard_operations_set_1(&board, i);
        }
    }


    uint64_t number = 0;
    uint64_t magic = 0;
    while (number != 1023){
        magic = _generate_random_64bit() & _generate_random_64bit() & _generate_random_64bit();
        number = (magic * board) >> 54;
    }

    return magic;
}

void generate_rook_magic_numbers(uint64_t* magic_numbers) {
    for (uint8_t square = 0; square < 64; square++) {
        magic_numbers[square] = generate_rook_magic_number(square);
    }
}