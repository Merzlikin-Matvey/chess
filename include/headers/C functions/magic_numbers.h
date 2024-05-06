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

#endif //CHESS_MAGIC_NUMBERS_H