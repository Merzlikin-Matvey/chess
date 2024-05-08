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
extern Bitboard _generate_up_right_pin_magic_number(uint8_t square);

extern void _fancy_print_up_right_pin_magic_numbers();
extern void _fancy_print_down_right_pin_magic_numbers();
extern void _fancy_print_horizontal_pin_magic_numbers();
extern void _fancy_print_vertical_pin_magic_numbers();


#endif //CHESS_MAGIC_NUMBERS_H