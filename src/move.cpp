#include "headers/move.hpp"

#include <iostream>

#include "headers/bitboard_operations.hpp"
#include "headers/board.hpp"
#include "headers/constants.hpp"
#include "headers/notations.hpp"

chess::Move::Move(const uint8_t from, const uint8_t from_color, const uint8_t from_type, const uint8_t to,
                  const uint8_t to_color, const uint8_t to_type, const bool w_l_castling, const bool w_s_castling,
                  const bool b_l_castling, const bool b_s_castling, const bool pawn_double_move, const bool en_passant,
                  const uint8_t pawn_change_type) {
    MoveType mt = MT_NORMAL;
    if (w_l_castling)
        mt = MT_W_L_CASTLE;
    else if (w_s_castling)
        mt = MT_W_S_CASTLE;
    else if (b_l_castling)
        mt = MT_B_L_CASTLE;
    else if (b_s_castling)
        mt = MT_B_S_CASTLE;
    else if (en_passant)
        mt = MT_EN_PASSANT;
    else if (pawn_double_move)
        mt = MT_PAWN_DOUBLE;

    const uint8_t cap_type = to_type == 255 ? 7 : to_type;
    const uint8_t cap_color = to_color == 255 ? 0 : to_color;
    const uint8_t promo = pawn_change_type == 255 ? 7 : pawn_change_type;

    data = from & 0x3F | (to & 0x3F) << 6 | (mt & 0x7) << 12 | (from_type & 0x7) << 15 | (cap_type & 0x7) << 18 |
           (from_color & 0x1) << 21 | (cap_color & 0x1) << 22 | (promo & 0x7) << 23;
}

