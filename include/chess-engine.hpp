#pragma once

#include <string>
#include <vector>
#include <utility>
#include <memory>
#include <array>

typedef uint64_t Bitboard;

namespace chess_operations {
    static constexpr void set_1(Bitboard &bb, uint8_t square) {
        bb = bb | (1ull << square);
    }
    static constexpr void set_0(Bitboard &bb, uint8_t square) {
        bb = bb & (~(1ull << square));
    }

    static constexpr bool get_bit(Bitboard bb, uint8_t square) {
        return (bb & (1ull << square));
    }
}

namespace chess {

    class Board {
    public:
        Board(std::array<std::array<Bitboard, 6>, 2> board);
        std::array<std::array<Bitboard, 6>, 2> _piece_bitboards{};
        std::array<Bitboard, 2> _side_bitboards{};
        std::array<Bitboard, 2> _inversion_side_bitboards{};
        Bitboard _all;

        bool operator == (const Board &board) const;
        bool operator != (const Board &board) const;
    };

    // Вывод доски в поток
    std::ostream& operator<<(std::ostream &ostream, const chess::Board& board);

    std::array<std::array<Bitboard, 6>, 2> convert_fen_to_bitboards(std::string fen);

    static constexpr uint8_t Pawn = 0;
    static constexpr uint8_t Knight = 1;
    static constexpr uint8_t Bishop = 2;
    static constexpr uint8_t Rook = 3;
    static constexpr uint8_t Queen = 4;
    static constexpr uint8_t King = 5;

    static constexpr uint8_t White = 0;
    static constexpr uint8_t Black = 1;





    std::string get_path_to_res(std::string file_name);



}