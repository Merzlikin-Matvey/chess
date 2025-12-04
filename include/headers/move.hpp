#pragma once

#include <array>
#include <memory>

typedef uint64_t Bitboard;

namespace chess {
    class Move {
    public:
        Move();
        Move(uint8_t first, uint8_t first_side, uint8_t first_type, uint8_t second, uint8_t second_side,
             uint8_t second_type, bool w_l_castling, bool w_s_castling, bool b_l_castling, bool b_s_castling,
             bool pawn_double_move, bool en_passant, uint8_t pawn_change_type);


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

        std::string to_string();
    };

    std::ostream& operator<<(std::ostream& ostream, chess::Move move);

    class MoveArray {
    public:
        MoveArray();
        std::array<chess::Move, 218> moves{};
        int size() const { return _size; }

        chess::Move& operator[](int index);
        const chess::Move& operator[](int index) const;
        MoveArray& operator=(const MoveArray& other) {
            if (this != &other) {
                _size = other._size;
                moves = other.moves;
            }
            return *this;
        }

        void push_back(chess::Move move);
        void clear();

        std::array<chess::Move, 218>::iterator begin() { return moves.begin(); }

        std::array<chess::Move, 218>::iterator end() { return moves.begin() + _size; }

        std::array<chess::Move, 218>::const_iterator begin() const { return moves.begin(); }

        std::array<chess::Move, 218>::const_iterator end() const { return moves.begin() + _size; }

    private:
        int _size = 0;
    };
} // namespace chess
