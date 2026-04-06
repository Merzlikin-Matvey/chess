#include "headers/board.hpp"
#include "headers/bitboard_lines.hpp"
#include "headers/bitboard_operations.hpp"
#include "headers/constants.hpp"
#include "headers/masks/masks.hpp"


Bitboard get_absolute_rook_mask(chess::Board &board, const uint8_t square) {
    const Bitboard mask = board.all & chess::masks::secondary_rook_masks[square];
    const int hash = chess::masks::get_rook_hash(mask, square);
    return chess::masks::primary_rook_masks[square][hash];
}

Bitboard get_absolute_bishop_mask(chess::Board &board, const uint8_t square) {
    const Bitboard mask = board.all & chess::masks::secondary_bishop_masks[square];
    const int hash = chess::masks::get_bishop_hash(mask, square);
    return chess::masks::primary_bishop_masks[square][hash];
}

Bitboard get_absolute_knight_mask(const uint8_t square) {
    return chess::masks::knight_masks[square];
}

Bitboard get_absolute_king_mask(const uint8_t square) {
    return chess::masks::king_masks[square];
}
    

bool chess::Board::is_position_attacked(const uint8_t x) {
    const uint8_t color = white_turn ? White : Black;
    const Bitboard rook_mask = get_absolute_rook_mask(*this, x);
    const Bitboard bishop_mask = get_absolute_bishop_mask(*this, x);
    const Bitboard king_mask = get_absolute_king_mask(x);
    const Bitboard knight_mask = get_absolute_knight_mask(x);

    if (rook_mask & (piece_bitboards[!color][Rook] | piece_bitboards[!color][Queen])) {
        return true;
    }

    if (bishop_mask & (piece_bitboards[!color][Bishop] | piece_bitboards[!color][Queen])) {
        return true;
    }

    if (king_mask & piece_bitboards[!color][King]) {
        return true;
    }

    if (knight_mask & piece_bitboards[!color][Knight]) {
        return true;
    }

    if (color == White) {
        if (x + 9 < 64) {
            if (bitboard_operations::get_bit(piece_bitboards[!color][Pawn], x + 9)) {
                return true;
            }
        }
        if (x + 7 < 64) {
            if (bitboard_operations::get_bit(piece_bitboards[!color][Pawn], x + 7)) {
                return true;
            }
        }
    } else {
        if (x >= 9) {
            if (bitboard_operations::get_bit(piece_bitboards[!color][Pawn], x - 9)) {
                return true;
            }
        }

        if (x >= 7) {
            if (bitboard_operations::get_bit(piece_bitboards[!color][Pawn], x - 7)) {
                return true;
            }
        }
    }

    return false;
}

bool chess::Board::is_check() {
    const uint8_t color = white_turn ? White : Black;
    const uint8_t king_index = bitboard_operations::bitScanForward(piece_bitboards[color][King]);
    return is_position_attacked(king_index);
}

bool chess::Board::is_double_check() {
    uint16_t count = 0;
    const uint8_t king_index = bitboard_operations::bitScanForward(piece_bitboards[white_turn ? White : Black][King]);
    const uint8_t color = white_turn ? White : Black;
    const Bitboard rook_mask = get_absolute_rook_mask(*this, king_index);
    const Bitboard bishop_mask = get_absolute_bishop_mask(*this, king_index);
    const Bitboard king_mask = get_absolute_king_mask(king_index);
    const Bitboard knight_mask = get_absolute_knight_mask(king_index);

    count += bitboard_operations::count_1(rook_mask & (piece_bitboards[!color][Rook] | piece_bitboards[!color][Queen]));
    count +=
        bitboard_operations::count_1(bishop_mask & (piece_bitboards[!color][Bishop] | piece_bitboards[!color][Queen]));
    count += bitboard_operations::count_1(king_mask & piece_bitboards[!color][King]);
    count += bitboard_operations::count_1(knight_mask & piece_bitboards[!color][Knight]);

    if (color == White) {
        if (king_index + 9 < 64) {
            if (bitboard_operations::get_bit(piece_bitboards[!color][Pawn], king_index + 9)) {
                count++;
            }
        }
        if (king_index + 7 < 64) {
            if (bitboard_operations::get_bit(piece_bitboards[!color][Pawn], king_index + 7)) {
                count++;
            }
        }
    } else {
        if (king_index >= 9) {
            if (bitboard_operations::get_bit(piece_bitboards[!color][Pawn], king_index - 9)) {
                count++;
            }
        }

        if (king_index >= 7) {
            if (bitboard_operations::get_bit(piece_bitboards[!color][Pawn], king_index - 7)) {
                count++;
            }
        }
    }

    return count >= 2;
}

