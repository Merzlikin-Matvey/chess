#include "headers/board.hpp"
#include "headers/bitboard_operations.hpp"

#include <iostream>


std::ostream& chess::operator<<(std::ostream &ostream, chess::Board board) {
    for (int8_t y = 7; y >= 0; y = y - 1) {
        for (uint8_t x = 0; x < 8; x = x + 1) {
            int8_t piece = board.get_piece_type(board, x, y);
            switch (piece) {
                case 0:
                    ostream << "P";
                    break;
                case 1:
                    ostream << "N";
                    break;
                case 2:
                    ostream << "B";
                    break;
                case 3:
                    ostream << "R";
                    break;
                case 4:
                    ostream << "Q";
                    break;
                case 5:
                    ostream << "K";
                    break;
                case 6:
                    ostream << "p";
                    break;
                case 7:
                    ostream << "n";
                    break;
                case 8:
                    ostream << "b";
                    break;
                case 9:
                    ostream << "r";
                    break;
                case 10:
                    ostream << "q";
                    break;
                case 11:
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
            }
            else {
                std::cout << "0";
            }
        }
        std::cout << std::endl;
    }
}