#pragma once

#include <algorithm>
#include <memory>
#include <array>
#include <string>
#include <cstdint>

typedef uint64_t Bitboard;

namespace chess {

    // Compact 32-bit move encoding:
    // Bits  0-5:  source square (0-63)
    // Bits  6-11: destination square (0-63)
    // Bits 12-14: move type (0=normal, 1=w_l_castle, 2=w_s_castle, 3=b_l_castle, 4=b_s_castle, 5=en_passant, 6=pawn_double)
    // Bits 15-17: moving piece type (0-5)
    // Bits 18-20: captured piece type (0-5, 7=none)
    // Bit  21:    attacker color (0=white, 1=black)
    // Bit  22:    captured color (0=white, 1=black)
    // Bits 23-25: promotion piece type (0-5, 7=none)

    enum MoveType : uint8_t {
        MT_NORMAL = 0,
        MT_W_L_CASTLE = 1,
        MT_W_S_CASTLE = 2,
        MT_B_L_CASTLE = 3,
        MT_B_S_CASTLE = 4,
        MT_EN_PASSANT = 5,
        MT_PAWN_DOUBLE = 6,
    };

    class Move {
    public:
        uint32_t data = 0;

        Move() = default;

        Move(uint8_t from, uint8_t from_color, uint8_t from_type,
             uint8_t to, uint8_t to_color, uint8_t to_type,
             bool w_l_castling, bool w_s_castling, bool b_l_castling, bool b_s_castling,
             bool pawn_double_move, bool en_passant, uint8_t pawn_change_type);

        uint8_t from() const { return data & 0x3F; }
        uint8_t to() const { return (data >> 6) & 0x3F; }
        uint8_t move_type() const { return (data >> 12) & 0x7; }
        uint8_t piece_type() const { return (data >> 15) & 0x7; }
        uint8_t captured_type() const { return (data >> 18) & 0x7; }
        uint8_t attacker_color() const { return (data >> 21) & 0x1; }
        uint8_t captured_color() const { return (data >> 22) & 0x1; }
        uint8_t promotion_type() const { return (data >> 23) & 0x7; }

        uint8_t second_side() const { return captured_type() == 7 ? 255 : captured_color(); }
        uint8_t second_type() const { return captured_type() == 7 ? 255 : captured_type(); }
        bool w_l_castling() const { return move_type() == MT_W_L_CASTLE; }
        bool w_s_castling() const { return move_type() == MT_W_S_CASTLE; }
        bool b_l_castling() const { return move_type() == MT_B_L_CASTLE; }
        bool b_s_castling() const { return move_type() == MT_B_S_CASTLE; }
        bool pawn_double_move() const { return move_type() == MT_PAWN_DOUBLE; }
        bool en_passant() const { return move_type() == MT_EN_PASSANT; }
        uint8_t pawn_change_type() const { return promotion_type() == 7 ? 255 : promotion_type(); }

        std::string to_string();

        static Move make(const uint8_t from, const uint8_t to, const uint8_t piece_type, const uint8_t attacker_color,
                         const uint8_t captured_type, const uint8_t captured_color,
                         const MoveType mt, const uint8_t promotion = 7) {
            Move m;
            m.data = (from & 0x3F)
                   | ((to & 0x3F) << 6)
                   | ((mt & 0x7) << 12)
                   | ((piece_type & 0x7) << 15)
                   | ((captured_type & 0x7) << 18)
                   | ((attacker_color & 0x1) << 21)
                   | ((captured_color & 0x1) << 22)
                   | ((promotion & 0x7) << 23);
            return m;
        }
    };

    std::ostream& operator<<(std::ostream &ostream, chess::Move move);

    class MoveArray {
    public:
        MoveArray() : _size(0) {}
        std::array<chess::Move, 218> moves{};
        int size() const{
            return _size;
        }

        chess::Move& operator[](int index);
        const chess::Move& operator[](int index) const;
        MoveArray& operator=(const MoveArray& other) {
            _size = other._size;
            std::copy_n(other.moves.begin(), _size, moves.begin());
            return *this;
        }

        void push_back(chess::Move move);
        void clear();
        void resize(int new_size) { _size = new_size; }

        std::array<chess::Move, 218>::iterator begin() {
            return moves.begin();
        }

        std::array<chess::Move, 218>::iterator end() {
            return moves.begin() + _size;
        }

        std::array<chess::Move, 218>::const_iterator begin() const {
            return moves.begin();
        }

        std::array<chess::Move, 218>::const_iterator end() const {
            return moves.begin() + _size;
        }

    private:
        int _size = 0;
    };
}
