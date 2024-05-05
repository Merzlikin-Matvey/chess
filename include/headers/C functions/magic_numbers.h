#ifndef CHESS_MAGIC_NUMBERS_H
#define CHESS_MAGIC_NUMBERS_H

#include <stdint.h>
#include <stdbool.h>

typedef uint64_t Bitboard;

extern Bitboard _set_rook_board(uint8_t square, uint16_t blockers);
extern Bitboard _set_bishop_board(uint8_t square, uint16_t blockers);
extern uint8_t _get_number_of_bishop_bits(uint8_t square);
extern bool _is_rook_magic_number_valid(uint64_t magic_number, uint8_t square);
extern bool _is_bishop_magic_number_valid(uint64_t magic_number, uint8_t square);
extern Bitboard _generate_random_64bit();
extern Bitboard _generate_bishop_magic_number(uint8_t square);
extern Bitboard _generate_rook_magic_number(uint8_t square);

#endif //CHESS_MAGIC_NUMBERS_H