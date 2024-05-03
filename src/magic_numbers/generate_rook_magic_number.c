#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

#include "headers/C functions/magic_numbers.h"
#include "headers/C functions/bitboard_operations.h"

int _c_bitboard_operations_get_bit(Bitboard board, int i) {
    return (board >> i) & 1;
}


#include <stdio.h>

void _с_print_bitboard(Bitboard bitboard) {
    for (int8_t y = 7; y >= 0; y = y - 1) {
        for (uint8_t x = 0; x < 8; x = x + 1) {
            if (_c_bitboard_operations_get_bit(bitboard, y * 8 + x)) {
                printf("1");
            }
            else {
                printf("0");
            }
        }
        printf("\n");
    }
}

uint64_t generate_rook_magic_number(uint8_t square) {
    Bitboard board = 0;
    uint8_t start_index = square / 8 * 8 + 1;
    uint8_t end_index = start_index + 6;
    uint8_t num_bits = 0;

    for (uint8_t i = start_index; i < end_index; i++) {
        if (i != square) {
            _c_bitboard_operations_set_1(&board, i);
            num_bits++;
        }
    }

    start_index = square % 8 + 8;
    end_index = 56 + square % 8 - 8;

    for (uint8_t i = start_index; i <= end_index; i += 8) {
        if (i != square) {
            _c_bitboard_operations_set_1(&board, i);
            num_bits++;
        }
    }


    uint64_t number = 0;
    uint64_t magic = 0;
    do {
        magic = _generate_random_64bit() & _generate_random_64bit() & _generate_random_64bit();
        number = (magic * board) >> (64 - num_bits);
    } while (number != pow(2, num_bits) - 1);

    return magic;
}

void generate_rook_magic_numbers(uint64_t* magic_numbers) {
    for (uint8_t square = 0; square < 64; square++) {
        magic_numbers[square] = generate_rook_magic_number(square);
    }
}