bool chess::Board::is_checkmate() {
    const MoveArray &moves = get_legal_moves();
    return moves.size() == 0;
}

Bitboard chess::Board::get_check_mask() {
    const uint8_t color = white_turn ? White : Black;
    const uint8_t king_index = bitboard_operations::bitScanForward(piece_bitboards[color][King]);
    uint8_t opponent_index;
    const Bitboard rook_mask = get_absolute_rook_mask(*this, king_index);
    const Bitboard bishop_mask = get_absolute_bishop_mask(*this, king_index);
    const Bitboard king_mask = get_absolute_king_mask(king_index);
    const Bitboard knight_mask = get_absolute_knight_mask(king_index);

    if (rook_mask & (piece_bitboards[!color][Rook] | piece_bitboards[!color][Queen])) {
        opponent_index = bitboard_operations::bitScanForward(
            rook_mask & (piece_bitboards[!color][Rook] | piece_bitboards[!color][Queen]));
        return masks::lines[opponent_index][king_index];
    }

    if (bishop_mask & (piece_bitboards[!color][Bishop] | piece_bitboards[!color][Queen])) {
        opponent_index = bitboard_operations::bitScanForward(
            bishop_mask & (piece_bitboards[!color][Bishop] | piece_bitboards[!color][Queen]));
        return masks::lines[opponent_index][king_index];
    }

    if (king_mask & piece_bitboards[!color][King]) {
        opponent_index = bitboard_operations::bitScanForward(king_mask & piece_bitboards[!color][King]);
        return masks::lines[opponent_index][king_index];
    }

    if (knight_mask & piece_bitboards[!color][Knight]) {
        opponent_index = bitboard_operations::bitScanForward(knight_mask & piece_bitboards[!color][Knight]);
        return masks::lines[opponent_index][king_index];
    }

    if (color == White) {
        if (king_index + 9 < 64) {
            if (bitboard_operations::get_bit(piece_bitboards[!color][Pawn], king_index + 9)) {
                opponent_index = king_index + 9;
                return masks::lines[opponent_index][king_index];
            }
        }
        if (king_index + 7 < 64) {
            if (bitboard_operations::get_bit(piece_bitboards[!color][Pawn], king_index + 7)) {
                opponent_index = king_index + 7;
                return masks::lines[opponent_index][king_index];
            }
        }
    } else {
        if (king_index >= 9) {
            if (bitboard_operations::get_bit(piece_bitboards[!color][Pawn], king_index - 9)) {
                opponent_index = king_index - 9;
                return masks::lines[opponent_index][king_index];
            }
        }

        if (king_index >= 7) {
            if (bitboard_operations::get_bit(piece_bitboards[!color][Pawn], king_index - 7)) {
                opponent_index = king_index - 7;
                return masks::lines[opponent_index][king_index];
            }
        }
    }

    return 0;
}

bool chess::Board::is_draw() const {
    constexpr uint8_t pawn_material = 1;
    constexpr uint8_t knight_material = 3;
    constexpr uint8_t bishop_material = 3;
    constexpr uint8_t rook_material = 5;
    constexpr uint8_t queen_material = 9;

    int count = 0;
    count += bitboard_operations::count_1(piece_bitboards[White][Pawn]) * pawn_material;
    count += bitboard_operations::count_1(piece_bitboards[Black][Pawn]) * pawn_material;
    count += bitboard_operations::count_1(piece_bitboards[White][Knight]) * knight_material;
    count += bitboard_operations::count_1(piece_bitboards[Black][Knight]) * knight_material;
    count += bitboard_operations::count_1(piece_bitboards[White][Bishop]) * bishop_material;
    count += bitboard_operations::count_1(piece_bitboards[Black][Bishop]) * bishop_material;
    count += bitboard_operations::count_1(piece_bitboards[White][Rook]) * rook_material;
    count += bitboard_operations::count_1(piece_bitboards[Black][Rook]) * rook_material;
    count += bitboard_operations::count_1(piece_bitboards[White][Queen]) * queen_material;
    count += bitboard_operations::count_1(piece_bitboards[Black][Queen]) * queen_material;

    return num_of_moves >= 100 || get_num_of_repetitions() >= 3 || count <= 4;
}

int chess::Board::get_winner() {
    if (is_checkmate()) {
        return white_turn ? Black : White;
    }
    if (is_draw()) {
        return 2;
    }
    return -1;
}
