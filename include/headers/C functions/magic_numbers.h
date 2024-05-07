#ifndef CHESS_MAGIC_NUMBERS_HCHESS_MAGIC_NUMBERS_H
#define CHESS_MAGIC_NUMBERS_H

#include <stdint.h>
#include <stdbool.h>

typedef uint64_t Bitboard;

extern Bitboard _generate_random_64bit();
extern Bitboard _generate_bishop_magic_number(uint8_t square);
extern Bitboard _generate_rook_magic_number(uint8_t square);
extern Bitboard _generate_vertical_pin_magic_number(uint8_t square);
extern Bitboard _generate_horizontal_pin_magic_number(uint8_t square);
extern Bitboard _generate_up_right_pin_magic_number(uint8_t square);
extern Bitboard _generate_down_right_pin_magic_number(uint8_t square);
extern Bitboard _set_down_right_pin_board(uint8_t square, uint8_t blockers);
extern Bitboard _set_up_right_pin_board(uint8_t square, uint8_t blockers);
extern bool is_down_right_pin_magic_number_valid(uint8_t square, uint64_t magic_number);
extern uint8_t _get_number_of_down_right_pin_mask_bits(uint8_t square);
extern uint8_t _get_number_of_up_right_pin_mask_bits(uint8_t square);
#endif //CHESS_MAGIC_NUMBERS_H