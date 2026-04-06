#include "headers/bitboard_operations.hpp"
#include "headers/board.hpp"
#include "headers/constants.hpp"

void chess::Board::pawn_mask_to_moves(Bitboard mask, int delta, MoveArray* moves, bool en_passant)const {
    Move move;
    uint8_t attacker_index;
    constexpr uint8_t attacker_type = Pawn;
    const uint8_t attacker_color = this->white_turn ? White : Black;
    uint8_t opponent_index;
    uint8_t opponent_type;
    uint8_t opponent_color;
    const bool double_move = abs(delta) == 16;

    while (mask) {
        opponent_index = bitboard_operations::bitScanForward(mask);
        bitboard_operations::set_0(mask, opponent_index);

        if (bitboard_operations::get_bit(this->side_bitboards[attacker_color], opponent_index)) {
            continue;
        }

        {
            const uint8_t mb = this->mailbox[opponent_index];
            opponent_type = mb == 255 ? 255 : mb & 0x7;
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

        const bool is_promotion =
            (attacker_color == White && opponent_index >= 56) || (attacker_color == Black && opponent_index <= 7);

        if (is_promotion) {
            for (const uint8_t promo : {Queen, Rook, Bishop, Knight}) {
                move = Move(attacker_index, attacker_color, attacker_type, opponent_index, opponent_color,
                            opponent_type, false, false, false, false, false, false, promo);
                moves->push_back(move);
            }
        } else if (en_passant) {
            move = Move(attacker_index, attacker_color, attacker_type, opponent_index, opponent_color, opponent_type,
                        false, false, false, false, false, true, 255);
            moves->push_back(move);
        } else {
            move = Move(attacker_index, attacker_color, attacker_type, opponent_index, opponent_color, opponent_type,
                        false, false, false, false, double_move, false, 255);
            moves->push_back(move);
        }
    }
}

void chess::Board::mask_to_moves(Bitboard mask, const uint8_t attacker_index, const uint8_t attacker_color, const uint8_t attacker_type,
                                 MoveArray* moves) const {
    uint8_t opponent_type;
    uint8_t opponent_color;

    while (mask) {
        const uint8_t opponent_index = bitboard_operations::bitScanForward(mask);
        bitboard_operations::set_0(mask, opponent_index);

        if (bitboard_operations::get_bit(this->side_bitboards[attacker_color], opponent_index)) {
            continue;
        }

        {
            const uint8_t mb = this->mailbox[opponent_index];
            opponent_type = mb == 255 ? 255 : mb & 0x7;
        }

        if (opponent_type == 255) {
            opponent_color = 255;
        } else {
            opponent_color = 1 - attacker_color;
        }

        const auto move = Move(attacker_index, attacker_color, attacker_type, opponent_index, opponent_color, opponent_type, false,
                    false, false, false, false, false, 255);

        moves->push_back(move);
    }
}