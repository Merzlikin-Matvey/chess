#pragma once

#include <memory>
#include <array>

namespace chess {
    class Move {
    public:
        Move();
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


        uint8_t first;
        uint8_t first_side;
        uint8_t first_type;

        uint8_t second;
        uint8_t second_side;
        uint8_t second_type;

        bool w_l_castling = false;
        bool w_s_castling = false;
        bool b_l_castling = false;
        bool b_s_castling = false;

        bool pawn_double_move = false;
        bool en_passant = false;
        uint8_t pawn_change_type = 255;
    };

    class MoveArray {
    public:
        std::array<chess::Move, 218> moves{};
        uint8_t size;
        MoveArray();

        Move operator[](int index) const;
        void push_back(const Move move);
    };
}
