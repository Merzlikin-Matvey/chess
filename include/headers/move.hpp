#pragma once

#include <memory>

class Move {
public:
    Move(uint8_t first,
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
         uint8_t pawn_change_type);


    uint8_t _first;
    uint8_t _first_side;
    uint8_t _first_type;

    uint8_t _second;
    uint8_t _second_side;
    uint8_t _second_type;

    bool _w_l_castling = false;
    bool _w_s_castling = false;
    bool _b_l_castling = false;
    bool _b_s_castling = false;

    bool _pawn_double_move = false;
    uint8_t _pawn_change_type = 255;
};