#include "headers/evaluate_position.hpp"

#include "headers/constants.hpp"
#include "headers/evaluating_constants.hpp"
#include "headers/pst.hpp"

int chess::engine::evaluate_position(Board& board, const uint8_t color) {
    const uint8_t board_color = board.white_turn ? White : Black;

    if (board.legal_moves.size() == 0) {
        if (board.is_check()) {  // checkmate
            if (board_color == color) {
                return constants::minimum;
            }
            return constants::maximum;
        }
        return 0;  // stalemate
    }

    int mg_score = 0;
    int eg_score = 0;
    int phase = 0;

    for (int piece = 0; piece < 6; piece++) {
        Bitboard bb = board.piece_bitboards[White][piece];

        // white
        while (bb) {
            const int sq = bitboard_operations::bitScanForward(bb);
            mg_score += pst::mg_value[piece] + (*pst::mg_table[piece])[sq];
            eg_score += pst::eg_value[piece] + (*pst::eg_table[piece])[sq];
            phase += pst::phase_weight[piece];
            bb &= bb - 1;
        }
         // black
        bb = board.piece_bitboards[Black][piece];
        while (bb) {
            const int sq = bitboard_operations::bitScanForward(bb);
            mg_score -= pst::mg_value[piece] + (*pst::mg_table[piece])[pst::mirror(sq)];
            eg_score -= pst::eg_value[piece] + (*pst::eg_table[piece])[pst::mirror(sq)];
            phase += pst::phase_weight[piece];
            bb &= bb - 1;
        }
    }

    if (phase > pst::total_phase) phase = pst::total_phase;

    const int score = (mg_score * phase + eg_score * (pst::total_phase - phase)) / pst::total_phase;

    return (color == White) ? score : -score;
}
