#pragma once

#include "headers/board.hpp"
#include "headers/constants.hpp"
#include "headers/masks/masks.hpp"
#include "headers/bitboard_lines.hpp"



inline Bitboard _get_rook_mask(chess::Board& board, uint8_t square) {
    Bitboard mask = board.all & chess::masks::secondary_rook_masks[square];
    int hash = chess::masks::get_rook_hash(mask, square);
    return chess::masks::primary_rook_masks[square][hash];
}

inline Bitboard _get_bishop_mask(chess::Board& board, uint8_t square) {
    std::cout << "Second" << std::endl;
    chess::print_bitboard(chess::masks::secondary_bishop_masks[square]);
    std::cout << std::endl;
    Bitboard mask = board.all & chess::masks::secondary_bishop_masks[square];
    int hash = chess::masks::get_bishop_hash(mask, square);
    std::cout << "Hash: " << hash << std::endl;
    return chess::masks::primary_bishop_masks[square][hash];
}

inline Bitboard _get_knight_mask(uint8_t square) {
    return chess::masks::knight_masks[square];
}

inline Bitboard _get_king_mask(uint8_t square) {
    return chess::masks::king_masks[square];
}

inline bool chess::Board::is_position_attacked(uint8_t x) {
    uint8_t color = white_turn ? White : Black;
    Bitboard rook_mask = _get_rook_mask(*this, x);
    Bitboard bishop_mask = _get_bishop_mask(*this, x);
    Bitboard king_mask = _get_king_mask(x);
    Bitboard knight_mask = _get_knight_mask(x);

    if (rook_mask & (piece_bitboards[!color][Rook] | piece_bitboards[!color][Queen])) {
        return true;
    }
    print_bitboard(bishop_mask);
    if (bishop_mask & (piece_bitboards[!color][Bishop] | piece_bitboards[!color][Queen])) {
        return true;
    }

    if (king_mask & piece_bitboards[!color][King]) {
        return true;
    }

    if (knight_mask & piece_bitboards[!color][Knight]) {
        return true;
    }

    if (color == White){
        if (x + 9 < 64){
            if (bitboard_operations::get_bit(piece_bitboards[!color][Pawn], x + 9)) {
                return true;
            }
        }
        if (x + 7 < 64){
            if (bitboard_operations::get_bit(piece_bitboards[!color][Pawn], x + 7)) {
                return true;
            }
        }
    }
    else {
        if (x >= 9){
            if (bitboard_operations::get_bit(piece_bitboards[!color][Pawn], x - 9)) {
                return true;
            }
        }

        if (x >= 7){
            if (bitboard_operations::get_bit(piece_bitboards[!color][Pawn], x - 7)) {
                return true;
            }
        }
    }

    return false;
}


inline bool chess::Board::is_check() {
    uint8_t color = white_turn ? White : Black;
    uint8_t king_index = bitboard_operations::bitScanForward(piece_bitboards[color][King]);
    return is_position_attacked(king_index);
}


inline bool chess::Board::is_double_check() {
    uint16_t count = 0;
    uint8_t king_index = bitboard_operations::bitScanForward(piece_bitboards[white_turn ? White : Black][King]);
    uint8_t color = white_turn ? White : Black;
    Bitboard rook_mask = _get_rook_mask(*this, king_index);
    Bitboard bishop_mask = _get_bishop_mask(*this, king_index);
    Bitboard king_mask = _get_king_mask(king_index);
    Bitboard knight_mask = _get_knight_mask(king_index);

    count += bitboard_operations::count_1(rook_mask & (piece_bitboards[!color][Rook] | piece_bitboards[!color][Queen]));
    count += bitboard_operations::count_1(bishop_mask & (piece_bitboards[!color][Bishop] | piece_bitboards[!color][Queen]));
    count += bitboard_operations::count_1(king_mask & piece_bitboards[!color][King]);
    count += bitboard_operations::count_1(knight_mask & piece_bitboards[!color][Knight]);

    if (color == White){
        if (king_index + 9 < 64){
            if (bitboard_operations::get_bit(piece_bitboards[!color][Pawn], king_index + 9)) {
                count++;
            }
        }
        if (king_index + 7 < 64){
            if (bitboard_operations::get_bit(piece_bitboards[!color][Pawn], king_index + 7)) {
                count++;
            }
        }
    }
    else {
        if (king_index >= 9){
            if (bitboard_operations::get_bit(piece_bitboards[!color][Pawn], king_index - 9)) {
                count++;
            }
        }

        if (king_index >= 7){
            if (bitboard_operations::get_bit(piece_bitboards[!color][Pawn], king_index - 7)) {
                count++;
            }
        }
    }

    return count >= 2;
}


