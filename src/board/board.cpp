#include "headers/board.hpp"

#include <cstring>
#include <sstream>
#include <string>

#include "headers/bitboard_operations.hpp"
#include "headers/constants.hpp"
#include "headers/fen.hpp"
#include "headers/notations.hpp"

void chess::Board::init_mailbox() {
    std::memset(mailbox, 255, 64);
    for (uint8_t color = 0; color < 2; color++) {
        for (uint8_t piece = 0; piece < 6; piece++) {
            Bitboard bb = piece_bitboards[color][piece];
            while (bb) {
                const int sq = bitboard_operations::bitScanForward(bb);
                bitboard_operations::set_0(bb, sq);
                mailbox[sq] = color << 3 | piece;
            }
        }
    }
}

chess::Board::Board(std::array<std::array<Bitboard, 6>, 2> board) {
    piece_bitboards = board;
    side_bitboards = {0, 0};
    all = 0;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 6; j++) {
            side_bitboards[i] |= board[i][j];
        }
    }
    all = side_bitboards[0] | side_bitboards[1];
    init_mailbox();
    hashes.push_back(zobrist::ZobristHash(*this));
    current_hash = hashes.back().hash;
}

chess::Board::Board(std::string fen) {
    std::istringstream iss(fen);
    std::string piece_placement;
    iss >> piece_placement;

    piece_bitboards = convert_fen_to_bitboards(piece_placement);
    side_bitboards = {0, 0};
    all = 0;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 6; j++) {
            side_bitboards[i] |= piece_bitboards[i][j];
        }
    }
    all = side_bitboards[0] | side_bitboards[1];
    init_mailbox();

    std::string active_color;
    if (iss >> active_color) {
        white_turn = active_color == "w";

        std::string castling_str;
        if (iss >> castling_str) {
            if (castling_str != "-") {
                w_s_castling = castling_str.find('K') != std::string::npos;
                w_l_castling = castling_str.find('Q') != std::string::npos;
                b_s_castling = castling_str.find('k') != std::string::npos;
                b_l_castling = castling_str.find('q') != std::string::npos;
            }

            std::string en_passant_str;
            if (iss >> en_passant_str) {
                if (en_passant_str != "-") {
                    en_passant_square = position_to_number_notation(en_passant_str);
                }

                std::string halfmove_str;
                if (iss >> halfmove_str) {
                    halfmove_clock = std::stoi(halfmove_str);

                    std::string fullmove_str;
                    if (iss >> fullmove_str) {
                        int fullmove = std::stoi(fullmove_str);
                        num_of_moves = fullmove - 1 + (white_turn ? 0.0 : 0.5);
                    }
                }
            }
        }
    }

    hashes.push_back(zobrist::ZobristHash(*this));
    current_hash = hashes.back().hash;
}

chess::Board::Board() {
    const std::array<std::array<Bitboard, 6>, 2> board = convert_default_positions();
    piece_bitboards = board;
    side_bitboards = {0, 0};
    all = 0;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 6; j++) {
            side_bitboards[i] |= board[i][j];
        }
    }
    all = side_bitboards[0] | side_bitboards[1];
    init_mailbox();
    w_l_castling = true;
    w_s_castling = true;
    b_l_castling = true;
    b_s_castling = true;
    hashes.push_back(zobrist::ZobristHash(*this));
    current_hash = hashes.back().hash;
}

bool chess::Board::operator==(const Board& board) const {
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 6; j++) {
            if (piece_bitboards[i][j] != board.piece_bitboards[i][j]) {
                return false;
            }
        }
    }
    return true;
}

bool chess::Board::operator!=(const Board& board) const {
    return !(*this == board);
}

int8_t chess::Board::get_piece_type(const Board& board, uint8_t x, uint8_t y) {
    for (int i = 0; i < 6; i++) {
        if (bitboard_operations::get_bit(board.piece_bitboards[White][i], y * 8 + x))
            return i;
        if (bitboard_operations::get_bit(board.piece_bitboards[Black][i], y * 8 + x))
            return i + 6;
    }
    return -1;
}

int8_t chess::Board::get_piece_type(const Board& board, uint8_t x) {
    for (int i = 0; i < 6; i++) {
        if (bitboard_operations::get_bit(board.piece_bitboards[White][i], x))
            return i;
        if (bitboard_operations::get_bit(board.piece_bitboards[Black][i], x))
            return i + 6;
    }
    return -1;
}

std::string chess::Board::to_fen()const {
    std::string fen = bitboards_to_fen(piece_bitboards);

    fen += white_turn ? " w " : " b ";

    std::string castling;
    if (w_s_castling)
        castling += 'K';
    if (w_l_castling)
        castling += 'Q';
    if (b_s_castling)
        castling += 'k';
    if (b_l_castling)
        castling += 'q';
    if (castling.empty())
        castling = "-";
    fen += castling;

    if (en_passant_square >= 0) {
        fen += " " + position_to_chess_notation(en_passant_square);
    } else {
        fen += " -";
    }

    fen += " " + std::to_string(halfmove_clock);

    int fullmove = static_cast<int>(num_of_moves) + 1;
    fen += " " + std::to_string(fullmove);

    return fen;
}

chess::Board& chess::Board::operator=(const Board& other) {
    piece_bitboards = other.piece_bitboards;
    side_bitboards = other.side_bitboards;
    all = other.all;
    white_turn = other.white_turn;
    w_l_castling = other.w_l_castling;
    w_s_castling = other.w_s_castling;
    b_l_castling = other.b_l_castling;
    b_s_castling = other.b_s_castling;
    en_passant_square = other.en_passant_square;
    halfmove_clock = other.halfmove_clock;
    num_of_moves = other.num_of_moves;
    legal_moves = other.legal_moves;
    hashes = other.hashes;
    current_hash = other.current_hash;
    move_history = other.move_history;
    std::ranges::copy(other.mailbox, std::begin(mailbox));

    return *this;
}