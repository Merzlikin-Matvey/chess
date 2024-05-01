#ifndef CHESS_MAGIC_NUMBERS_H
#define CHESS_MAGIC_NUMBERS_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

const uint64_t _generate_random_64bit();


uint64_t generate_rook_magic_number(uint8_t square);
void generate_rook_magic_numbers(uint64_t* magic_numbers);

uint64_t generate_bishop_magic_number(uint8_t square);
void generate_bishop_magic_numbers(uint64_t* magic_numbers);

#ifdef __cplusplus
}
#endif

#endif //CHESS_MAGIC_NUMBERS_H