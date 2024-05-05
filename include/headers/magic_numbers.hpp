#pragma once

#include <cstdint>
#include <array>
#include <iostream>

typedef uint64_t Bitboard;


extern "C" {
    #include "C functions/magic_numbers.h"
}

namespace chess::magic_numbers{
    Bitboard generate_rook_magic_number(uint8_t square) {
        return ::_generate_rook_magic_number(square);
    }

    std::array<Bitboard, 64> generate_rook_magic_numbers() {
        std::array<Bitboard, 64> magic_numbers{};
        for (uint8_t square = 0; square < 64; square++) {
            magic_numbers[square] = generate_rook_magic_number(square);
        }
        return magic_numbers;
    }

    void fancy_print_rook_magic_numbers() {
        std::array<Bitboard, 64> magic_numbers = generate_rook_magic_numbers();
        for (uint8_t square = 0; square < 64; square += 4) {
            std::cout << "0x" << std::hex << magic_numbers[square] << ", "
                      << "0x"<< std::hex << magic_numbers[square + 1] << ", "
                      << "0x"<< std::hex << magic_numbers[square + 2] << ", "
                      << "0x"<< std::hex << magic_numbers[square + 3] << "," << std::endl;
        }
    }


    Bitboard generate_bishop_magic_number(uint8_t square) {
        return ::_generate_bishop_magic_number(square);
    }

    std::array<Bitboard, 64> generate_bishop_magic_numbers() {
        std::array<Bitboard, 64> magic_numbers{};
        for (uint8_t square = 0; square < 64; square++) {
            magic_numbers[square] = generate_bishop_magic_number(square);
        }
        return magic_numbers;
    }

    void fancy_print_bishop_magic_numbers() {
        std::array<Bitboard, 64> magic_numbers = generate_bishop_magic_numbers();
        for (uint8_t square = 0; square < 64; square += 4) {
            std::cout << "0x" << std::hex << magic_numbers[square] << ", "
                      << "0x"<< std::hex << magic_numbers[square + 1] << ", "
                      << "0x"<< std::hex << magic_numbers[square + 2] << ", "
                      << "0x"<< std::hex << magic_numbers[square + 3] << "," << std::endl;
        }
    }

    // Constants
    constexpr std::array<Bitboard, 64> rook_magic_numbers = {
            0x80004008805020, 0x40200210004000, 0x300200100285040, 0x3000d0020081000,
            0x200060010442008, 0x5200010600500884, 0x480008002000300, 0x880010000204080,
            0x411002108800140, 0x40084010002000c0, 0x1001001301442000, 0x521001821001000,
            0x101a00200a011004, 0x6003009020004, 0x100030086000c, 0x1002000408690082,
            0x80004000402000, 0x10024020014000, 0x7c40110020010040, 0x10008010080081,
            0x4201010004080010, 0x2243010008020400, 0x2000040008420190, 0x20080200004c04a3,
            0x80024840002008, 0x10004240012000, 0x810080020200400, 0x910000900106101,
            0x200a200100844, 0x642000200100408, 0x100220c00011008, 0x2040082000400e1,
            0x6007401421800280, 0x303000a000404008, 0x409101002000, 0x80104202002008,
            0x2084008008080040, 0x206000806003410, 0x4109204000805, 0x4000058c52000401,
            0x208000402000400c, 0x1100208201020044, 0x802008140220010, 0x211001000090020,
            0x58000402004040, 0x421000214010008, 0xc08100201040028, 0x104008408620009,
            0x481214700800100, 0x5410106000400040, 0x20001102a04100, 0x1042100300201900,
            0x100508010100, 0x801000802040100, 0x60101a210081400, 0x4680010442840200,
            0x2080420100902482, 0x601901400281, 0x4401012002281141, 0x220040300666,
            0x1004210040801, 0x2845000208240001, 0x20090800900244, 0x4120484050028c6,

    };

    constexpr std::array<Bitboard, 64> bishop_magic_numbers = {
            0x60141002002020, 0x5410300202404000, 0x61020402400000, 0x18048108880004,
            0x221210120a110c, 0x200a080308010008, 0x224452808c000f0, 0x8404210100200,
            0x108410042240, 0x41020a102020851, 0x1200088801002000, 0x100040400820810,
            0x11041814b02, 0x4001100a900010, 0x240020610240600, 0x100008441101020,
            0x810014044090410, 0x4804000218420400, 0x890000504002044, 0x8011041414060,
            0x2040c12020002, 0x41000820884010, 0x400040010402600e, 0x2400230a02014410,
            0x4c201040200c0100, 0x43002c0040c0400, 0x580500001140280, 0x20080001040408,
            0x1851010030104000, 0x2448060004490408, 0x1020e01d82400, 0x801220001005110,
            0x802120a182008, 0x8020a1000200112, 0x1c0048100400a2, 0x28540400080120,
            0x4010200100808, 0x1023014200110100, 0x2040641040201, 0x24404200004101,
            0x8011820100860, 0x800480808407400, 0x2021008044401008, 0x20c0204202082020,
            0x240012012001100, 0x4001101000800042, 0x2200284010e0844, 0x208048901400212,
            0x50608020b102000, 0x2000220210040882, 0x8040b3402080004, 0x230488046080000,
            0x4000000530440c20, 0x12200a242010, 0x2108080904040c04, 0x2004140802022001,
            0x44030401040e0200, 0x2000028404490400, 0x2414080024060800, 0x1002200000840400,
            0x204200c0380b0410, 0x1a20400812081210, 0x220110230040480, 0x4050020808c40540,
    };


}

