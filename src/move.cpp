#include "headers/move.hpp"
#include "headers/board.hpp"
#include "headers/constants.hpp"
#include "headers/bitboard_operations.hpp"
#include "headers/notations.hpp"

#include <iostream>


chess::Move::Move(){
    first = 0;
    first_side = 0;
    first_type = 0;

    second = 0;
    second_side = 255;
    second_type = 255;

    w_l_castling = false;
    w_s_castling = false;
    b_l_castling = false;
    b_s_castling = false;

    pawn_double_move = false;
    en_passant = false;
    pawn_change_type = 255;
}

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

    this->first = first;
    this->first_side = first_side;
    this->first_type = first_type;

    this->second = second;
    this->second_side = second_side;
    this->second_type = second_type;

    this->w_l_castling = w_l_castling;
    this->w_s_castling = w_s_castling;
    this->b_l_castling = b_l_castling;
    this->b_s_castling = b_s_castling;

    this->pawn_double_move = pawn_double_move;
    this->en_passant = en_passant;
    this->pawn_change_type = pawn_change_type;
}

void chess::Board::move(chess::Move move){
    bitboard_operations::set_0(piece_bitboards[move.first_side][move.first_type], move.first);
    bitboard_operations::set_0(side_bitboards[move.first_side], move.first);
    bitboard_operations::set_0(all, move.first);
    if (move.second_type == 255){
        bitboard_operations::set_1(piece_bitboards[move.first_side][move.first_type], move.second);
        bitboard_operations::set_1(side_bitboards[move.first_side], move.second);
        bitboard_operations::set_1(all, move.second);
    }
    else {
        bitboard_operations::set_0(piece_bitboards[move.second_side][move.second_type], move.second);
        bitboard_operations::set_0(side_bitboards[move.second_side], move.second);
        bitboard_operations::set_0(all, move.second);
        bitboard_operations::set_1(piece_bitboards[move.first_side][move.first_type], move.second);
        bitboard_operations::set_1(side_bitboards[move.first_side], move.second);
        bitboard_operations::set_1(all, move.second);

    }

    if (move.en_passant){
        if (move.first_side == chess::White){
            bitboard_operations::set_0(piece_bitboards[chess::Black][chess::Pawn], move.second - 8);
            bitboard_operations::set_0(side_bitboards[chess::Black], move.second - 8);
            bitboard_operations::set_0(all, move.second - 8);
        }
        else {
            bitboard_operations::set_0(piece_bitboards[chess::White][chess::Pawn], move.second + 8);
            bitboard_operations::set_0(side_bitboards[chess::White], move.second + 8);
            bitboard_operations::set_0(all, move.second + 8);
        }
    }

    if (move.w_l_castling){
        bitboard_operations::set_1(piece_bitboards[chess::White][chess::King], 2);
        bitboard_operations::set_1(side_bitboards[chess::White], 2);
        bitboard_operations::set_1(all, 2);
        bitboard_operations::set_0(piece_bitboards[chess::White][chess::Rook], 0);
        bitboard_operations::set_0(side_bitboards[chess::White], 0);
        bitboard_operations::set_0(all, 0);
        bitboard_operations::set_1(piece_bitboards[chess::White][chess::Rook], 3);
        bitboard_operations::set_1(side_bitboards[chess::White], 3);
        bitboard_operations::set_1(all, 3);
        white_castling = false;
    }
    else if (move.w_s_castling){
        bitboard_operations::set_1(piece_bitboards[chess::White][chess::King], 6);
        bitboard_operations::set_1(side_bitboards[chess::White], 6);
        bitboard_operations::set_1(all, 6);
        bitboard_operations::set_0(piece_bitboards[chess::White][chess::Rook], 7);
        bitboard_operations::set_0(side_bitboards[chess::White], 7);
        bitboard_operations::set_0(all, 7);
        bitboard_operations::set_1(piece_bitboards[chess::White][chess::Rook], 5);
        bitboard_operations::set_1(side_bitboards[chess::White], 5);
        bitboard_operations::set_1(all, 5);
        white_castling = false;
    }
    else if (move.b_l_castling){
        bitboard_operations::set_1(piece_bitboards[chess::Black][chess::King], 58);
        bitboard_operations::set_1(side_bitboards[chess::Black], 58);
        bitboard_operations::set_1(all, 58);
        bitboard_operations::set_0(piece_bitboards[chess::Black][chess::Rook], 56);
        bitboard_operations::set_0(side_bitboards[chess::Black], 56);
        bitboard_operations::set_0(all, 56);
        bitboard_operations::set_1(piece_bitboards[chess::Black][chess::Rook], 59);
        bitboard_operations::set_1(side_bitboards[chess::Black], 59);
        bitboard_operations::set_1(all, 59);
        black_castling = false;
    }
    else if (move.b_s_castling){
        bitboard_operations::set_1(piece_bitboards[chess::Black][chess::King], 62);
        bitboard_operations::set_1(side_bitboards[chess::Black], 62);
        bitboard_operations::set_1(all, 62);
        bitboard_operations::set_0(piece_bitboards[chess::Black][chess::Rook], 63);
        bitboard_operations::set_0(side_bitboards[chess::Black], 63);
        bitboard_operations::set_0(all, 63);
        bitboard_operations::set_1(piece_bitboards[chess::Black][chess::Rook], 61);
        bitboard_operations::set_1(side_bitboards[chess::Black], 61);
        bitboard_operations::set_1(all, 61);
        black_castling = false;
    }

    white_turn = !white_turn;
    if (_hashes.size() > 0){
        zobrist::ZobristHash last_hash = _hashes.back();
        last_hash = last_hash ^ zobrist::BlackMove;
        last_hash = last_hash ^ zobrist::Constants[move.first][move.first_side][move.first_type];
        if (move.second_type == 255){
            last_hash = last_hash ^ zobrist::Constants[move.second][move.first_side][move.first_type];
        }
        else {
            last_hash = last_hash ^ zobrist::Constants[move.second][move.second_side][move.second_type];
        }
        _hashes.push_back(last_hash);
    }
    else {
        _hashes.push_back(zobrist::ZobristHash(*this));
    }

    num_of_moves += 0.5;
}


std::ostream& chess::operator<<(std::ostream &ostream, chess::Move move) {
    ostream << "First: " << (int)move.first << std::endl;
    ostream << "First side: " << (int)move.first_side << std::endl;
    ostream << "First type: " << (int)move.first_type << std::endl;
    ostream << "Second: " << (int)move.second << std::endl;
    ostream << "Second side: " << (int)move.second_side << std::endl;
    ostream << "Second type: " << (int)move.second_type << std::endl;
    ostream << "W long castling: " << move.w_l_castling << std::endl;
    ostream << "W short castling: " << move.w_s_castling << std::endl;
    ostream << "B long castling: " << move.b_l_castling << std::endl;
    ostream << "B short castling: " << move.b_s_castling << std::endl;
    ostream << "Pawn double move: " << move.pawn_double_move << std::endl;
    ostream << "En passant: " << move.en_passant << std::endl;
    ostream << "Pawn change type: " << (int)move.pawn_change_type << std::endl;

    return ostream;
}

std::string chess::Move::to_string() {
    return move_to_chess_notation(first, second);
}