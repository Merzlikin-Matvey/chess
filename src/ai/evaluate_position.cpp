#include "headers/evaluate_position.hpp"
#include "headers/evaluating_constants.hpp"


double chess::engine::evaluate_position(Board& board, uint8_t color) {
    uint8_t board_color = board.white_turn ? chess::White : chess::Black;
    uint8_t king_index = bitboard_operations::bitScanForward(board.piece_bitboards[color][chess::King]);
    double score = 0;

    if (board.is_checkmate()) {
        if (board_color == color) {
            return constants::minimum;
        } else {
            return constants::maximum;
        }
    }

    score += constants::material_weight *
        (bitboard_operations::count_1(board.piece_bitboards[color][chess::Pawn]) * constants::pawn +
         bitboard_operations::count_1(board.piece_bitboards[color][chess::Knight]) * constants::knight +
         bitboard_operations::count_1(board.piece_bitboards[color][chess::Bishop]) * constants::bishop +
         bitboard_operations::count_1(board.piece_bitboards[color][chess::Rook]) * constants::rook +
         bitboard_operations::count_1(board.piece_bitboards[color][chess::Queen]) * constants::queen);

    score -= constants::material_weight *
        (bitboard_operations::count_1(board.piece_bitboards[!color][chess::Pawn]) * constants::pawn +
         bitboard_operations::count_1(board.piece_bitboards[!color][chess::Knight]) * constants::knight +
         bitboard_operations::count_1(board.piece_bitboards[!color][chess::Bishop]) * constants::bishop +
         bitboard_operations::count_1(board.piece_bitboards[!color][chess::Rook]) * constants::rook +
         bitboard_operations::count_1(board.piece_bitboards[!color][chess::Queen]) * constants::queen);

    uint8_t num_pawns_moves = 0;
    uint8_t num_knights_moves = 0;
    uint8_t num_bishops_moves = 0;
    uint8_t num_rooks_moves = 0;
    uint8_t num_queens_moves = 0;
    uint8_t num_kings_moves = 0;

    for (int i = 0; i < board.legal_moves.size(); i++) {
        Move move = board.legal_moves.moves[i];
        if (move.first_type == chess::Pawn) {
            num_pawns_moves++;
        } else if (move.first_type == chess::Knight) {
            num_knights_moves++;
        } else if (move.first_type == chess::Bishop) {
            num_bishops_moves++;
        } else if (move.first_type == chess::Rook) {
            num_rooks_moves++;
        } else if (move.first_type == chess::Queen) {
            num_queens_moves++;
        } else if (move.first_type == chess::King) {
            num_kings_moves++;
        }
    }

    if (color == board_color) {
        score += constants::mobility_weight *
            (num_pawns_moves * constants::pawn_mobility + num_knights_moves * constants::knight_mobility +
             num_bishops_moves * constants::bishop_mobility + num_rooks_moves * constants::rook_mobility +
             num_queens_moves * constants::queen_mobility + num_kings_moves * constants::king_mobility);
    } else {
        score -= constants::mobility_weight *
            (num_pawns_moves * constants::pawn_mobility + num_knights_moves * constants::knight_mobility +
             num_bishops_moves * constants::bishop_mobility + num_rooks_moves * constants::rook_mobility +
             num_queens_moves * constants::queen_mobility + num_kings_moves * constants::king_mobility);
    }

    if (board.is_check()) {
        if (color == board_color) {
            score += constants::check;
        } else {
            score -= constants::check;
        }

        if (board.is_double_check()) {
            if (color == board_color) {
                score += constants::double_check;
            } else {
                score -= constants::double_check;
            }
        }
    }


    double pawn_structure_score = 0;

    for (uint8_t i = 0; i < 8; i++) {
        switch (
            bitboard_operations::count_1(bitboard_operations::columns[i] & board.piece_bitboards[color][chess::Pawn])) {
        case 0:
            pawn_structure_score += constants::no_pawns_in_column;
            break;
        case 1:
            pawn_structure_score += constants::pawn_1_in_column;
            break;
        case 2:
            pawn_structure_score += constants::pawn_2_in_column;
            break;
        case 3:
            pawn_structure_score += constants::pawn_3_in_column;
            break;
        case 4:
            pawn_structure_score += constants::pawn_4_in_column;
            break;
        default:
            pawn_structure_score += constants::many_pawns_in_column;
            break;
        }
    }

    if (color == chess::White and king_index < 56) {
        pawn_structure_score += constants::pawn_after_king *
            (bitboard_operations::get_bit(board.piece_bitboards[chess::White][chess::Pawn], king_index + 8));
    } else if (color == chess::Black and king_index > 7) {
        pawn_structure_score += constants::pawn_after_king *
            (bitboard_operations::get_bit(board.piece_bitboards[chess::Black][chess::Pawn], king_index - 8));
    }

    if (color == chess::White) {
        if (board.piece_bitboards[chess::Black][chess::Pawn] & bitboard_operations::rows[1]) {
            pawn_structure_score += constants::pawns_in_end;
        }
    } else {
        if (board.piece_bitboards[chess::White][chess::Pawn] & bitboard_operations::rows[6]) {
            pawn_structure_score += constants::pawns_in_end;
        }
    }

    Bitboard right_defended_pawns =
        ((board.piece_bitboards[color][chess::Pawn] & ~bitboard_operations::columns[7]) << 7) &
        board.piece_bitboards[color][chess::Pawn];
    Bitboard left_defended_pawns =
        ((board.piece_bitboards[color][chess::Pawn] & ~bitboard_operations::columns[0]) << 9) &
        board.piece_bitboards[color][chess::Pawn];

    pawn_structure_score += constants::defended_pawn * bitboard_operations::count_1(right_defended_pawns);
    pawn_structure_score += constants::defended_pawn * bitboard_operations::count_1(left_defended_pawns);

    pawn_structure_score *= constants::pawn_structure;
    score += pawn_structure_score;


    double center_control_score = 0;

    center_control_score +=
        constants::pawn * bitboard_operations::count_1(board.piece_bitboards[color][chess::Pawn] & constants::center);
    center_control_score += constants::knight *
        bitboard_operations::count_1(board.piece_bitboards[color][chess::Knight] & constants::center);
    center_control_score += constants::bishop *
        bitboard_operations::count_1(board.piece_bitboards[color][chess::Bishop] & constants::center);
    center_control_score +=
        constants::rook * bitboard_operations::count_1(board.piece_bitboards[color][chess::Rook] & constants::center);
    center_control_score +=
        constants::queen * bitboard_operations::count_1(board.piece_bitboards[color][chess::Queen] & constants::center);

    center_control_score -=
        constants::pawn * bitboard_operations::count_1(board.piece_bitboards[!color][chess::Pawn] & constants::center);
    center_control_score -= constants::knight *
        bitboard_operations::count_1(board.piece_bitboards[!color][chess::Knight] & constants::center);
    center_control_score -= constants::bishop *
        bitboard_operations::count_1(board.piece_bitboards[!color][chess::Bishop] & constants::center);
    center_control_score -=
        constants::rook * bitboard_operations::count_1(board.piece_bitboards[!color][chess::Rook] & constants::center);
    center_control_score -= constants::queen *
        bitboard_operations::count_1(board.piece_bitboards[!color][chess::Queen] & constants::center);

    center_control_score *= constants::center_control;
    score += center_control_score;

    if (bitboard_operations::count_1(board.piece_bitboards[color][chess::Bishop]) >= 2) {
        score += constants::two_bishops;
    }


    return score;
}
