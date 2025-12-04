#include "headers/bitboard_operations.hpp"
#include "headers/board.hpp"
#include "headers/constants.hpp"

void chess::Board::pawn_mask_to_moves(Bitboard mask, int delta, MoveArray* moves, bool en_passant) {
    Move move;
    uint8_t attacker_index;
    uint8_t attacker_type = Pawn;
    uint8_t attacker_color = this->white_turn ? White : Black;
    uint8_t opponent_index;
    uint8_t opponent_type;
    uint8_t opponent_color;
    bool double_move = abs(delta) == 16;


    while (mask) {
        opponent_index = bitboard_operations::bitScanForward(mask);
        bitboard_operations::set_0(mask, opponent_index);

        if (bitboard_operations::get_bit(this->side_bitboards[attacker_color], opponent_index)) {
            continue;
        }

        opponent_type = 255;
        for (uint8_t i = 0; i < 6; i++) {
            if (bitboard_operations::get_bit(this->piece_bitboards[1 - attacker_color][i], opponent_index)) {
                opponent_type = i;
                break;
            }
        }

        if (this->white_turn) {
            attacker_index = opponent_index - delta;
        } else {
            attacker_index = opponent_index + delta;
        }

        if (opponent_type == 255) {
            opponent_color = 255;
        } else {
            opponent_color = 1 - attacker_color;
        }

        if (en_passant) {
            move = Move(attacker_index, attacker_color, attacker_type, opponent_index, opponent_color, opponent_type,
                        false, false, false, false, false, true, 255);
        } else {
            move = Move(attacker_index, attacker_color, attacker_type, opponent_index, opponent_color, opponent_type,
                        false, false, false, false, double_move, false, 255);
        }

        moves->push_back(move);
    }
}


void chess::Board::mask_to_moves(Bitboard mask, uint8_t attacker_index, uint8_t attacker_color, uint8_t attacker_type,
                                 MoveArray* moves) {
    Move move;
    uint8_t opponent_index;
    uint8_t opponent_type;
    uint8_t opponent_color;

    while (mask) {
        opponent_index = bitboard_operations::bitScanForward(mask);
        bitboard_operations::set_0(mask, opponent_index);

        if (bitboard_operations::get_bit(this->side_bitboards[attacker_color], opponent_index)) {
            continue;
        }

        opponent_type = 255;
        for (uint8_t i = 0; i < 6; i++) {
            if (bitboard_operations::get_bit(this->piece_bitboards[1 - attacker_color][i], opponent_index)) {
                opponent_type = i;
                break;
            }
        }


        if (opponent_type == 255) {
            opponent_color = 255;
        } else {
            opponent_color = 1 - attacker_color;
        }

        move = Move(attacker_index, attacker_color, attacker_type, opponent_index, opponent_color, opponent_type, false,
                    false, false, false, false, false, 255);

        moves->push_back(move);
    }
}
