#include <chess-engine.hpp>

#include <iostream>


std::ostream& chess::operator<<(std::ostream &ostream, chess::Board board) {
    for (int8_t y = 7; y >= 0; y = y - 1) {
        for (uint8_t x = 0; x < 8; x = x + 1) {
            int8_t piece = board.getPieceType(board, x, y);
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