#include <bit>

#include "headers/bitboard_operations.hpp"
#include "headers/board.hpp"
#include "headers/check_and_checkmate.hpp"
#include "headers/constants.hpp"
#include "headers/masks/masks.hpp"
#include "headers/move.hpp"

void chess::Board::castling(chess::MoveArray* moves) {
    uint8_t color = white_turn ? White : Black;

    if (color == White) {
        // Long
        if (w_l_castling and bitboard_operations::get_bit(piece_bitboards[White][Rook], 0) and
            !bitboard_operations::get_bit(all, 1) and !bitboard_operations::get_bit(all, 2) and
            !bitboard_operations::get_bit(all, 3) and bitboard_operations::get_bit(piece_bitboards[White][King], 4)) {
            if (!is_position_attacked(2) and !is_position_attacked(3)) {
                moves->push_back(Move(4, White, King, 2, 255, 255, true, false, false, false, false, false, 255));
            }
        }

        // Short
        if (w_s_castling and bitboard_operations::get_bit(piece_bitboards[White][Rook], 7) and
            !bitboard_operations::get_bit(all, 5) and !bitboard_operations::get_bit(all, 6) and
            bitboard_operations::get_bit(piece_bitboards[White][King], 4)) {
            if (!is_position_attacked(5) and !is_position_attacked(6)) {
                moves->push_back(Move(4, White, King, 6, 255, 255, false, true, false, false, false, false, 255));
            }
        }
    } else {
        // Long
        if (b_l_castling and bitboard_operations::get_bit(piece_bitboards[Black][Rook], 56) and
            !bitboard_operations::get_bit(all, 57) and !bitboard_operations::get_bit(all, 58) and
            !bitboard_operations::get_bit(all, 59) and bitboard_operations::get_bit(piece_bitboards[Black][King], 60)) {
            if (!is_position_attacked(58) and !is_position_attacked(59)) {
                moves->push_back(Move(60, Black, King, 58, 255, 255, false, false, true, false, false, false, 255));
            }
        }

        // Short
        if (b_s_castling and bitboard_operations::get_bit(piece_bitboards[Black][Rook], 63) and
            !bitboard_operations::get_bit(all, 61) and !bitboard_operations::get_bit(all, 62) and
            bitboard_operations::get_bit(piece_bitboards[Black][King], 60)) {
            if (!is_position_attacked(61) and !is_position_attacked(62)) {
                moves->push_back(Move(60, Black, King, 62, 255, 255, false, false, false, true, false, false, 255));
            }
        }
    }
}

Bitboard chess::Board::get_king_legal_moves_mask() {
    const uint8_t color = white_turn ? White : Black;
    const uint8_t king_position = bitboard_operations::bitScanForward(piece_bitboards[color][King]);
    Bitboard primary_mask = masks::king_masks[king_position];
    Bitboard mask = 0;

    bitboard_operations::set_0(piece_bitboards[color][King], king_position);
    bitboard_operations::set_0(side_bitboards[color], king_position);
    bitboard_operations::set_0(all, king_position);
    while (primary_mask) {
        const uint8_t bit = bitboard_operations::bitScanForward(primary_mask);
        bitboard_operations::set_0(primary_mask, bit);

        bitboard_operations::set_1(piece_bitboards[color][King], bit);
        if (!is_check()) {
            bitboard_operations::set_1(mask, bit);
        }
        bitboard_operations::set_0(piece_bitboards[color][King], bit);
    }

    bitboard_operations::set_1(piece_bitboards[color][King], king_position);
    bitboard_operations::set_1(side_bitboards[color], king_position);
    bitboard_operations::set_1(all, king_position);
    return mask;
}

