#ifndef CHESS_MAGIC_NUMBERS_H
#define CHESS_MAGIC_NUMBERS_H

#include <stdint.h>


typedef uint64_t Bitboard;

extern uint64_t _generate_random_64bit();
extern Bitboard _generate_magic_number(Bitboard board, uint8_t num_bits);
extern Bitboard _set_rook_board(uint8_t square);
extern Bitboard _set_bishop_board(uint8_t square);
extern uint8_t _get_number_of_rook_bits(uint8_t square);
extern uint8_t _get_number_of_bishop_bits(uint8_t square);

extern Bitboard _c_generate_rook_magic_number(uint8_t square);
extern Bitboard _c_generate_bishop_magic_number(uint8_t square);


#endif //CHESS_MAGIC_NUMBERS_H