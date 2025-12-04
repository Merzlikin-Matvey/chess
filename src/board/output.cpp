#include "headers/bitboard_operations.hpp"
#include "headers/board.hpp"
#include "headers/constants.hpp"
#include "headers/move.hpp"

#include <iostream>


std::ostream& chess::operator<<(std::ostream& ostream, chess::Board board) {
    for (int8_t y = 7; y >= 0; y = y - 1) {
        for (uint8_t x = 0; x < 8; x = x + 1) {
            int8_t piece = board.get_piece_type(board, x, y);
            switch (piece) {
            case Pawn:
                ostream << "P";
                break;
            case Knight:
                ostream << "N";
                break;
            case Bishop:
                ostream << "B";
                break;
            case Rook:
                ostream << "R";
                break;
            case Queen:
                ostream << "Q";
                break;
            case King:
                ostream << "K";
                break;
            case Pawn + 6:
                ostream << "p";
                break;
            case Rook + 6:
                ostream << "r";
                break;
            case Bishop + 6:
                ostream << "b";
                break;
            case Knight + 6:
                ostream << "n";
                break;
            case Queen + 6:
                ostream << "q";
                break;
            case King + 6:
                ostream << "k";
                break;
            default:
                ostream << ".";
                break;
            }

            ostream << "  ";
        }
        ostream << std::endl;
    }

    return ostream;
}

void chess::print_bitboard(Bitboard bitboard) {
    for (int8_t y = 7; y >= 0; y = y - 1) {
        for (uint8_t x = 0; x < 8; x = x + 1) {
            if (bitboard_operations::get_bit(bitboard, y * 8 + x)) {
                std::cout << "1";
            } else {
                std::cout << "0";
            }
        }
        std::cout << std::endl;
    }
}
