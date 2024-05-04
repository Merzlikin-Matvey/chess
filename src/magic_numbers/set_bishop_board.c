#include "headers/C functions/magic_numbers.h"
#include "headers/C functions/bitboard_operations.h"

Bitboard _set_bishop_board(uint8_t square) {
    Bitboard board = 0;
    int i = square + 9;


    while ((i % 8 != 7) && (i <= 54)){
        if (i != square){
            _c_bitboard_operations_set_1(&board, i);
        }
        i += 9;
    }

    i = square ;
    while ((i % 8 != 0) && (i >= 9)){
        if (i != square){
            _c_bitboard_operations_set_1(&board, i);
        }
        i -= 9;
    }

    i = square;
    while ((i % 8 != 0) && (i <= 56)){
        if (i != square){
            _c_bitboard_operations_set_1(&board, i);
        }
        i += 7;
    }

    i = square;
    while ((i % 8 != 7) && (i >= 8)){
        if (i != square){
            _c_bitboard_operations_set_1(&board, i);
        }
        i -= 7;
    }








    return board;
}

uint8_t _get_number_of_bishop_bits(uint8_t square) {
    uint8_t count = 0;
    int i = square;

    while ((i % 8 != 7) && (i <= 54)){
        if (i != square){
            count++;
        }
        i += 9;
    }

    i = square ;
    while ((i % 8 != 0) && (i >= 9)){
        if (i != square){
            count++;
        }
        i -= 9;
    }

    i = square;
    while ((i % 8 != 0) && (i <= 56)){
        if (i != square){
            count++;
        }
        i += 7;
    }

    i = square;
    while ((i % 8 != 7) && (i >= 8)){
        if (i != square){
            count++;
        }
        i -= 7;
    }

    return count;
}