void chess::Board::move(const Move move) {
    if (move.second_type() == King) {
        std::cout << "KING EATING" << std::endl;
        std::cout << *this << std::endl;
        for (auto legal_move : get_legal_moves()) {
            std::cout << legal_move.to_string() << std::endl;
        }
    }
    bitboard_operations::set_0(piece_bitboards[move.attacker_color()][move.piece_type()], move.from());
    bitboard_operations::set_0(side_bitboards[move.attacker_color()], move.from());
    bitboard_operations::set_0(all, move.from());

    uint8_t placed_type = move.piece_type();
    if (move.pawn_change_type() != 255) {
        placed_type = move.pawn_change_type();
    }

    if (move.second_type() == 255) {
        bitboard_operations::set_1(piece_bitboards[move.attacker_color()][placed_type], move.to());
        bitboard_operations::set_1(side_bitboards[move.attacker_color()], move.to());
        bitboard_operations::set_1(all, move.to());
    } else {
        bitboard_operations::set_0(piece_bitboards[move.second_side()][move.second_type()], move.to());
        bitboard_operations::set_0(side_bitboards[move.second_side()], move.to());
        bitboard_operations::set_0(all, move.to());
        bitboard_operations::set_1(piece_bitboards[move.attacker_color()][placed_type], move.to());
        bitboard_operations::set_1(side_bitboards[move.attacker_color()], move.to());
        bitboard_operations::set_1(all, move.to());
    }

    mailbox[move.from()] = 255;
    mailbox[move.to()] = move.attacker_color() << 3 | placed_type;

    if (move.en_passant()) {
        if (move.attacker_color() == White) {
            bitboard_operations::set_0(piece_bitboards[Black][Pawn], move.to() - 8);
            bitboard_operations::set_0(side_bitboards[Black], move.to() - 8);
            bitboard_operations::set_0(all, move.to() - 8);
            mailbox[move.to() - 8] = 255;
        } else {
            bitboard_operations::set_0(piece_bitboards[White][Pawn], move.to() + 8);
            bitboard_operations::set_0(side_bitboards[White], move.to() + 8);
            bitboard_operations::set_0(all, move.to() + 8);
            mailbox[move.to() + 8] = 255;
        }
    }

    if (move.w_l_castling()) {
        bitboard_operations::set_1(piece_bitboards[White][King], 2);
        bitboard_operations::set_1(side_bitboards[White], 2);
        bitboard_operations::set_1(all, 2);
        bitboard_operations::set_0(piece_bitboards[White][Rook], 0);
        bitboard_operations::set_0(side_bitboards[White], 0);
        bitboard_operations::set_0(all, 0);
        bitboard_operations::set_1(piece_bitboards[White][Rook], 3);
        bitboard_operations::set_1(side_bitboards[White], 3);
        bitboard_operations::set_1(all, 3);
        mailbox[2] = White << 3 | King;
        mailbox[0] = 255;
        mailbox[3] = White << 3 | Rook;
    } else if (move.w_s_castling()) {
        bitboard_operations::set_1(piece_bitboards[White][King], 6);
        bitboard_operations::set_1(side_bitboards[White], 6);
        bitboard_operations::set_1(all, 6);
        bitboard_operations::set_0(piece_bitboards[White][Rook], 7);
        bitboard_operations::set_0(side_bitboards[White], 7);
        bitboard_operations::set_0(all, 7);
        bitboard_operations::set_1(piece_bitboards[White][Rook], 5);
        bitboard_operations::set_1(side_bitboards[White], 5);
        bitboard_operations::set_1(all, 5);
        mailbox[6] = White << 3 | King;
        mailbox[7] = None;
        mailbox[5] = White << 3 | Rook;
    } else if (move.b_l_castling()) {
        bitboard_operations::set_1(piece_bitboards[Black][King], 58);
        bitboard_operations::set_1(side_bitboards[Black], 58);
        bitboard_operations::set_1(all, 58);
        bitboard_operations::set_0(piece_bitboards[Black][Rook], 56);
        bitboard_operations::set_0(side_bitboards[Black], 56);
        bitboard_operations::set_0(all, 56);
        bitboard_operations::set_1(piece_bitboards[Black][Rook], 59);
        bitboard_operations::set_1(side_bitboards[Black], 59);
        bitboard_operations::set_1(all, 59);
        mailbox[58] = Black << 3 | King;
        mailbox[56] = None;
        mailbox[59] = Black << 3 | Rook;
    } else if (move.b_s_castling()) {
        bitboard_operations::set_1(piece_bitboards[Black][King], 62);
        bitboard_operations::set_1(side_bitboards[Black], 62);
        bitboard_operations::set_1(all, 62);
        bitboard_operations::set_0(piece_bitboards[Black][Rook], 63);
        bitboard_operations::set_0(side_bitboards[Black], 63);
        bitboard_operations::set_0(all, 63);
        bitboard_operations::set_1(piece_bitboards[Black][Rook], 61);
        bitboard_operations::set_1(side_bitboards[Black], 61);
        bitboard_operations::set_1(all, 61);
        mailbox[62] = Black << 3 | King;
        mailbox[63] = 255;
        mailbox[61] = Black << 3 | Rook;
    }

    // Revoke castling rights
    if (move.piece_type() == King) {
        if (move.attacker_color() == White) {
            w_l_castling = false;
            w_s_castling = false;
        } else {
            b_l_castling = false;
            b_s_castling = false;
        }
    }
    if (move.piece_type() == Rook) {
        if (move.from() == 0)
            w_l_castling = false;
        if (move.from() == 7)
            w_s_castling = false;
        if (move.from() == 56)
            b_l_castling = false;
        if (move.from() == 63)
            b_s_castling = false;
    }
    // Rook captured
    if (move.to() != 255) {
        if (move.to() == 0)
            w_l_castling = false;
        if (move.to() == 7)
            w_s_castling = false;
        if (move.to() == 56)
            b_l_castling = false;
        if (move.to() == 63)
            b_s_castling = false;
    }

    // En passant square
    if (move.pawn_double_move()) {
        if (move.attacker_color() == White) {
            en_passant_square = move.from() + 8;
        } else {
            en_passant_square = move.from() - 8;
        }
    } else {
        en_passant_square = -1;
    }

    // Halfmove clock
    if (move.piece_type() == Pawn || move.second_type() != 255) {
        halfmove_clock = 0;
    } else {
        halfmove_clock++;
    }

    white_turn = !white_turn;
    current_hash = zobrist::ZobristHash(*this).hash;
    hashes.push_back(zobrist::ZobristHash(current_hash));
    move_history.push_back(move.to_string());
    num_of_moves += 0.5;
}