inline bool chess::Board::is_checkmate() {
    MoveArray& moves = get_legal_moves();
    return moves.size() == 0;
}


inline Bitboard chess::Board::get_check_mask() {
    uint8_t color = white_turn ? White : Black;
    uint8_t king_index = bitboard_operations::bitScanForward(piece_bitboards[color][King]);
    uint8_t opponent_index;
    Bitboard rook_mask = _get_rook_mask(*this, king_index);
    Bitboard bishop_mask = _get_bishop_mask(*this, king_index);
    Bitboard king_mask = _get_king_mask(king_index);
    Bitboard knight_mask = _get_knight_mask(king_index);

    if (rook_mask & (piece_bitboards[!color][Rook] | piece_bitboards[!color][Queen])) {
        opponent_index = bitboard_operations::bitScanForward(rook_mask & (piece_bitboards[!color][Rook] | piece_bitboards[!color][Queen]));
        return chess::masks::lines[opponent_index][king_index];
    }

    if (bishop_mask & (piece_bitboards[!color][Bishop] | piece_bitboards[!color][Queen])) {
        opponent_index = bitboard_operations::bitScanForward(bishop_mask & (piece_bitboards[!color][Bishop] | piece_bitboards[!color][Queen]));
        return chess::masks::lines[opponent_index][king_index];
    }

    if (king_mask & piece_bitboards[!color][King]) {
        opponent_index = bitboard_operations::bitScanForward(king_mask & piece_bitboards[!color][King]);
        return chess::masks::lines[opponent_index][king_index];
    }

    if (knight_mask & piece_bitboards[!color][Knight]) {
        opponent_index = bitboard_operations::bitScanForward(knight_mask & piece_bitboards[!color][Knight]);
        return chess::masks::lines[opponent_index][king_index];
    }

    if (color == White){
        if (king_index + 9 < 64){
            if (bitboard_operations::get_bit(piece_bitboards[!color][Pawn], king_index + 9)) {
                opponent_index = king_index + 9;
                return chess::masks::lines[opponent_index][king_index];
            }
        }
        if (king_index + 7 < 64){
            if (bitboard_operations::get_bit(piece_bitboards[!color][Pawn], king_index + 7)) {
                opponent_index = king_index + 7;
                return chess::masks::lines[opponent_index][king_index];
            }
        }
    }
    else {
        if (king_index >= 9){
            if (bitboard_operations::get_bit(piece_bitboards[!color][Pawn], king_index - 9)) {
                opponent_index = king_index - 9;
                return chess::masks::lines[opponent_index][king_index];
            }
        }

        if (king_index >= 7){
            if (bitboard_operations::get_bit(piece_bitboards[!color][Pawn], king_index - 7)) {
                opponent_index = king_index - 7;
                return chess::masks::lines[opponent_index][king_index];
            }
        }
    }

    return 0;
}

inline bool chess::Board::is_draw() {
    uint8_t pawn_material = 1;
    uint8_t knight_material = 3;
    uint8_t bishop_material = 3;
    uint8_t rook_material = 5;
    uint8_t queen_material = 9;

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

    return num_of_moves >= 50 || get_num_of_repetitions() >= 3 || count <= 4;
}

inline int chess::Board::get_winner() {
    if (is_checkmate()){
        return white_turn ? Black : White;
    }
    if (is_draw()){
        return 2;
    }
    return -1;
}