chess::MoveArray& chess::Board::get_legal_moves() {
    legal_moves.clear();
    uint8_t color = white_turn ? White : Black;
    uint8_t king_position = bitboard_operations::bitScanForward(piece_bitboards[color][King]);

    if (is_double_check()) {
        check_status = 2;
        mask_to_moves(get_king_legal_moves_mask(), king_position, color, King, &legal_moves);
        return legal_moves;
    }
    check_status = is_position_attacked(king_position) ? 1 : 0;

    Bitboard vertical_pin_mask = masks::get_vertical_pin_mask(*this, king_position, color);
    Bitboard horizontal_pin_mask = masks::get_horizontal_pin_mask(*this, king_position, color);
    Bitboard up_right_pin_mask = masks::get_up_right_pin_mask(*this, king_position, color);
    Bitboard up_left_pin_mask = masks::get_down_right_pin_mask(*this, king_position, color);
    Bitboard pin_mask = vertical_pin_mask | horizontal_pin_mask | up_right_pin_mask | up_left_pin_mask;
    Bitboard inverse_pin_mask = ~pin_mask;

    uint8_t square;

    if (check_status == 1) {
        Bitboard check_mask = get_check_mask();

        // Pinned pawns
        Bitboard vertical_pinned_pawns = piece_bitboards[color][Pawn] & vertical_pin_mask;
        Bitboard up_right_pinned_pawns = piece_bitboards[color][Pawn] & up_right_pin_mask;
        Bitboard up_left_pinned_pawns = piece_bitboards[color][Pawn] & up_left_pin_mask;
        pawn_mask_to_moves(masks::get_pawn_mask(vertical_pinned_pawns, *this) & check_mask & vertical_pin_mask, 8,
                           &legal_moves, false);
        pawn_mask_to_moves(masks::get_pawn_long_mask(vertical_pinned_pawns, *this) & check_mask & vertical_pin_mask, 16,
                           &legal_moves, false);
        if (color == White) {
            pawn_mask_to_moves(
                masks::get_pawn_right_mask(up_right_pinned_pawns, *this) & check_mask & up_right_pin_mask, 9,
                &legal_moves, false);
            pawn_mask_to_moves(
                masks::get_pawn_left_mask(up_left_pinned_pawns, *this) & check_mask & up_left_pinned_pawns, 7,
                &legal_moves, false);
        } else {
            pawn_mask_to_moves(
                masks::get_pawn_right_mask(up_right_pinned_pawns, *this) & check_mask & up_right_pin_mask, 7,
                &legal_moves, false);
            pawn_mask_to_moves(
                masks::get_pawn_left_mask(up_left_pinned_pawns, *this) & check_mask & up_left_pinned_pawns, 9,
                &legal_moves, false);
        }

        // Pinned rooks
        Bitboard pinned_rooks = piece_bitboards[color][Rook] & (horizontal_pin_mask | vertical_pin_mask);
        while (pinned_rooks) {
            square = bitboard_operations::bitScanForward(pinned_rooks);
            bitboard_operations::set_0(pinned_rooks, square);
            mask_to_moves(masks::get_rook_mask(*this, square) & (horizontal_pin_mask | vertical_pin_mask) & check_mask,
                          square, color, Rook, &legal_moves);
        }

        // Pinned bishops
        Bitboard pinned_bishops = piece_bitboards[color][Bishop] & (up_right_pin_mask | up_left_pin_mask);
        while (pinned_bishops) {
            square = bitboard_operations::bitScanForward(pinned_bishops);
            bitboard_operations::set_0(pinned_bishops, square);
            mask_to_moves(masks::get_bishop_mask(*this, square) & (up_right_pin_mask | up_left_pin_mask) & check_mask,
                          square, color, Bishop, &legal_moves);
        }

        // Pinned queens
        Bitboard vertical_and_horizontal_pinned_queens =
            piece_bitboards[color][Queen] & (horizontal_pin_mask | vertical_pin_mask);
        Bitboard diagonal_pinned_queens = piece_bitboards[color][Queen] & (up_right_pin_mask | up_left_pin_mask);

        while (vertical_and_horizontal_pinned_queens) {
            square = bitboard_operations::bitScanForward(vertical_and_horizontal_pinned_queens);
            bitboard_operations::set_0(vertical_and_horizontal_pinned_queens, square);
            mask_to_moves(masks::get_rook_mask(*this, square) & (horizontal_pin_mask | vertical_pin_mask) & check_mask,
                          square, color, Queen, &legal_moves);
        }

        while (diagonal_pinned_queens) {
            square = bitboard_operations::bitScanForward(diagonal_pinned_queens);
            bitboard_operations::set_0(diagonal_pinned_queens, square);
            mask_to_moves(masks::get_bishop_mask(*this, square) & (up_right_pin_mask | up_left_pin_mask) & check_mask,
                          square, color, Queen, &legal_moves);
        }

        // Pawns
        Bitboard pawns = piece_bitboards[color][Pawn] & inverse_pin_mask;
        pawn_mask_to_moves(masks::get_pawn_mask(pawns, *this) & check_mask, 8, &legal_moves, false);
        pawn_mask_to_moves(masks::get_pawn_long_mask(pawns, *this) & check_mask, 16, &legal_moves, false);
        if (color == White) {
            pawn_mask_to_moves(masks::get_pawn_right_mask(pawns, *this) & check_mask, 9, &legal_moves, false);
            pawn_mask_to_moves(masks::get_pawn_left_mask(pawns, *this) & check_mask, 7, &legal_moves, false);
        } else {
            pawn_mask_to_moves(masks::get_pawn_right_mask(pawns, *this) & check_mask, 7, &legal_moves, false);
            pawn_mask_to_moves(masks::get_pawn_left_mask(pawns, *this) & check_mask, 9, &legal_moves, false);
        }

        // En passant during check (only if capturing the checking pawn)
        if (en_passant_square >= 0) {
            uint8_t captured_sq = (color == White) ? en_passant_square - 8 : en_passant_square + 8;
            if (bitboard_operations::get_bit(check_mask, captured_sq)) {
                Bitboard ep_masks[] = {masks::get_right_en_passant_mask(pawns, *this),
                                       masks::get_left_en_passant_mask(pawns, *this)};
                int deltas_w[] = {9, 7};
                int deltas_b[] = {7, 9};
                int* deltas = (color == White) ? deltas_w : deltas_b;

                for (int d = 0; d < 2; d++) {
                    Bitboard ep = ep_masks[d];
                    while (ep) {
                        uint8_t target = bitboard_operations::bitScanForward(ep);
                        bitboard_operations::set_0(ep, target);
                        uint8_t src = white_turn ? target - deltas[d] : target + deltas[d];

                        bitboard_operations::set_0(piece_bitboards[color][Pawn], src);
                        bitboard_operations::set_0(side_bitboards[color], src);
                        bitboard_operations::set_0(all, src);
                        bitboard_operations::set_0(piece_bitboards[1 - color][Pawn], captured_sq);
                        bitboard_operations::set_0(side_bitboards[1 - color], captured_sq);
                        bitboard_operations::set_0(all, captured_sq);
                        bitboard_operations::set_1(piece_bitboards[color][Pawn], target);
                        bitboard_operations::set_1(side_bitboards[color], target);
                        bitboard_operations::set_1(all, target);

                        bool valid = !is_check();

                        bitboard_operations::set_1(piece_bitboards[color][Pawn], src);
                        bitboard_operations::set_1(side_bitboards[color], src);
                        bitboard_operations::set_1(all, src);
                        bitboard_operations::set_1(piece_bitboards[1 - color][Pawn], captured_sq);
                        bitboard_operations::set_1(side_bitboards[1 - color], captured_sq);
                        bitboard_operations::set_1(all, captured_sq);
                        bitboard_operations::set_0(piece_bitboards[color][Pawn], target);
                        bitboard_operations::set_0(side_bitboards[color], target);
                        bitboard_operations::set_0(all, target);

                        if (valid) {
                            Bitboard single = 1ull << target;
                            pawn_mask_to_moves(single, deltas[d], &legal_moves, true);
                        }
                    }
                }
            }
        }

        // Rooks
        Bitboard rooks = piece_bitboards[color][Rook] & inverse_pin_mask;
        while (rooks) {
            square = bitboard_operations::bitScanForward(rooks);
            bitboard_operations::set_0(rooks, square);
            mask_to_moves(masks::get_rook_mask(*this, square) & check_mask, square, color, Rook, &legal_moves);
        }

        // Bishops
        Bitboard bishops = piece_bitboards[color][Bishop] & inverse_pin_mask;
        while (bishops) {
            square = bitboard_operations::bitScanForward(bishops);
            bitboard_operations::set_0(bishops, square);
            mask_to_moves(masks::get_bishop_mask(*this, square) & check_mask, square, color, Bishop, &legal_moves);
        }

        // Queens
        Bitboard queens = piece_bitboards[color][Queen] & inverse_pin_mask;
        while (queens) {
            square = bitboard_operations::bitScanForward(queens);
            bitboard_operations::set_0(queens, square);
            mask_to_moves(masks::get_bishop_mask(*this, square) & check_mask, square, color, Queen, &legal_moves);
            mask_to_moves(masks::get_rook_mask(*this, square) & check_mask, square, color, Queen, &legal_moves);
        }

        // Knights
        Bitboard knights = piece_bitboards[color][Knight] & inverse_pin_mask;
        while (knights) {
            square = bitboard_operations::bitScanForward(knights);
            bitboard_operations::set_0(knights, square);
            mask_to_moves(masks::get_knight_mask(square) & check_mask, square, color, Knight, &legal_moves);
        }

        // King
        mask_to_moves(get_king_legal_moves_mask(), king_position, color, King, &legal_moves);
    } else {
        // Pinned pawns
        Bitboard vertical_pinned_pawns = piece_bitboards[color][Pawn] & vertical_pin_mask;
        Bitboard up_right_pinned_pawns = piece_bitboards[color][Pawn] & up_right_pin_mask;
        Bitboard up_left_pinned_pawns = piece_bitboards[color][Pawn] & up_left_pin_mask;
        pawn_mask_to_moves(masks::get_pawn_mask(vertical_pinned_pawns, *this), 8, &legal_moves, false);
        pawn_mask_to_moves(masks::get_pawn_long_mask(vertical_pinned_pawns, *this), 16, &legal_moves, false);
        if (color == White) {
            pawn_mask_to_moves(masks::get_pawn_right_mask(up_right_pinned_pawns, *this), 9, &legal_moves, false);
            pawn_mask_to_moves(masks::get_pawn_left_mask(up_left_pinned_pawns, *this), 7, &legal_moves, false);
        } else {
            pawn_mask_to_moves(masks::get_pawn_right_mask(up_left_pinned_pawns, *this), 7, &legal_moves, false);
            pawn_mask_to_moves(masks::get_pawn_left_mask(up_right_pinned_pawns, *this), 9, &legal_moves, false);
        }

        // Pinned rooks
        Bitboard pinned_rooks = piece_bitboards[color][Rook] & (horizontal_pin_mask | vertical_pin_mask);
        while (pinned_rooks) {
            square = bitboard_operations::bitScanForward(pinned_rooks);
            bitboard_operations::set_0(pinned_rooks, square);
            mask_to_moves(masks::get_rook_mask(*this, square) & (horizontal_pin_mask | vertical_pin_mask), square,
                          color, Rook, &legal_moves);
        }

        // Pinned bishops
        Bitboard pinned_bishops = piece_bitboards[color][Bishop] & (up_right_pin_mask | up_left_pin_mask);
        while (pinned_bishops) {
            square = bitboard_operations::bitScanForward(pinned_bishops);
            bitboard_operations::set_0(pinned_bishops, square);
            mask_to_moves(masks::get_bishop_mask(*this, square) & (up_right_pin_mask | up_left_pin_mask), square, color,
                          Bishop, &legal_moves);
        }

        // Pinned queens
        Bitboard vertical_and_horizontal_pinned_queens =
            piece_bitboards[color][Queen] & (horizontal_pin_mask | vertical_pin_mask);
        Bitboard diagonal_pinned_queens = piece_bitboards[color][Queen] & (up_right_pin_mask | up_left_pin_mask);

        while (vertical_and_horizontal_pinned_queens) {
            square = bitboard_operations::bitScanForward(vertical_and_horizontal_pinned_queens);
            bitboard_operations::set_0(vertical_and_horizontal_pinned_queens, square);
            mask_to_moves(masks::get_rook_mask(*this, square) & (horizontal_pin_mask | vertical_pin_mask), square,
                          color, Queen, &legal_moves);
        }

        while (diagonal_pinned_queens) {
            square = bitboard_operations::bitScanForward(diagonal_pinned_queens);
            bitboard_operations::set_0(diagonal_pinned_queens, square);
            mask_to_moves(masks::get_bishop_mask(*this, square) & (up_right_pin_mask | up_left_pin_mask), square, color,
                          Queen, &legal_moves);
        }

        // Pawns
        Bitboard pawns = piece_bitboards[color][Pawn] & inverse_pin_mask;
        pawn_mask_to_moves(masks::get_pawn_mask(pawns, *this), 8, &legal_moves, false);
        pawn_mask_to_moves(masks::get_pawn_long_mask(pawns, *this), 16, &legal_moves, false);
        if (color == White) {
            pawn_mask_to_moves(masks::get_pawn_right_mask(pawns, *this), 9, &legal_moves, false);
            pawn_mask_to_moves(masks::get_pawn_left_mask(pawns, *this), 7, &legal_moves, false);
        } else {
            pawn_mask_to_moves(masks::get_pawn_right_mask(pawns, *this), 7, &legal_moves, false);
            pawn_mask_to_moves(masks::get_pawn_left_mask(pawns, *this), 9, &legal_moves, false);
        }

        // En passant
        if (en_passant_square >= 0) {
            uint8_t captured_sq = (color == White) ? en_passant_square - 8 : en_passant_square + 8;
            Bitboard ep_masks[] = {masks::get_right_en_passant_mask(pawns, *this),
                                   masks::get_left_en_passant_mask(pawns, *this)};
            int deltas_w[] = {9, 7};
            int deltas_b[] = {7, 9};
            int* deltas = (color == White) ? deltas_w : deltas_b;

            for (int d = 0; d < 2; d++) {
                Bitboard ep = ep_masks[d];
                while (ep) {
                    uint8_t target = bitboard_operations::bitScanForward(ep);
                    bitboard_operations::set_0(ep, target);
                    uint8_t src = white_turn ? target - deltas[d] : target + deltas[d];

                    // Simulate capture
                    bitboard_operations::set_0(piece_bitboards[color][Pawn], src);
                    bitboard_operations::set_0(side_bitboards[color], src);
                    bitboard_operations::set_0(all, src);
                    bitboard_operations::set_0(piece_bitboards[1 - color][Pawn], captured_sq);
                    bitboard_operations::set_0(side_bitboards[1 - color], captured_sq);
                    bitboard_operations::set_0(all, captured_sq);
                    bitboard_operations::set_1(piece_bitboards[color][Pawn], target);
                    bitboard_operations::set_1(side_bitboards[color], target);
                    bitboard_operations::set_1(all, target);

                    bool valid = !is_check();

                    // Undo
                    bitboard_operations::set_1(piece_bitboards[color][Pawn], src);
                    bitboard_operations::set_1(side_bitboards[color], src);
                    bitboard_operations::set_1(all, src);
                    bitboard_operations::set_1(piece_bitboards[1 - color][Pawn], captured_sq);
                    bitboard_operations::set_1(side_bitboards[1 - color], captured_sq);
                    bitboard_operations::set_1(all, captured_sq);
                    bitboard_operations::set_0(piece_bitboards[color][Pawn], target);
                    bitboard_operations::set_0(side_bitboards[color], target);
                    bitboard_operations::set_0(all, target);

                    if (valid) {
                        Bitboard single = 1ull << target;
                        pawn_mask_to_moves(single, deltas[d], &legal_moves, true);
                    }
                }
            }
        }

        // Rooks
        Bitboard rooks = piece_bitboards[color][Rook] & inverse_pin_mask;
        while (rooks) {
            square = bitboard_operations::bitScanForward(rooks);
            bitboard_operations::set_0(rooks, square);
            mask_to_moves(masks::get_rook_mask(*this, square), square, color, Rook, &legal_moves);
        }

        // Bishops
        Bitboard bishops = piece_bitboards[color][Bishop] & inverse_pin_mask;
        while (bishops) {
            square = bitboard_operations::bitScanForward(bishops);
            bitboard_operations::set_0(bishops, square);
            mask_to_moves(masks::get_bishop_mask(*this, square), square, color, Bishop, &legal_moves);
        }

        // Queens
        Bitboard queens = piece_bitboards[color][Queen] & inverse_pin_mask;
        while (queens) {
            square = bitboard_operations::bitScanForward(queens);
            bitboard_operations::set_0(queens, square);
            mask_to_moves(masks::get_bishop_mask(*this, square), square, color, Queen, &legal_moves);
            mask_to_moves(masks::get_rook_mask(*this, square), square, color, Queen, &legal_moves);
        }

        // Knights
        Bitboard knights = piece_bitboards[color][Knight] & inverse_pin_mask;
        while (knights) {
            square = bitboard_operations::bitScanForward(knights);
            bitboard_operations::set_0(knights, square);
            mask_to_moves(masks::get_knight_mask(square), square, color, Knight, &legal_moves);
        }

        // King
        mask_to_moves(get_king_legal_moves_mask(), king_position, color, King, &legal_moves);

        // Castling
        castling(&legal_moves);
    }

    return legal_moves;
}