void chess::Board::make_move(const Move move, PositionState& state) {
    state.captured_type = move.second_type();
    state.captured_side = move.second_side();
    state.prev_en_passant = en_passant_square;
    state.prev_halfmove = halfmove_clock;
    state.prev_w_l_castling = w_l_castling;
    state.prev_w_s_castling = w_s_castling;
    state.prev_b_l_castling = b_l_castling;
    state.prev_b_s_castling = b_s_castling;
    state.prev_hash = current_hash;

    bitboard_operations::set_0(piece_bitboards[move.attacker_color()][move.piece_type()], move.from());
    bitboard_operations::set_0(side_bitboards[move.attacker_color()], move.from());
    bitboard_operations::set_0(all, move.from());

    uint8_t placed_type = move.piece_type();
    if (move.pawn_change_type() != 255) {
        placed_type = move.pawn_change_type();
    }

    if (move.second_type() == 255) {
        bitboard_operations::set_1(piece_bitboards[move.attacker_color()][placed_type], move.to());
        bitboard_operations::set_1(side_bitboards[move.attacker_color()], move.to());
        bitboard_operations::set_1(all, move.to());
    } else {
        bitboard_operations::set_0(piece_bitboards[move.second_side()][move.second_type()], move.to());
        bitboard_operations::set_0(side_bitboards[move.second_side()], move.to());
        bitboard_operations::set_1(piece_bitboards[move.attacker_color()][placed_type], move.to());
        bitboard_operations::set_1(side_bitboards[move.attacker_color()], move.to());
        bitboard_operations::set_1(all, move.to());
    }

    mailbox[move.from()] = 255;
    mailbox[move.to()] = move.attacker_color() << 3 | placed_type;

    if (move.en_passant()) {
        if (move.attacker_color() == White) {
            bitboard_operations::set_0(piece_bitboards[Black][Pawn], move.to() - 8);
            bitboard_operations::set_0(side_bitboards[Black], move.to() - 8);
            bitboard_operations::set_0(all, move.to() - 8);
            mailbox[move.to() - 8] = 255;
        } else {
            bitboard_operations::set_0(piece_bitboards[White][Pawn], move.to() + 8);
            bitboard_operations::set_0(side_bitboards[White], move.to() + 8);
            bitboard_operations::set_0(all, move.to() + 8);
            mailbox[move.to() + 8] = 255;
        }
    }

    if (move.w_l_castling()) {
        bitboard_operations::set_1(piece_bitboards[White][King], 2);
        bitboard_operations::set_1(side_bitboards[White], 2);
        bitboard_operations::set_1(all, 2);
        bitboard_operations::set_0(piece_bitboards[White][Rook], 0);
        bitboard_operations::set_0(side_bitboards[White], 0);
        bitboard_operations::set_0(all, 0);
        bitboard_operations::set_1(piece_bitboards[White][Rook], 3);
        bitboard_operations::set_1(side_bitboards[White], 3);
        bitboard_operations::set_1(all, 3);
        mailbox[2] = White << 3 | King;
        mailbox[0] = 255;
        mailbox[3] = White << 3 | Rook;
    } else if (move.w_s_castling()) {
        bitboard_operations::set_1(piece_bitboards[White][King], 6);
        bitboard_operations::set_1(side_bitboards[White], 6);
        bitboard_operations::set_1(all, 6);
        bitboard_operations::set_0(piece_bitboards[White][Rook], 7);
        bitboard_operations::set_0(side_bitboards[White], 7);
        bitboard_operations::set_0(all, 7);
        bitboard_operations::set_1(piece_bitboards[White][Rook], 5);
        bitboard_operations::set_1(side_bitboards[White], 5);
        bitboard_operations::set_1(all, 5);
        mailbox[6] = White << 3 | King;
        mailbox[7] = 255;
        mailbox[5] = White << 3 | Rook;
    } else if (move.b_l_castling()) {
        bitboard_operations::set_1(piece_bitboards[Black][King], 58);
        bitboard_operations::set_1(side_bitboards[Black], 58);
        bitboard_operations::set_1(all, 58);
        bitboard_operations::set_0(piece_bitboards[Black][Rook], 56);
        bitboard_operations::set_0(side_bitboards[Black], 56);
        bitboard_operations::set_0(all, 56);
        bitboard_operations::set_1(piece_bitboards[Black][Rook], 59);
        bitboard_operations::set_1(side_bitboards[Black], 59);
        bitboard_operations::set_1(all, 59);
        mailbox[58] = Black << 3 | King;
        mailbox[56] = 255;
        mailbox[59] = Black << 3 | Rook;
    } else if (move.b_s_castling()) {
        bitboard_operations::set_1(piece_bitboards[Black][King], 62);
        bitboard_operations::set_1(side_bitboards[Black], 62);
        bitboard_operations::set_1(all, 62);
        bitboard_operations::set_0(piece_bitboards[Black][Rook], 63);
        bitboard_operations::set_0(side_bitboards[Black], 63);
        bitboard_operations::set_0(all, 63);
        bitboard_operations::set_1(piece_bitboards[Black][Rook], 61);
        bitboard_operations::set_1(side_bitboards[Black], 61);
        bitboard_operations::set_1(all, 61);
        mailbox[62] = Black << 3 | King;
        mailbox[63] = 255;
        mailbox[61] = Black << 3 | Rook;
    }

    if (move.piece_type() == King) {
        if (move.attacker_color() == White) {
            w_l_castling = false;
            w_s_castling = false;
        } else {
            b_l_castling = false;
            b_s_castling = false;
        }
    }
    if (move.piece_type() == Rook) {
        if (move.from() == 0)
            w_l_castling = false;
        if (move.from() == 7)
            w_s_castling = false;
        if (move.from() == 56)
            b_l_castling = false;
        if (move.from() == 63)
            b_s_castling = false;
    }
    if (move.to() != 255) {
        if (move.to() == 0)
            w_l_castling = false;
        if (move.to() == 7)
            w_s_castling = false;
        if (move.to() == 56)
            b_l_castling = false;
        if (move.to() == 63)
            b_s_castling = false;
    }

    if (move.pawn_double_move()) {
        if (move.attacker_color() == White) {
            en_passant_square = move.from() + 8;
        } else {
            en_passant_square = move.from() - 8;
        }
    } else {
        en_passant_square = -1;
    }

    if (move.piece_type() == Pawn || move.second_type() != 255) {
        halfmove_clock = 0;
    } else {
        halfmove_clock++;
    }

    white_turn = !white_turn;
    num_of_moves += 0.5;

    current_hash ^= zobrist::BlackMove;
    current_hash ^= zobrist::Constants[move.from()][move.attacker_color()][move.piece_type()];
    current_hash ^= zobrist::Constants[move.to()][move.attacker_color()][placed_type];

    if (move.second_type() != 255) {
        current_hash ^= zobrist::Constants[move.to()][move.second_side()][move.second_type()];
    }

    if (move.en_passant()) {
        if (move.attacker_color() == White) {
            current_hash ^= zobrist::Constants[move.to() - 8][Black][Pawn];
        } else {
            current_hash ^= zobrist::Constants[move.to() + 8][White][Pawn];
        }
    }

    if (move.w_l_castling()) {
        current_hash ^= zobrist::Constants[0][White][Rook];
        current_hash ^= zobrist::Constants[3][White][Rook];
    } else if (move.w_s_castling()) {
        current_hash ^= zobrist::Constants[7][White][Rook];
        current_hash ^= zobrist::Constants[5][White][Rook];
    } else if (move.b_l_castling()) {
        current_hash ^= zobrist::Constants[56][Black][Rook];
        current_hash ^= zobrist::Constants[59][Black][Rook];
    } else if (move.b_s_castling()) {
        current_hash ^= zobrist::Constants[63][Black][Rook];
        current_hash ^= zobrist::Constants[61][Black][Rook];
    }

    if (state.prev_w_l_castling != w_l_castling)
        current_hash ^= zobrist::WhiteLongCastling;
    if (state.prev_w_s_castling != w_s_castling)
        current_hash ^= zobrist::WhiteShortCastling;
    if (state.prev_b_l_castling != b_l_castling)
        current_hash ^= zobrist::BlackLongCastling;
    if (state.prev_b_s_castling != b_s_castling)
        current_hash ^= zobrist::BlackShortCastling;

    if (state.prev_en_passant >= 0) {
        current_hash ^= zobrist::EnPassantFile[state.prev_en_passant % 8];
    }
    if (en_passant_square >= 0) {
        current_hash ^= zobrist::EnPassantFile[en_passant_square % 8];
    }
}

