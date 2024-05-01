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

    direction = masks::get_up_masks()[king_index];
    opponent = bitboard_operations::bitScanForward(direction & queen_rook);
    if (opponent != -1) {
        line = masks::_get_line(opponent, king_index);
        count = bitboard_operations::count_1(line & board.side_bitboards[side]);
        if (count == 1) {
            hv_mask |= line;
        }
    }

    // Down
    direction = masks::get_down_masks()[king_index];
    opponent = bitboard_operations::bitScanReverse(direction & queen_rook);
    if (opponent != -1) {
        line = masks::_get_line(opponent, king_index);
        count = bitboard_operations::count_1(line & board.side_bitboards[side]);
        if (count == 1) {
            hv_mask |= line;
        }
    }

    // Left
    direction = masks::get_left_masks()[king_index];
    opponent = bitboard_operations::bitScanReverse(direction & queen_rook);
    if (opponent != -1) {
        line = masks::_get_line(opponent, king_index);
        count = bitboard_operations::count_1(line & board.side_bitboards[side]);
        if (count == 1) {
            hv_mask |= line;
        }
    }

    // Right
    direction = masks::get_right_masks()[king_index];
    opponent = bitboard_operations::bitScanForward(direction & queen_rook);
    if (opponent != -1) {
        line = masks::_get_line(opponent, king_index);
        count = bitboard_operations::count_1(line & board.side_bitboards[side]);
        if (count == 1) {
            hv_mask |= line;
        }
    }

    // Up left
    direction = masks::get_up_left_masks()[king_index];
    opponent = bitboard_operations::bitScanReverse(direction & queen_bishop);
    if (opponent != -1) {
        line = masks::_get_line(opponent, king_index);
        count = bitboard_operations::count_1(line & board.side_bitboards[side]);
        if (count == 1) {
            d_mask |= line;
        }
    }

    // Up right
    direction = masks::get_up_right_masks()[king_index];
    opponent = bitboard_operations::bitScanForward(direction & queen_bishop);
    if (opponent != -1) {
        line = masks::_get_line(opponent, king_index);
        count = bitboard_operations::count_1(line & board.side_bitboards[side]);
        if (count == 1) {
            d_mask |= line;
        }
    }

    // Down left
    direction = masks::get_down_left_masks()[king_index];
    opponent = bitboard_operations::bitScanReverse(direction & queen_bishop);
    if (opponent != -1) {
        line = masks::_get_line(opponent, king_index);
        count = bitboard_operations::count_1(line & board.side_bitboards[side]);
        if (count == 1) {
            d_mask |= line;
        }
    }

    // Down right
    direction = masks::get_down_right_masks()[king_index];
    opponent = bitboard_operations::bitScanForward(direction & queen_bishop);
    if (opponent != -1) {
        line = masks::_get_line(opponent, king_index);
        count = bitboard_operations::count_1(line & board.side_bitboards[side]);
        if (count == 1) {
            d_mask |= line;
        }
    }


    return {hv_mask, d_mask};

}
