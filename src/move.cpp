#include "headers/move.hpp"
#include "headers/board.hpp"
#include "headers/constants.hpp"
#include "headers/bitboard_operations.hpp"
#include "headers/notations.hpp"

#include <iostream>


chess::Move::Move(uint8_t first,
           uint8_t first_side,
           uint8_t first_type,
           uint8_t second,
           uint8_t second_side,
           uint8_t second_type,
           bool w_l_castling,
           bool w_s_castling,
           bool b_l_castling,
           bool b_s_castling,
           bool pawn_double_move,
           bool en_passant,
           uint8_t pawn_change_type) {

    MoveType mt = MT_NORMAL;
    if (w_l_castling) mt = MT_W_L_CASTLE;
    else if (w_s_castling) mt = MT_W_S_CASTLE;
    else if (b_l_castling) mt = MT_B_L_CASTLE;
    else if (b_s_castling) mt = MT_B_S_CASTLE;
    else if (en_passant) mt = MT_EN_PASSANT;
    else if (pawn_double_move) mt = MT_PAWN_DOUBLE;

    uint8_t cap_type = (second_type == 255) ? 7 : second_type;
    uint8_t cap_color = (second_side == 255) ? 0 : second_side;
    uint8_t promo = (pawn_change_type == 255) ? 7 : pawn_change_type;

    data = (first & 0x3F)
         | ((second & 0x3F) << 6)
         | ((mt & 0x7) << 12)
         | ((first_type & 0x7) << 15)
         | ((cap_type & 0x7) << 18)
         | ((first_side & 0x1) << 21)
         | ((cap_color & 0x1) << 22)
         | ((promo & 0x7) << 23);
}

