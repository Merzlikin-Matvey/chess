#include "headers/C functions/magic_numbers.h"
#include "headers/C functions/bitboard_operations.h"

Bitboard _set_rook_board(uint8_t square) {
    Bitboard board = 0;
    uint8_t i = square;

    while (i < 56){
        if (i != square){
            _c_bitboard_operations_set_1(&board, i);
        }
        i += 8;
    }

    i = square;
    while (i > 7){
        if (i != square){
            _c_bitboard_operations_set_1(&board, i);
        }
        i -= 8;
    }

    i = square;
    while ((i % 8) != 7){
        if (i != square){
            _c_bitboard_operations_set_1(&board, i);
        }
        i++;
    }

    i = square;
    while ((i % 8) != 0){
        if (i != square){
            _c_bitboard_operations_set_1(&board, i);
        }
        i--;
    }

    return board;
}

uint8_t _get_number_of_rook_bits(uint8_t square) {
    uint8_t count = 0;
    int i = square;

    while (i < 56){
        if (i != square){
            count++;
        }
        i += 8;
    }

    i = square;
    while (i > 7){
        if (i != square){
            count++;
        }
        i -= 8;
    }

    i = square;
    while ((i % 8) != 7){
        if (i != square){
            count++;
        }
        i++;
    }

    i = square;
    while ((i % 8) != 0){
        if (i != square){
            count++;
        }
        i--;
    }

    return count;
}