static int count_mask(const Bitboard mask, const Bitboard friendly) {
    return std::popcount(mask & ~friendly);
}

static int count_pawn_mask(Bitboard mask, const Bitboard friendly, const uint8_t color) {
    mask &= ~friendly;
    const Bitboard promo_rank = (color == chess::White) ? bitboard_operations::rows[7] : bitboard_operations::rows[0];
    const Bitboard promos = mask & promo_rank;
    const Bitboard non_promos = mask & ~promo_rank;
    return std::popcount(non_promos) + std::popcount(promos) * 4;
}

int chess::Board::count_legal_moves() {
    int count = 0;
    uint8_t color = white_turn ? White : Black;
    Bitboard friendly = side_bitboards[color];
    uint8_t king_position = bitboard_operations::bitScanForward(piece_bitboards[color][King]);

    if (is_double_check()) {
        return count_mask(get_king_legal_moves_mask(), friendly);
    }

    Bitboard vertical_pin_mask = masks::get_vertical_pin_mask(*this, king_position, color);
    Bitboard horizontal_pin_mask = masks::get_horizontal_pin_mask(*this, king_position, color);
    Bitboard up_right_pin_mask = masks::get_up_right_pin_mask(*this, king_position, color);
    Bitboard up_left_pin_mask = masks::get_down_right_pin_mask(*this, king_position, color);
    Bitboard pin_mask = vertical_pin_mask | horizontal_pin_mask | up_right_pin_mask | up_left_pin_mask;
    Bitboard inverse_pin_mask = ~pin_mask;

    uint8_t square;

    if (is_check()) {
        Bitboard check_mask = get_check_mask();

        // Pinned pawns
        Bitboard vertical_pinned_pawns = piece_bitboards[color][Pawn] & vertical_pin_mask;
        Bitboard up_right_pinned_pawns = piece_bitboards[color][Pawn] & up_right_pin_mask;
        Bitboard up_left_pinned_pawns = piece_bitboards[color][Pawn] & up_left_pin_mask;
        count += count_pawn_mask(masks::get_pawn_mask(vertical_pinned_pawns, *this) & check_mask & vertical_pin_mask,
                                 friendly, color);
        count += count_pawn_mask(
            masks::get_pawn_long_mask(vertical_pinned_pawns, *this) & check_mask & vertical_pin_mask, friendly, color);
        if (color == White) {
            count += count_pawn_mask(
                masks::get_pawn_right_mask(up_right_pinned_pawns, *this) & check_mask & up_right_pin_mask, friendly,
                color);
            count += count_pawn_mask(
                masks::get_pawn_left_mask(up_left_pinned_pawns, *this) & check_mask & up_left_pinned_pawns, friendly,
                color);
        } else {
            count += count_pawn_mask(
                masks::get_pawn_right_mask(up_right_pinned_pawns, *this) & check_mask & up_right_pin_mask, friendly,
                color);
            count += count_pawn_mask(
                masks::get_pawn_left_mask(up_left_pinned_pawns, *this) & check_mask & up_left_pinned_pawns, friendly,
                color);
        }

        // Pinned rooks
        Bitboard pinned_rooks = piece_bitboards[color][Rook] & (horizontal_pin_mask | vertical_pin_mask);
        while (pinned_rooks) {
            square = bitboard_operations::bitScanForward(pinned_rooks);
            bitboard_operations::set_0(pinned_rooks, square);
            count += count_mask(
                masks::get_rook_mask(*this, square) & (horizontal_pin_mask | vertical_pin_mask) & check_mask, friendly);
        }

        // Pinned bishops
        Bitboard pinned_bishops = piece_bitboards[color][Bishop] & (up_right_pin_mask | up_left_pin_mask);
        while (pinned_bishops) {
            square = bitboard_operations::bitScanForward(pinned_bishops);
            bitboard_operations::set_0(pinned_bishops, square);
            count += count_mask(
                masks::get_bishop_mask(*this, square) & (up_right_pin_mask | up_left_pin_mask) & check_mask, friendly);
        }

        // Pinned queens
        Bitboard vertical_and_horizontal_pinned_queens =
            piece_bitboards[color][Queen] & (horizontal_pin_mask | vertical_pin_mask);
        Bitboard diagonal_pinned_queens = piece_bitboards[color][Queen] & (up_right_pin_mask | up_left_pin_mask);

        while (vertical_and_horizontal_pinned_queens) {
            square = bitboard_operations::bitScanForward(vertical_and_horizontal_pinned_queens);
            bitboard_operations::set_0(vertical_and_horizontal_pinned_queens, square);
            count += count_mask(
                masks::get_rook_mask(*this, square) & (horizontal_pin_mask | vertical_pin_mask) & check_mask, friendly);
        }

        while (diagonal_pinned_queens) {
            square = bitboard_operations::bitScanForward(diagonal_pinned_queens);
            bitboard_operations::set_0(diagonal_pinned_queens, square);
            count += count_mask(
                masks::get_bishop_mask(*this, square) & (up_right_pin_mask | up_left_pin_mask) & check_mask, friendly);
        }

        // Pawns
        Bitboard pawns = piece_bitboards[color][Pawn] & inverse_pin_mask;
        count += count_pawn_mask(masks::get_pawn_mask(pawns, *this) & check_mask, friendly, color);
        count += count_pawn_mask(masks::get_pawn_long_mask(pawns, *this) & check_mask, friendly, color);
        if (color == White) {
            count += count_pawn_mask(masks::get_pawn_right_mask(pawns, *this) & check_mask, friendly, color);
            count += count_pawn_mask(masks::get_pawn_left_mask(pawns, *this) & check_mask, friendly, color);
        } else {
            count += count_pawn_mask(masks::get_pawn_right_mask(pawns, *this) & check_mask, friendly, color);
            count += count_pawn_mask(masks::get_pawn_left_mask(pawns, *this) & check_mask, friendly, color);
        }

        // En passant during check
        if (en_passant_square >= 0) {
            uint8_t captured_sq = (color == White) ? en_passant_square - 8 : en_passant_square + 8;
            if (bitboard_operations::get_bit(check_mask, captured_sq)) {
                Bitboard ep_masks[] = {masks::get_right_en_passant_mask(pawns, *this),
                                       masks::get_left_en_passant_mask(pawns, *this)};
                int deltas_w[] = {9, 7};
                int deltas_b[] = {7, 9};
                int* deltas = (color == White) ? deltas_w : deltas_b;

                for (int d = 0; d < 2; d++) {
                    Bitboard ep = ep_masks[d];
                    while (ep) {
                        uint8_t target = bitboard_operations::bitScanForward(ep);
                        bitboard_operations::set_0(ep, target);
                        uint8_t src = white_turn ? target - deltas[d] : target + deltas[d];

                        bitboard_operations::set_0(piece_bitboards[color][Pawn], src);
                        bitboard_operations::set_0(side_bitboards[color], src);
                        bitboard_operations::set_0(all, src);
                        bitboard_operations::set_0(piece_bitboards[1 - color][Pawn], captured_sq);
                        bitboard_operations::set_0(side_bitboards[1 - color], captured_sq);
                        bitboard_operations::set_0(all, captured_sq);
                        bitboard_operations::set_1(piece_bitboards[color][Pawn], target);
                        bitboard_operations::set_1(side_bitboards[color], target);
                        bitboard_operations::set_1(all, target);

                        bool valid = !is_check();

                        bitboard_operations::set_1(piece_bitboards[color][Pawn], src);
                        bitboard_operations::set_1(side_bitboards[color], src);
                        bitboard_operations::set_1(all, src);
                        bitboard_operations::set_1(piece_bitboards[1 - color][Pawn], captured_sq);
                        bitboard_operations::set_1(side_bitboards[1 - color], captured_sq);
                        bitboard_operations::set_1(all, captured_sq);
                        bitboard_operations::set_0(piece_bitboards[color][Pawn], target);
                        bitboard_operations::set_0(side_bitboards[color], target);
                        bitboard_operations::set_0(all, target);

                        if (valid)
                            count++;
                    }
                }
            }
        }

        // Rooks
        Bitboard rooks = piece_bitboards[color][Rook] & inverse_pin_mask;
        while (rooks) {
            square = bitboard_operations::bitScanForward(rooks);
            bitboard_operations::set_0(rooks, square);
            count += count_mask(masks::get_rook_mask(*this, square) & check_mask, friendly);
        }

        // Bishops
        Bitboard bishops = piece_bitboards[color][Bishop] & inverse_pin_mask;
        while (bishops) {
            square = bitboard_operations::bitScanForward(bishops);
            bitboard_operations::set_0(bishops, square);
            count += count_mask(masks::get_bishop_mask(*this, square) & check_mask, friendly);
        }

        // Queens
        Bitboard queens = piece_bitboards[color][Queen] & inverse_pin_mask;
        while (queens) {
            square = bitboard_operations::bitScanForward(queens);
            bitboard_operations::set_0(queens, square);
            count += count_mask(masks::get_bishop_mask(*this, square) & check_mask, friendly);
            count += count_mask(masks::get_rook_mask(*this, square) & check_mask, friendly);
        }

        // Knights
        Bitboard knights = piece_bitboards[color][Knight] & inverse_pin_mask;
        while (knights) {
            square = bitboard_operations::bitScanForward(knights);
            bitboard_operations::set_0(knights, square);
            count += count_mask(masks::get_knight_mask(square) & check_mask, friendly);
        }

        // King
        count += count_mask(get_king_legal_moves_mask(), friendly);
    } else {
        // Pinned pawns
        Bitboard vertical_pinned_pawns = piece_bitboards[color][Pawn] & vertical_pin_mask;
        Bitboard up_right_pinned_pawns = piece_bitboards[color][Pawn] & up_right_pin_mask;
        Bitboard up_left_pinned_pawns = piece_bitboards[color][Pawn] & up_left_pin_mask;
        count += count_pawn_mask(masks::get_pawn_mask(vertical_pinned_pawns, *this), friendly, color);
        count += count_pawn_mask(masks::get_pawn_long_mask(vertical_pinned_pawns, *this), friendly, color);
        if (color == White) {
            count += count_pawn_mask(masks::get_pawn_right_mask(up_right_pinned_pawns, *this), friendly, color);
            count += count_pawn_mask(masks::get_pawn_left_mask(up_left_pinned_pawns, *this), friendly, color);
        } else {
            count += count_pawn_mask(masks::get_pawn_right_mask(up_left_pinned_pawns, *this), friendly, color);
            count += count_pawn_mask(masks::get_pawn_left_mask(up_right_pinned_pawns, *this), friendly, color);
        }

        // Pinned rooks
        Bitboard pinned_rooks = piece_bitboards[color][Rook] & (horizontal_pin_mask | vertical_pin_mask);
        while (pinned_rooks) {
            square = bitboard_operations::bitScanForward(pinned_rooks);
            bitboard_operations::set_0(pinned_rooks, square);
            count +=
                count_mask(masks::get_rook_mask(*this, square) & (horizontal_pin_mask | vertical_pin_mask), friendly);
        }

        // Pinned bishops
        Bitboard pinned_bishops = piece_bitboards[color][Bishop] & (up_right_pin_mask | up_left_pin_mask);
        while (pinned_bishops) {
            square = bitboard_operations::bitScanForward(pinned_bishops);
            bitboard_operations::set_0(pinned_bishops, square);
            count +=
                count_mask(masks::get_bishop_mask(*this, square) & (up_right_pin_mask | up_left_pin_mask), friendly);
        }

        // Pinned queens
        Bitboard vertical_and_horizontal_pinned_queens =
            piece_bitboards[color][Queen] & (horizontal_pin_mask | vertical_pin_mask);
        Bitboard diagonal_pinned_queens = piece_bitboards[color][Queen] & (up_right_pin_mask | up_left_pin_mask);

        while (vertical_and_horizontal_pinned_queens) {
            square = bitboard_operations::bitScanForward(vertical_and_horizontal_pinned_queens);
            bitboard_operations::set_0(vertical_and_horizontal_pinned_queens, square);
            count +=
                count_mask(masks::get_rook_mask(*this, square) & (horizontal_pin_mask | vertical_pin_mask), friendly);
        }

        while (diagonal_pinned_queens) {
            square = bitboard_operations::bitScanForward(diagonal_pinned_queens);
            bitboard_operations::set_0(diagonal_pinned_queens, square);
            count +=
                count_mask(masks::get_bishop_mask(*this, square) & (up_right_pin_mask | up_left_pin_mask), friendly);
        }

        // Pawns
        Bitboard pawns = piece_bitboards[color][Pawn] & inverse_pin_mask;
        count += count_pawn_mask(masks::get_pawn_mask(pawns, *this), friendly, color);
        count += count_pawn_mask(masks::get_pawn_long_mask(pawns, *this), friendly, color);
        if (color == White) {
            count += count_pawn_mask(masks::get_pawn_right_mask(pawns, *this), friendly, color);
            count += count_pawn_mask(masks::get_pawn_left_mask(pawns, *this), friendly, color);
        } else {
            count += count_pawn_mask(masks::get_pawn_right_mask(pawns, *this), friendly, color);
            count += count_pawn_mask(masks::get_pawn_left_mask(pawns, *this), friendly, color);
        }

        // En passant
        if (en_passant_square >= 0) {
            uint8_t captured_sq = (color == White) ? en_passant_square - 8 : en_passant_square + 8;
            Bitboard ep_masks[] = {masks::get_right_en_passant_mask(pawns, *this),
                                   masks::get_left_en_passant_mask(pawns, *this)};
            int deltas_w[] = {9, 7};
            int deltas_b[] = {7, 9};
            int* deltas = (color == White) ? deltas_w : deltas_b;

            for (int d = 0; d < 2; d++) {
                Bitboard ep = ep_masks[d];
                while (ep) {
                    uint8_t target = bitboard_operations::bitScanForward(ep);
                    bitboard_operations::set_0(ep, target);
                    uint8_t src = white_turn ? target - deltas[d] : target + deltas[d];

                    bitboard_operations::set_0(piece_bitboards[color][Pawn], src);
                    bitboard_operations::set_0(side_bitboards[color], src);
                    bitboard_operations::set_0(all, src);
                    bitboard_operations::set_0(piece_bitboards[1 - color][Pawn], captured_sq);
                    bitboard_operations::set_0(side_bitboards[1 - color], captured_sq);
                    bitboard_operations::set_0(all, captured_sq);
                    bitboard_operations::set_1(piece_bitboards[color][Pawn], target);
                    bitboard_operations::set_1(side_bitboards[color], target);
                    bitboard_operations::set_1(all, target);

                    bool valid = !is_check();

                    bitboard_operations::set_1(piece_bitboards[color][Pawn], src);
                    bitboard_operations::set_1(side_bitboards[color], src);
                    bitboard_operations::set_1(all, src);
                    bitboard_operations::set_1(piece_bitboards[1 - color][Pawn], captured_sq);
                    bitboard_operations::set_1(side_bitboards[1 - color], captured_sq);
                    bitboard_operations::set_1(all, captured_sq);
                    bitboard_operations::set_0(piece_bitboards[color][Pawn], target);
                    bitboard_operations::set_0(side_bitboards[color], target);
                    bitboard_operations::set_0(all, target);

                    if (valid)
                        count++;
                }
            }
        }

        // Rooks
        Bitboard rooks = piece_bitboards[color][Rook] & inverse_pin_mask;
        while (rooks) {
            square = bitboard_operations::bitScanForward(rooks);
            bitboard_operations::set_0(rooks, square);
            count += count_mask(masks::get_rook_mask(*this, square), friendly);
        }

        // Bishops
        Bitboard bishops = piece_bitboards[color][Bishop] & inverse_pin_mask;
        while (bishops) {
            square = bitboard_operations::bitScanForward(bishops);
            bitboard_operations::set_0(bishops, square);
            count += count_mask(masks::get_bishop_mask(*this, square), friendly);
        }

        // Queens
        Bitboard queens = piece_bitboards[color][Queen] & inverse_pin_mask;
        while (queens) {
            square = bitboard_operations::bitScanForward(queens);
            bitboard_operations::set_0(queens, square);
            count += count_mask(masks::get_bishop_mask(*this, square), friendly);
            count += count_mask(masks::get_rook_mask(*this, square), friendly);
        }

        // Knights
        Bitboard knights = piece_bitboards[color][Knight] & inverse_pin_mask;
        while (knights) {
            square = bitboard_operations::bitScanForward(knights);
            bitboard_operations::set_0(knights, square);
            count += count_mask(masks::get_knight_mask(square), friendly);
        }

        // King
        count += count_mask(get_king_legal_moves_mask(), friendly);

        // Castling
        {
            if (color == White) {
                if (w_l_castling && bitboard_operations::get_bit(piece_bitboards[White][Rook], 0) &&
                    !bitboard_operations::get_bit(all, 1) && !bitboard_operations::get_bit(all, 2) &&
                    !bitboard_operations::get_bit(all, 3) &&
                    bitboard_operations::get_bit(piece_bitboards[White][King], 4) && !is_position_attacked(2) &&
                    !is_position_attacked(3))
                    count++;
                if (w_s_castling && bitboard_operations::get_bit(piece_bitboards[White][Rook], 7) &&
                    !bitboard_operations::get_bit(all, 5) && !bitboard_operations::get_bit(all, 6) &&
                    bitboard_operations::get_bit(piece_bitboards[White][King], 4) && !is_position_attacked(5) &&
                    !is_position_attacked(6))
                    count++;
            } else {
                if (b_l_castling && bitboard_operations::get_bit(piece_bitboards[Black][Rook], 56) &&
                    !bitboard_operations::get_bit(all, 57) && !bitboard_operations::get_bit(all, 58) &&
                    !bitboard_operations::get_bit(all, 59) &&
                    bitboard_operations::get_bit(piece_bitboards[Black][King], 60) && !is_position_attacked(58) &&
                    !is_position_attacked(59))
                    count++;
                if (b_s_castling && bitboard_operations::get_bit(piece_bitboards[Black][Rook], 63) &&
                    !bitboard_operations::get_bit(all, 61) && !bitboard_operations::get_bit(all, 62) &&
                    bitboard_operations::get_bit(piece_bitboards[Black][King], 60) && !is_position_attacked(61) &&
                    !is_position_attacked(62))
                    count++;
            }
        }
    }

    return count;
}

