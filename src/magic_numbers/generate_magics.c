#include "headers/C functions/magic_numbers.h"
#include "headers/C functions/bitboard_operations.h"

Bitboard _c_generate_rook_magic_number(uint8_t square) {
    Bitboard board = _set_rook_board(square);
    uint8_t num_bits = _get_number_of_rook_bits(square);
    return _generate_magic_number(board, num_bits);
}

Bitboard _c_generate_bishop_magic_number(uint8_t square) {
    Bitboard board = _set_bishop_board(square);
    uint8_t num_bits = _get_number_of_bishop_bits(square);
    return _generate_magic_number(board, num_bits);
}