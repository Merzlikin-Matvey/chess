#include <iostream>

#include "chess-engine.hpp"
#include "headers/C functions/magic_numbers.h"
#include <iostream>
#include <omp.h>
#include <chrono>

using namespace std;
using namespace chess;

void test(){
    Board board = Board("4r3/4q3/8/6b1/4P3/p1rPKR1p/4P3/8");

    long long n = 1000;

    auto start = chrono::high_resolution_clock::now();
    for (long long i = 0; i < n; i++) {
        auto mask = chess::magic_numbers::rook_magic_numbers[i % 64];
    }
    auto end = chrono::high_resolution_clock::now();

    cout << "Time per iteration: " << chrono::duration_cast<chrono::nanoseconds>(end - start).count() / n << "ns" << endl;
}


bool static constexpr _get_bit(int num, int bit) {
    return (num & (1 << bit)) != 0;
}
std::array<std::array<Bitboard, 1024>, 64> generate_rook_masks(){

    std::array<std::array<Bitboard, 1024>, 64> masks{};
    std::array<Bitboard, 64> magic_numbers = chess::magic_numbers::rook_magic_numbers;
    Bitboard magic;

    // Вертикаль
    for (int square = 0; square < 1; square++){
        uint8_t i = 0;
        magic = magic_numbers[square];
        while (true){

            if (_get_bit(i, square / 8) or (_get_bit(i, 0)) or (_get_bit(i, 7))){
                i++;
                continue;
            }

            Bitboard vertical_board = 0;
            for (uint8_t bits = 0; bits < 8; bits++){
                if (_get_bit(i, bits)){
                    bitboard_operations::set_1(vertical_board, square % 8 + bits * 8);
                }
            }

            uint8_t j = 0;
            while (true){
                if (_get_bit(j, square % 8) or (_get_bit(j, 0)) or (_get_bit(j, 7))){
                    j++;
                    continue;
                }
                Bitboard board = vertical_board;
                for (uint8_t bits = 0; bits < 8; bits++){
                    if (_get_bit(j, bits)){
                        bitboard_operations::set_1(board, (square / 8) * 8 + bits);
                    }
                }
                int hash = (board * magic) >> 54;
                Bitboard mask = 0;
                bitboard_operations::set_1(mask, square);


                masks[square][hash] = mask;




                if (j == 255){
                    break;
                }
                j++;
            }

            if (i == 255){
                break;
            }
            i++;
        }
    }
    return masks;
}


int main() {
    auto masks = generate_rook_masks();
    for (int i = 0; i < 10; i++){
        print_bitboard(masks[0][i]);
        cout << endl;
    }




}