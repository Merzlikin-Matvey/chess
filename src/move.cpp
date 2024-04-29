#include "headers/move.hpp"

Move::Move(uint8_t first,
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

    _first = first;
    _first_side = first_side;
    _first_type = first_type;

    _second = second;
    _second_side = second_side;
    _second_type = second_type;

    _w_l_castling = w_l_castling;
    _w_s_castling = w_s_castling;
    _b_l_castling = b_l_castling;
    _b_s_castling = b_s_castling;

    _pawn_double_move = pawn_double_move;
    _pawn_change_type = pawn_change_type;
}