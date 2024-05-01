#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

#include "headers/C functions/magic_numbers.h"
#include "headers/C functions/bitboard_operations.h"

uint64_t generate_bishop_magic_number(uint8_t square) {
    uint8_t number_of_bits = 0;
    Bitboard board = 0;

    uint8_t start_index = square;
    while ((start_index >= 0) && (start_index <= 64)){
        start_index += 9;
        _c_bitboard_operations_set_1(&board, start_index);
        number_of_bits++;
    }

    uint8_t end_index = square;
    while ((start_index >= 0) && (start_index <= 64)){
        end_index -= 9;
        _c_bitboard_operations_set_1(&board, end_index);
        number_of_bits++;
    }

    start_index = square;
    while ((start_index >= 0) && (start_index <= 64)){
        start_index += 7;
        _c_bitboard_operations_set_1(&board, start_index);
        number_of_bits++;
    }

    end_index = square;
    while ((start_index >= 0) && (start_index <= 64)){
        end_index -= 7;
        _c_bitboard_operations_set_1(&board, end_index);
        number_of_bits++;
    }

    uint64_t number = 0;
    uint64_t magic = 0;
    while (number != pow(2, number_of_bits) - 1){
        magic = _generate_random_64bit() & _generate_random_64bit() & _generate_random_64bit();
        number = (magic * board) >> (64 - number_of_bits);
    }

    return magic;

}

void generate_bishop_magic_numbers(uint64_t* magic_numbers) {
    for (uint8_t square = 0; square < 64; square++) {
        magic_numbers[square] = generate_bishop_magic_number(square);
    }
}