void chess::Board::move(chess::Move move){
    if (move.second_type() == King){
        std::cout << "KING EATING" << std::endl;
        std::cout << *this << std::endl;
        for (auto move : get_legal_moves()) {
            std::cout << move.to_string() << std::endl;
        }


    }
    bitboard_operations::set_0(piece_bitboards[move.attacker_color()][move.piece_type()], move.from());
    bitboard_operations::set_0(side_bitboards[move.attacker_color()], move.from());
    bitboard_operations::set_0(all, move.from());

    uint8_t placed_type = move.piece_type();
    if (move.pawn_change_type() != 255) {
        placed_type = move.pawn_change_type();
    }


    if (move.second_type() == 255){
        bitboard_operations::set_1(piece_bitboards[move.attacker_color()][placed_type], move.to());
        bitboard_operations::set_1(side_bitboards[move.attacker_color()], move.to());
        bitboard_operations::set_1(all, move.to());
    }
    else {
        bitboard_operations::set_0(piece_bitboards[move.second_side()][move.second_type()], move.to());
        bitboard_operations::set_0(side_bitboards[move.second_side()], move.to());
        bitboard_operations::set_0(all, move.to());
        bitboard_operations::set_1(piece_bitboards[move.attacker_color()][placed_type], move.to());
        bitboard_operations::set_1(side_bitboards[move.attacker_color()], move.to());
        bitboard_operations::set_1(all, move.to());
    }

    mailbox[move.from()] = 255;
    mailbox[move.to()] = (move.attacker_color() << 3) | placed_type;

    if (move.en_passant()){
        if (move.attacker_color() == chess::White){
            bitboard_operations::set_0(piece_bitboards[chess::Black][chess::Pawn], move.to() - 8);
            bitboard_operations::set_0(side_bitboards[chess::Black], move.to() - 8);
            bitboard_operations::set_0(all, move.to() - 8);
            mailbox[move.to() - 8] = 255;
        }
        else {
            bitboard_operations::set_0(piece_bitboards[chess::White][chess::Pawn], move.to() + 8);
            bitboard_operations::set_0(side_bitboards[chess::White], move.to() + 8);
            bitboard_operations::set_0(all, move.to() + 8);
            mailbox[move.to() + 8] = 255;
        }
    }

    if (move.w_l_castling()){
        bitboard_operations::set_1(piece_bitboards[chess::White][chess::King], 2);
        bitboard_operations::set_1(side_bitboards[chess::White], 2);
        bitboard_operations::set_1(all, 2);
        bitboard_operations::set_0(piece_bitboards[chess::White][chess::Rook], 0);
        bitboard_operations::set_0(side_bitboards[chess::White], 0);
        bitboard_operations::set_0(all, 0);
        bitboard_operations::set_1(piece_bitboards[chess::White][chess::Rook], 3);
        bitboard_operations::set_1(side_bitboards[chess::White], 3);
        bitboard_operations::set_1(all, 3);
        mailbox[2] = (chess::White << 3) | chess::King;
        mailbox[0] = 255;
        mailbox[3] = (chess::White << 3) | chess::Rook;
    }
    else if (move.w_s_castling()){
        bitboard_operations::set_1(piece_bitboards[chess::White][chess::King], 6);
        bitboard_operations::set_1(side_bitboards[chess::White], 6);
        bitboard_operations::set_1(all, 6);
        bitboard_operations::set_0(piece_bitboards[chess::White][chess::Rook], 7);
        bitboard_operations::set_0(side_bitboards[chess::White], 7);
        bitboard_operations::set_0(all, 7);
        bitboard_operations::set_1(piece_bitboards[chess::White][chess::Rook], 5);
        bitboard_operations::set_1(side_bitboards[chess::White], 5);
        bitboard_operations::set_1(all, 5);
        mailbox[6] = (chess::White << 3) | chess::King;
        mailbox[7] = 255;
        mailbox[5] = (chess::White << 3) | chess::Rook;
    }
    else if (move.b_l_castling()){
        bitboard_operations::set_1(piece_bitboards[chess::Black][chess::King], 58);
        bitboard_operations::set_1(side_bitboards[chess::Black], 58);
        bitboard_operations::set_1(all, 58);
        bitboard_operations::set_0(piece_bitboards[chess::Black][chess::Rook], 56);
        bitboard_operations::set_0(side_bitboards[chess::Black], 56);
        bitboard_operations::set_0(all, 56);
        bitboard_operations::set_1(piece_bitboards[chess::Black][chess::Rook], 59);
        bitboard_operations::set_1(side_bitboards[chess::Black], 59);
        bitboard_operations::set_1(all, 59);
        mailbox[58] = (chess::Black << 3) | chess::King;
        mailbox[56] = 255;
        mailbox[59] = (chess::Black << 3) | chess::Rook;
    }
    else if (move.b_s_castling()){
        bitboard_operations::set_1(piece_bitboards[chess::Black][chess::King], 62);
        bitboard_operations::set_1(side_bitboards[chess::Black], 62);
        bitboard_operations::set_1(all, 62);
        bitboard_operations::set_0(piece_bitboards[chess::Black][chess::Rook], 63);
        bitboard_operations::set_0(side_bitboards[chess::Black], 63);
        bitboard_operations::set_0(all, 63);
        bitboard_operations::set_1(piece_bitboards[chess::Black][chess::Rook], 61);
        bitboard_operations::set_1(side_bitboards[chess::Black], 61);
        bitboard_operations::set_1(all, 61);
        mailbox[62] = (chess::Black << 3) | chess::King;
        mailbox[63] = 255;
        mailbox[61] = (chess::Black << 3) | chess::Rook;
    }

    // Revoke castling rights
    if (move.piece_type() == chess::King) {
        if (move.attacker_color() == chess::White) {
            w_l_castling = false;
            w_s_castling = false;
        } else {
            b_l_castling = false;
            b_s_castling = false;
        }
    }
    if (move.piece_type() == chess::Rook) {
        if (move.from() == 0) w_l_castling = false;
        if (move.from() == 7) w_s_castling = false;
        if (move.from() == 56) b_l_castling = false;
        if (move.from() == 63) b_s_castling = false;
    }
    // Rook captured
    if (move.to() != 255) {
        if (move.to() == 0) w_l_castling = false;
        if (move.to() == 7) w_s_castling = false;
        if (move.to() == 56) b_l_castling = false;
        if (move.to() == 63) b_s_castling = false;
    }

    // En passant square
    if (move.pawn_double_move()) {
        if (move.attacker_color() == chess::White) {
            en_passant_square = move.from() + 8;
        } else {
            en_passant_square = move.from() - 8;
        }
    } else {
        en_passant_square = -1;
    }

    // Halfmove clock
    if (move.piece_type() == chess::Pawn || move.second_type() != 255) {
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

void chess::Board::make_move(chess::Move move, chess::PositionState& state) {
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
    mailbox[move.to()] = (move.attacker_color() << 3) | placed_type;

    if (move.en_passant()) {
        if (move.attacker_color() == chess::White) {
            bitboard_operations::set_0(piece_bitboards[chess::Black][chess::Pawn], move.to() - 8);
            bitboard_operations::set_0(side_bitboards[chess::Black], move.to() - 8);
            bitboard_operations::set_0(all, move.to() - 8);
            mailbox[move.to() - 8] = 255;
        } else {
            bitboard_operations::set_0(piece_bitboards[chess::White][chess::Pawn], move.to() + 8);
            bitboard_operations::set_0(side_bitboards[chess::White], move.to() + 8);
            bitboard_operations::set_0(all, move.to() + 8);
            mailbox[move.to() + 8] = 255;
        }
    }

    if (move.w_l_castling()) {
        bitboard_operations::set_1(piece_bitboards[chess::White][chess::King], 2);
        bitboard_operations::set_1(side_bitboards[chess::White], 2);
        bitboard_operations::set_1(all, 2);
        bitboard_operations::set_0(piece_bitboards[chess::White][chess::Rook], 0);
        bitboard_operations::set_0(side_bitboards[chess::White], 0);
        bitboard_operations::set_0(all, 0);
        bitboard_operations::set_1(piece_bitboards[chess::White][chess::Rook], 3);
        bitboard_operations::set_1(side_bitboards[chess::White], 3);
        bitboard_operations::set_1(all, 3);
        mailbox[2] = (chess::White << 3) | chess::King;
        mailbox[0] = 255;
        mailbox[3] = (chess::White << 3) | chess::Rook;
    } else if (move.w_s_castling()) {
        bitboard_operations::set_1(piece_bitboards[chess::White][chess::King], 6);
        bitboard_operations::set_1(side_bitboards[chess::White], 6);
        bitboard_operations::set_1(all, 6);
        bitboard_operations::set_0(piece_bitboards[chess::White][chess::Rook], 7);
        bitboard_operations::set_0(side_bitboards[chess::White], 7);
        bitboard_operations::set_0(all, 7);
        bitboard_operations::set_1(piece_bitboards[chess::White][chess::Rook], 5);
        bitboard_operations::set_1(side_bitboards[chess::White], 5);
        bitboard_operations::set_1(all, 5);
        mailbox[6] = (chess::White << 3) | chess::King;
        mailbox[7] = 255;
        mailbox[5] = (chess::White << 3) | chess::Rook;
    } else if (move.b_l_castling()) {
        bitboard_operations::set_1(piece_bitboards[chess::Black][chess::King], 58);
        bitboard_operations::set_1(side_bitboards[chess::Black], 58);
        bitboard_operations::set_1(all, 58);
        bitboard_operations::set_0(piece_bitboards[chess::Black][chess::Rook], 56);
        bitboard_operations::set_0(side_bitboards[chess::Black], 56);
        bitboard_operations::set_0(all, 56);
        bitboard_operations::set_1(piece_bitboards[chess::Black][chess::Rook], 59);
        bitboard_operations::set_1(side_bitboards[chess::Black], 59);
        bitboard_operations::set_1(all, 59);
        mailbox[58] = (chess::Black << 3) | chess::King;
        mailbox[56] = 255;
        mailbox[59] = (chess::Black << 3) | chess::Rook;
    } else if (move.b_s_castling()) {
        bitboard_operations::set_1(piece_bitboards[chess::Black][chess::King], 62);
        bitboard_operations::set_1(side_bitboards[chess::Black], 62);
        bitboard_operations::set_1(all, 62);
        bitboard_operations::set_0(piece_bitboards[chess::Black][chess::Rook], 63);
        bitboard_operations::set_0(side_bitboards[chess::Black], 63);
        bitboard_operations::set_0(all, 63);
        bitboard_operations::set_1(piece_bitboards[chess::Black][chess::Rook], 61);
        bitboard_operations::set_1(side_bitboards[chess::Black], 61);
        bitboard_operations::set_1(all, 61);
        mailbox[62] = (chess::Black << 3) | chess::King;
        mailbox[63] = 255;
        mailbox[61] = (chess::Black << 3) | chess::Rook;
    }

    if (move.piece_type() == chess::King) {
        if (move.attacker_color() == chess::White) {
            w_l_castling = false;
            w_s_castling = false;
        } else {
            b_l_castling = false;
            b_s_castling = false;
        }
    }
    if (move.piece_type() == chess::Rook) {
        if (move.from() == 0) w_l_castling = false;
        if (move.from() == 7) w_s_castling = false;
        if (move.from() == 56) b_l_castling = false;
        if (move.from() == 63) b_s_castling = false;
    }
    if (move.to() != 255) {
        if (move.to() == 0) w_l_castling = false;
        if (move.to() == 7) w_s_castling = false;
        if (move.to() == 56) b_l_castling = false;
        if (move.to() == 63) b_s_castling = false;
    }

    if (move.pawn_double_move()) {
        if (move.attacker_color() == chess::White) {
            en_passant_square = move.from() + 8;
        } else {
            en_passant_square = move.from() - 8;
        }
    } else {
        en_passant_square = -1;
    }

    if (move.piece_type() == chess::Pawn || move.second_type() != 255) {
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

    if (state.prev_w_l_castling != w_l_castling) current_hash ^= zobrist::WhiteLongCastling;
    if (state.prev_w_s_castling != w_s_castling) current_hash ^= zobrist::WhiteShortCastling;
    if (state.prev_b_l_castling != b_l_castling) current_hash ^= zobrist::BlackLongCastling;
    if (state.prev_b_s_castling != b_s_castling) current_hash ^= zobrist::BlackShortCastling;

    if (state.prev_en_passant >= 0) {
        current_hash ^= zobrist::EnPassantFile[state.prev_en_passant % 8];
    }
    if (en_passant_square >= 0) {
        current_hash ^= zobrist::EnPassantFile[en_passant_square % 8];
    }
}

void chess::Board::unmake_move(chess::Move move, const chess::PositionState& state) {
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
        bitboard_operations::set_0(piece_bitboards[chess::White][chess::King], 2);
        bitboard_operations::set_0(side_bitboards[chess::White], 2);
        bitboard_operations::set_0(all, 2);
        bitboard_operations::set_1(piece_bitboards[chess::White][chess::Rook], 0);
        bitboard_operations::set_1(side_bitboards[chess::White], 0);
        bitboard_operations::set_1(all, 0);
        bitboard_operations::set_0(piece_bitboards[chess::White][chess::Rook], 3);
        bitboard_operations::set_0(side_bitboards[chess::White], 3);
        bitboard_operations::set_0(all, 3);
        mailbox[4] = (chess::White << 3) | chess::King;
        mailbox[0] = (chess::White << 3) | chess::Rook;
        mailbox[2] = 255;
        mailbox[3] = 255;
    } else if (move.w_s_castling()) {
        bitboard_operations::set_0(piece_bitboards[chess::White][chess::King], 6);
        bitboard_operations::set_0(side_bitboards[chess::White], 6);
        bitboard_operations::set_0(all, 6);
        bitboard_operations::set_1(piece_bitboards[chess::White][chess::Rook], 7);
        bitboard_operations::set_1(side_bitboards[chess::White], 7);
        bitboard_operations::set_1(all, 7);
        bitboard_operations::set_0(piece_bitboards[chess::White][chess::Rook], 5);
        bitboard_operations::set_0(side_bitboards[chess::White], 5);
        bitboard_operations::set_0(all, 5);
        mailbox[4] = (chess::White << 3) | chess::King;
        mailbox[7] = (chess::White << 3) | chess::Rook;
        mailbox[6] = 255;
        mailbox[5] = 255;
    } else if (move.b_l_castling()) {
        bitboard_operations::set_0(piece_bitboards[chess::Black][chess::King], 58);
        bitboard_operations::set_0(side_bitboards[chess::Black], 58);
        bitboard_operations::set_0(all, 58);
        bitboard_operations::set_1(piece_bitboards[chess::Black][chess::Rook], 56);
        bitboard_operations::set_1(side_bitboards[chess::Black], 56);
        bitboard_operations::set_1(all, 56);
        bitboard_operations::set_0(piece_bitboards[chess::Black][chess::Rook], 59);
        bitboard_operations::set_0(side_bitboards[chess::Black], 59);
        bitboard_operations::set_0(all, 59);
        mailbox[60] = (chess::Black << 3) | chess::King;
        mailbox[56] = (chess::Black << 3) | chess::Rook;
        mailbox[58] = 255;
        mailbox[59] = 255;
    } else if (move.b_s_castling()) {
        bitboard_operations::set_0(piece_bitboards[chess::Black][chess::King], 62);
        bitboard_operations::set_0(side_bitboards[chess::Black], 62);
        bitboard_operations::set_0(all, 62);
        bitboard_operations::set_1(piece_bitboards[chess::Black][chess::Rook], 63);
        bitboard_operations::set_1(side_bitboards[chess::Black], 63);
        bitboard_operations::set_1(all, 63);
        bitboard_operations::set_0(piece_bitboards[chess::Black][chess::Rook], 61);
        bitboard_operations::set_0(side_bitboards[chess::Black], 61);
        bitboard_operations::set_0(all, 61);
        mailbox[60] = (chess::Black << 3) | chess::King;
        mailbox[63] = (chess::Black << 3) | chess::Rook;
        mailbox[62] = 255;
        mailbox[61] = 255;
    }

    bitboard_operations::set_0(piece_bitboards[move.attacker_color()][placed_type], move.to());
    bitboard_operations::set_0(side_bitboards[move.attacker_color()], move.to());
    bitboard_operations::set_0(all, move.to());

    bitboard_operations::set_1(piece_bitboards[move.attacker_color()][move.piece_type()], move.from());
    bitboard_operations::set_1(side_bitboards[move.attacker_color()], move.from());
    bitboard_operations::set_1(all, move.from());
    
    mailbox[move.from()] = (move.attacker_color() << 3) | move.piece_type();
    mailbox[move.to()] = 255;

    if (state.captured_type != 255) {
        bitboard_operations::set_1(piece_bitboards[state.captured_side][state.captured_type], move.to());
        bitboard_operations::set_1(side_bitboards[state.captured_side], move.to());
        bitboard_operations::set_1(all, move.to());
        mailbox[move.to()] = (state.captured_side << 3) | state.captured_type;
    }

    if (move.en_passant()) {
        if (move.attacker_color() == chess::White) {
            bitboard_operations::set_1(piece_bitboards[chess::Black][chess::Pawn], move.to() - 8);
            bitboard_operations::set_1(side_bitboards[chess::Black], move.to() - 8);
            bitboard_operations::set_1(all, move.to() - 8);
            mailbox[move.to() - 8] = (chess::Black << 3) | chess::Pawn;
        } else {
            bitboard_operations::set_1(piece_bitboards[chess::White][chess::Pawn], move.to() + 8);
            bitboard_operations::set_1(side_bitboards[chess::White], move.to() + 8);
            bitboard_operations::set_1(all, move.to() + 8);
            mailbox[move.to() + 8] = (chess::White << 3) | chess::Pawn;
        }
    }
}

void chess::Board::move(std::string move){
    for (int i = 0; i < legal_moves.size(); i++){
        if (move == legal_moves.moves[i].to_string()){
            this->move(legal_moves.moves[i]);
            return;
        }
    }
    throw std::invalid_argument("Invalid move");
}


std::ostream& chess::operator<<(std::ostream &ostream, chess::Move move) {
    ostream << "First: " << (int)move.from() << std::endl;
    ostream << "First side: " << (int)move.attacker_color() << std::endl;
    ostream << "First type: " << (int)move.piece_type() << std::endl;
    ostream << "Second: " << (int)move.to() << std::endl;
    ostream << "Second side: " << (int)move.second_side() << std::endl;
    ostream << "Second type: " << (int)move.second_type() << std::endl;
    ostream << "W long castling: " << move.w_l_castling() << std::endl;
    ostream << "W short castling: " << move.w_s_castling() << std::endl;
    ostream << "B long castling: " << move.b_l_castling() << std::endl;
    ostream << "B short castling: " << move.b_s_castling() << std::endl;
    ostream << "Pawn double move: " << move.pawn_double_move() << std::endl;
    ostream << "En passant: " << move.en_passant() << std::endl;
    ostream << "Pawn change type: " << (int)move.pawn_change_type() << std::endl;

    return ostream;
}

std::string chess::Move::to_string() {
    std::string result = move_to_chess_notation(from(), to());
    if (pawn_change_type() != 255) {
        const char promo_chars[] = {'\0', 'r', 'n', 'b', 'q', '\0'};
        result += promo_chars[pawn_change_type()];
    }
    return result;
}
