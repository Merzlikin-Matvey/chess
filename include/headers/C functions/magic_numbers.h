#ifndef CHESS_MAGIC_NUMBERS_H
#define CHESS_MAGIC_NUMBERS_H

#include <stdint.h>

typedef uint64_t Bitboard;

extern Bitboard _generate_random_64bit();
extern Bitboard _generate_bishop_magic_number(uint8_t square);

#endif //CHESS_MAGIC_NUMBERS_H