void chess::Board::unmake_move(const Move move, const PositionState& state) {
    white_turn = !white_turn;
    num_of_moves -= 0.5;
    current_hash = state.prev_hash;

    en_passant_square = state.prev_en_passant;
    halfmove_clock = state.prev_halfmove;
    w_l_castling = state.prev_w_l_castling;
    w_s_castling = state.prev_w_s_castling;
    b_l_castling = state.prev_b_l_castling;
    b_s_castling = state.prev_b_s_castling;

    uint8_t placed_type = move.piece_type();
    if (move.pawn_change_type() != 255) {
        placed_type = move.pawn_change_type();
    }

    if (move.w_l_castling()) {
        bitboard_operations::set_0(piece_bitboards[White][King], 2);
        bitboard_operations::set_0(side_bitboards[White], 2);
        bitboard_operations::set_0(all, 2);
        bitboard_operations::set_1(piece_bitboards[White][Rook], 0);
        bitboard_operations::set_1(side_bitboards[White], 0);
        bitboard_operations::set_1(all, 0);
        bitboard_operations::set_0(piece_bitboards[White][Rook], 3);
        bitboard_operations::set_0(side_bitboards[White], 3);
        bitboard_operations::set_0(all, 3);
        mailbox[4] = White << 3 | King;
        mailbox[0] = White << 3 | Rook;
        mailbox[2] = 255;
        mailbox[3] = 255;
    } else if (move.w_s_castling()) {
        bitboard_operations::set_0(piece_bitboards[White][King], 6);
        bitboard_operations::set_0(side_bitboards[White], 6);
        bitboard_operations::set_0(all, 6);
        bitboard_operations::set_1(piece_bitboards[White][Rook], 7);
        bitboard_operations::set_1(side_bitboards[White], 7);
        bitboard_operations::set_1(all, 7);
        bitboard_operations::set_0(piece_bitboards[White][Rook], 5);
        bitboard_operations::set_0(side_bitboards[White], 5);
        bitboard_operations::set_0(all, 5);
        mailbox[4] = White << 3 | King;
        mailbox[7] = White << 3 | Rook;
        mailbox[6] = 255;
        mailbox[5] = 255;
    } else if (move.b_l_castling()) {
        bitboard_operations::set_0(piece_bitboards[Black][King], 58);
        bitboard_operations::set_0(side_bitboards[Black], 58);
        bitboard_operations::set_0(all, 58);
        bitboard_operations::set_1(piece_bitboards[Black][Rook], 56);
        bitboard_operations::set_1(side_bitboards[Black], 56);
        bitboard_operations::set_1(all, 56);
        bitboard_operations::set_0(piece_bitboards[Black][Rook], 59);
        bitboard_operations::set_0(side_bitboards[Black], 59);
        bitboard_operations::set_0(all, 59);
        mailbox[60] = Black << 3 | King;
        mailbox[56] = Black << 3 | Rook;
        mailbox[58] = 255;
        mailbox[59] = 255;
    } else if (move.b_s_castling()) {
        bitboard_operations::set_0(piece_bitboards[Black][King], 62);
        bitboard_operations::set_0(side_bitboards[Black], 62);
        bitboard_operations::set_0(all, 62);
        bitboard_operations::set_1(piece_bitboards[Black][Rook], 63);
        bitboard_operations::set_1(side_bitboards[Black], 63);
        bitboard_operations::set_1(all, 63);
        bitboard_operations::set_0(piece_bitboards[Black][Rook], 61);
        bitboard_operations::set_0(side_bitboards[Black], 61);
        bitboard_operations::set_0(all, 61);
        mailbox[60] = Black << 3 | King;
        mailbox[63] = Black << 3 | Rook;
        mailbox[62] = 255;
        mailbox[61] = 255;
    }

    bitboard_operations::set_0(piece_bitboards[move.attacker_color()][placed_type], move.to());
    bitboard_operations::set_0(side_bitboards[move.attacker_color()], move.to());
    bitboard_operations::set_0(all, move.to());

    bitboard_operations::set_1(piece_bitboards[move.attacker_color()][move.piece_type()], move.from());
    bitboard_operations::set_1(side_bitboards[move.attacker_color()], move.from());
    bitboard_operations::set_1(all, move.from());

    mailbox[move.from()] = move.attacker_color() << 3 | move.piece_type();
    mailbox[move.to()] = 255;

    if (state.captured_type != 255) {
        bitboard_operations::set_1(piece_bitboards[state.captured_side][state.captured_type], move.to());
        bitboard_operations::set_1(side_bitboards[state.captured_side], move.to());
        bitboard_operations::set_1(all, move.to());
        mailbox[move.to()] = state.captured_side << 3 | state.captured_type;
    }

    if (move.en_passant()) {
        if (move.attacker_color() == White) {
            bitboard_operations::set_1(piece_bitboards[Black][Pawn], move.to() - 8);
            bitboard_operations::set_1(side_bitboards[Black], move.to() - 8);
            bitboard_operations::set_1(all, move.to() - 8);
            mailbox[move.to() - 8] = Black << 3 | Pawn;
        } else {
            bitboard_operations::set_1(piece_bitboards[White][Pawn], move.to() + 8);
            bitboard_operations::set_1(side_bitboards[White], move.to() + 8);
            bitboard_operations::set_1(all, move.to() + 8);
            mailbox[move.to() + 8] = White << 3 | Pawn;
        }
    }
}