chess::MoveArray chess::Board::get_legal_moves_for_position(uint8_t x) {
    MoveArray moves = MoveArray();
    get_legal_moves();

    for (int i = 0; i < legal_moves.size(); i++) {
        if (legal_moves.moves[i].from() == x) {
            moves.push_back(legal_moves.moves[i]);
        }
    }

    return moves;
}

chess::MoveArray chess::Board::distil_pawn_moves(MoveArray moves) {
    MoveArray distilled_moves;

    for (int i = 0; i < moves.size(); i++) {
        if (moves[i].piece_type() == Pawn and moves[i].attacker_color() == White and moves[i].to() >= 56) {
            for (uint8_t promo : {Queen, Rook, Bishop, Knight}) {
                Move m = Move::make(moves[i].from(), moves[i].to(), moves[i].piece_type(), moves[i].attacker_color(),
                                    moves[i].captured_type(), moves[i].captured_color(), MT_NORMAL, promo);
                distilled_moves.push_back(m);
            }
        } else if (moves[i].piece_type() == Pawn and moves[i].attacker_color() == Black and moves[i].to() <= 7) {
            for (uint8_t promo : {Queen, Rook, Bishop, Knight}) {
                Move m = Move::make(moves[i].from(), moves[i].to(), moves[i].piece_type(), moves[i].attacker_color(),
                                    moves[i].captured_type(), moves[i].captured_color(), MT_NORMAL, promo);
                distilled_moves.push_back(m);
            }
        } else {
            distilled_moves.push_back(moves[i]);
        }
    }

    return distilled_moves;
}