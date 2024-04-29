#include "headers/move.hpp"
#include "headers/board.hpp"
#include "headers/constants.hpp"
#include "headers/bitboard_operations.hpp"

#include <iostream>

chess::Move::Move(uint8_t first,
           uint8_t first_side,
           uint8_t first_type,
           uint8_t second,
           uint8_t second_side,
           uint8_t second_type,
           bool w_l_castling,
           bool w_s_castling,
           bool b_l_castling,
           bool b_s_castling,
           bool pawn_double_move,
           bool en_passant,
           uint8_t pawn_change_type) {

    this->first = first;
    this->first_side = first_side;
    this->first_type = first_type;

    this->second = second;
    this->second_side = second_side;
    this->second_type = second_type;

    this->w_l_castling = w_l_castling;
    this->w_s_castling = w_s_castling;
    this->b_l_castling = b_l_castling;
    this->b_s_castling = b_s_castling;

    this->pawn_double_move = pawn_double_move;
    this->en_passant = en_passant;
    this->pawn_change_type = pawn_change_type;
}

void chess::Board::move(chess::Move move){
    bitboard_operations::set_0(_piece_bitboards[move.first_side][move.first_type], move.first);
    if (move.second_type == 255){
        bitboard_operations::set_1(_piece_bitboards[move.first_side][move.first_type], move.second);
    }
    else {
        bitboard_operations::set_0(_piece_bitboards[move.second_side][move.second_type], move.second);
        bitboard_operations::set_1(_piece_bitboards[move.first_side][move.first_type], move.second);
    }
}