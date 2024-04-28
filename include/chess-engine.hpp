#pragma once

#include <string>
#include <vector>
#include <utility>
#include <memory>
#include <array>

#include "headers/Board.hpp"
#include "headers/chess_operation.shpp"


namespace chess {

    // Вывод доски в поток
    std::ostream& operator<<(std::ostream &ostream, chess::Board board);

    std::array<std::array<Bitboard, 6>, 2> convert_fen_to_bitboards(std::string fen);

    static constexpr uint8_t Pawn = 0;
    static constexpr uint8_t Knight = 1;
    static constexpr uint8_t Bishop = 2;
    static constexpr uint8_t Rook = 3;
    static constexpr uint8_t Queen = 4;
    static constexpr uint8_t King = 5;

    static constexpr uint8_t White = 0;
    static constexpr uint8_t Black = 1;




}