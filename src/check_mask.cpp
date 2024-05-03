#include "headers/board.hpp"
#include "headers/masks.hpp"
#include "headers/bitboard_operations.hpp"
#include "headers/constants.hpp"
#include "headers/board.hpp"
#include "headers/bitboard_lines.hpp"

#include <iostream>

std::pair<Bitboard, Bitboard> masks::get_check_mask(chess::Board& board, uint8_t side) {
    Bitboard hv_mask = 0, d_mask = 0, direction = 0, line;
    int first, last, opponent, count;
    uint8_t king_index = bitboard_operations::bitScanForward(board.piece_bitboards[side][chess::King]);
    Bitboard queen_rook = board.piece_bitboards[!side][chess::Queen] | board.piece_bitboards[!side][chess::Rook];
    Bitboard queen_bishop = board.piece_bitboards[!side][chess::Bishop] | board.piece_bitboards[!side][chess::Queen];



    return {hv_mask, d_mask};

}
