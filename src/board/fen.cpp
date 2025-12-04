#include "headers/fen.hpp"
#include "headers/bitboard_operations.hpp"
#include "headers/constants.hpp"

#include <iostream>
#include <string>

std::array<std::array<Bitboard, 6>, 2> chess::convert_fen_to_bitboards(std::string fen) {
    std::array<std::array<Bitboard, 6>, 2> piece_bitboards = {{{0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}}};
    uint8_t x = 0;
    uint8_t y = 7;

    uint8_t side;
    bool still_figures = true;

    for (auto symbol : fen) {
        if (symbol == '/') {
            y--;
            x = 0;
        } else if (symbol == ' ') {
            still_figures = false;
        } else if (still_figures) {
            if (isdigit(symbol)) {
                x += symbol - '0';
            } else {
                uint8_t piece;
                switch (symbol) {
                case 'P':
                    piece = Pawn;
                    side = White;
                    break;
                case 'N':
                    piece = Knight;
                    side = White;
                    break;
                case 'B':
                    piece = Bishop;
                    side = White;
                    break;
                case 'R':
                    piece = Rook;
                    side = White;
                    break;
                case 'Q':
                    piece = Queen;
                    side = White;
                    break;
                case 'K':
                    piece = King;
                    side = White;
                    break;
                case 'p':
                    piece = Pawn;
                    side = Black;
                    break;
                case 'n':
                    piece = Knight;
                    side = Black;
                    break;
                case 'b':
                    piece = Bishop;
                    side = Black;
                    break;
                case 'r':
                    piece = Rook;
                    side = Black;
                    break;
                case 'q':
                    piece = Queen;
                    side = Black;
                    break;
                case 'k':
                    piece = King;
                    side = Black;
                    break;
                }
                bitboard_operations::set_1(piece_bitboards[side][piece], y * 8 + x);
                x++;
            }
        }
    }

    return piece_bitboards;
}

std::array<std::array<Bitboard, 6>, 2> chess::convert_default_positions() {
    std::array<std::array<Bitboard, 6>, 2> piece_bitboards = {{{0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}}};
    std::string fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR";
    return convert_fen_to_bitboards(fen);
}

std::string chess::bitboards_to_fen(std::array<std::array<Bitboard, 6>, 2> piece_bitboards) {
    std::string fen = "";
    std::string figures = "PNBRQKpnbrqk";

    for (int rank = 7; rank >= 0; rank--) {
        int empty = 0;
        for (int file = 0; file < 8; file++) {
            int square = 8 * rank + file;

            bool found = false;
            for (int side = 0; side < 2; side++) {
                for (int piece = 0; piece < 6; piece++) {
                    if (bitboard_operations::get_bit(piece_bitboards[side][piece], square)) {
                        if (empty > 0) {
                            fen += std::to_string(empty);
                            empty = 0;
                        }

                        fen += figures[side * 6 + piece];
                        found = true;
                        break;
                    }

                    if (found)
                        break;
                }
                if (found)
                    break;
            }

            if (!found) {
                empty++;
            }
        }

        if (empty > 0) {
            fen += std::to_string(empty);
        }

        if (rank > 0) {
            fen += "/";
        }
    }

    return fen;
}