void chess::Board::move(const std::string& move) {
    for (int i = 0; i < legal_moves.size(); i++) {
        if (move == legal_moves.moves[i].to_string()) {
            this->move(legal_moves.moves[i]);
            return;
        }
    }
    throw std::invalid_argument("Invalid move");
}

std::ostream& chess::operator<<(std::ostream& ostream, const Move move) {
    ostream << "First: " << static_cast<int>(move.from()) << std::endl;
    ostream << "First side: " << static_cast<int>(move.attacker_color()) << std::endl;
    ostream << "First type: " << static_cast<int>(move.piece_type()) << std::endl;
    ostream << "Second: " << static_cast<int>(move.to()) << std::endl;
    ostream << "Second side: " << static_cast<int>(move.second_side()) << std::endl;
    ostream << "Second type: " << static_cast<int>(move.second_type()) << std::endl;
    ostream << "W long castling: " << move.w_l_castling() << std::endl;
    ostream << "W short castling: " << move.w_s_castling() << std::endl;
    ostream << "B long castling: " << move.b_l_castling() << std::endl;
    ostream << "B short castling: " << move.b_s_castling() << std::endl;
    ostream << "Pawn double move: " << move.pawn_double_move() << std::endl;
    ostream << "En passant: " << move.en_passant() << std::endl;
    ostream << "Pawn change type: " << static_cast<int>(move.pawn_change_type()) << std::endl;

    return ostream;
}

std::string chess::Move::to_string() const {
    std::string result = move_to_chess_notation(from(), to());
    if (pawn_change_type() != 255) {
        constexpr std::array promo_chars = {'\0', 'r', 'n', 'b', 'q', '\0'};
        result += promo_chars[pawn_change_type()];
    }
    return result;
}

void chess::Board::make_null_move(NullMoveState& state) {
    state.prev_en_passant = en_passant_square;
    state.prev_hash = current_hash;

    white_turn = !white_turn;
    current_hash ^= zobrist::BlackMove;

    if (en_passant_square >= 0) {
        current_hash ^= zobrist::EnPassantFile[en_passant_square % 8];
        en_passant_square = -1;
    }
}

void chess::Board::unmake_null_move(const NullMoveState& state) {
    white_turn = !white_turn;
    en_passant_square = state.prev_en_passant;
    current_hash = state.prev_hash;
}