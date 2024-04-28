#include <chess-engine.hpp>

std::array<std::array<Bitboard, 6>, 2> chess::convert_fen_to_bitboards(std::string fen){
    std::array<std::array<Bitboard, 6>, 2> piece_bitboards = {{{0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}}};
    uint8_t x = 0;
    uint8_t y = 7;

    uint8_t side;

    for (auto symbol : fen){
        if (symbol == '/'){
            y--;
            x = 0;
        } else if (symbol == ' '){
            break;
        } else if (symbol == 'w'){
            side = White;
        } else if (symbol == 'b'){
            side = Black;
        } else {
            if (isdigit(symbol)){
                x += symbol - '0';
            } else {
                uint8_t piece;
                switch (symbol){
                    case 'P':
                        piece = Pawn;
                        break;
                    case 'N':
                        piece = Knight;
                        break;
                    case 'B':
                        piece = Bishop;
                        break;
                    case 'R':
                        piece = Rook;
                        break;
                    case 'Q':
                        piece = Queen;
                        break;
                    case 'K':
                        piece = King;
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
                chess_operations::set_1(piece_bitboards[side][piece], y * 8 + x);
                x++;
            }
        }
    }

    return piece_bitboards;

}