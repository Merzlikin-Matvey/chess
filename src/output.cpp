#include <chess-engine.hpp>

#include <iostream>

std::ostream& operator<<(std::ostream &ostream, const chess::Board& board) {
    for (int8_t y = 7; y >= 0; y = y - 1) {
        for (uint8_t x = 0; x < 8; x = x + 1) {
            ostream << "|  ";

            if (chess_operations::get_bit(board._piece_bitboards[chess::White][chess::Pawn], y * 8 + x)) ostream << "P";
            else if (chess_operations::get_bit(board._piece_bitboards[chess::White][chess::Knight], y * 8 + x)) ostream << "N";
            else if (chess_operations::get_bit(board._piece_bitboards[chess::White][chess::Bishop], y * 8 + x)) ostream << "B";
            else if (chess_operations::get_bit(board._piece_bitboards[chess::White][chess::Rook], y * 8 + x)) ostream << "R";
            else if (chess_operations::get_bit(board._piece_bitboards[chess::White][chess::Queen], y * 8 + x)) ostream << "Q";
            else if (chess_operations::get_bit(board._piece_bitboards[chess::White][chess::King], y * 8 + x)) ostream << "K";

            else if (chess_operations::get_bit(board._piece_bitboards[chess::Black][chess::Pawn], y * 8 + x)) ostream << "p";
            else if (chess_operations::get_bit(board._piece_bitboards[chess::Black][chess::Knight], y * 8 + x)) ostream << "n";
            else if (chess_operations::get_bit(board._piece_bitboards[chess::Black][chess::Bishop], y * 8 + x)) ostream << "b";
            else if (chess_operations::get_bit(board._piece_bitboards[chess::Black][chess::Rook], y * 8 + x)) ostream << "r";
            else if (chess_operations::get_bit(board._piece_bitboards[chess::Black][chess::Queen], y * 8 + x)) ostream << "q";
            else if (chess_operations::get_bit(board._piece_bitboards[chess::Black][chess::King], y * 8 + x)) ostream << "k";

            else ostream << " ";

            ostream << "  ";
        }
        ostream << "|\n";
    }

    return ostream;
}