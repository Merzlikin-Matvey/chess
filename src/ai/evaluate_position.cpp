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

    // PST
    for (int piece = 0; piece < 6; piece++) {
        Bitboard bb = board.piece_bitboards[White][piece];

        while (bb) {
            const int sq = bitboard_operations::bitScanForward(bb);
            mg_score += pst::mg_value[piece] + (*pst::mg_table[piece])[pst::mirror(sq)];
            eg_score += pst::eg_value[piece] + (*pst::eg_table[piece])[pst::mirror(sq)];
            phase += pst::phase_weight[piece];
            bb &= bb - 1;
        }

        bb = board.piece_bitboards[Black][piece];
        while (bb) {
            const int sq = bitboard_operations::bitScanForward(bb);
            mg_score -= pst::mg_value[piece] + (*pst::mg_table[piece])[sq];
            eg_score -= pst::eg_value[piece] + (*pst::eg_table[piece])[sq];
            phase += pst::phase_weight[piece];
            bb &= bb - 1;
        }
    }

    // Passed pawns
    const Bitboard white_pawns = board.piece_bitboards[White][Pawn];
    const Bitboard black_pawns = board.piece_bitboards[Black][Pawn];

    Bitboard wp = white_pawns;
    while (wp) {
        const int sq = bitboard_operations::bitScanForward(wp);
        if ((pst::passed_masks.white[sq] & black_pawns) == 0) {
            const int rank = sq / 8;
            int mg_bonus = pst::passed_mg[rank];
            int eg_bonus = pst::passed_eg[rank];

            // Protected passed pawn
            const int file = sq % 8;
            bool protected_pawn = false;
            if (rank > 0) {
                if (file > 0 && bitboard_operations::get_bit(white_pawns, sq - 9))
                    protected_pawn = true;
                if (file < 7 && bitboard_operations::get_bit(white_pawns, sq - 7))
                    protected_pawn = true;
            }
            if (protected_pawn) {
                mg_bonus = mg_bonus * 13 / 10;
                eg_bonus = eg_bonus * 13 / 10;
            }

            // Blocked passed pawn
            if (rank < 7 and bitboard_operations::get_bit(board.side_bitboards[Black], sq + 8)) {
                mg_bonus = mg_bonus / 2;
                eg_bonus = eg_bonus / 2;
            }

            mg_score += mg_bonus;
            eg_score += eg_bonus;
        }
        wp &= wp - 1;
    }

    Bitboard bp = black_pawns;
    while (bp) {
        const int sq = bitboard_operations::bitScanForward(bp);
        if ((pst::passed_masks.black[sq] & white_pawns) == 0) {
            const int rank = 7 - sq / 8;
            int mg_bonus = pst::passed_mg[rank];
            int eg_bonus = pst::passed_eg[rank];

            // Protected passed pawn
            const int file = sq % 8;
            bool protected_pawn = false;
            if (sq / 8 < 7) {
                if (file > 0 && bitboard_operations::get_bit(black_pawns, sq + 7))
                    protected_pawn = true;
                if (file < 7 && bitboard_operations::get_bit(black_pawns, sq + 9))
                    protected_pawn = true;
            }
            if (protected_pawn) {
                mg_bonus = mg_bonus * 13 / 10;
                eg_bonus = eg_bonus * 13 / 10;
            }

            // Blocked passed pawn
            if (sq > 7 and bitboard_operations::get_bit(board.side_bitboards[White], sq - 8)) {
                mg_bonus = mg_bonus / 2;
                eg_bonus = eg_bonus / 2;
            }

            mg_score -= mg_bonus;
            eg_score -= eg_bonus;
        }
        bp &= bp - 1;
    }

    if (phase > pst::total_phase) {
        phase = pst::total_phase;
    }

    const int score = (mg_score * phase + eg_score * (pst::total_phase - phase)) / pst::total_phase;

    return color == White ? score : -score;
}
