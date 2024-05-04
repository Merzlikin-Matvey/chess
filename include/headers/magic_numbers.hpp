#pragma once

#include <cstdint>
#include <array>

typedef uint64_t Bitboard;


extern "C" {
    #include "C functions/magic_numbers.h"
}

namespace chess::magic_numbers{
    Bitboard generate_rook_magic_number(uint8_t square) {
        return ::_c_generate_rook_magic_number(square);
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
        return ::_c_generate_bishop_magic_number(square);
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
    const std::array<Bitboard, 64> rook_magic_numbers = {
            0x7dca766d50180000, 0x1a49239548d70068, 0x751266262c018110, 0x8261742f33246085,
            0x1f50155248e40420, 0x6af0210d0b842000, 0x84ea509625310000, 0x6f9068a544d48284,
            0x5389cc3179a21404, 0x108b73d9716b1011, 0x652a087401000080, 0x96a2cd1350c8250,
            0x29941c9843db0200, 0x683017161a0b8000, 0x6ac0199e06000042, 0x9aa600847b64201,
            0x29b2130c0e01d202, 0x10302a4c2e0f0800, 0xb68867d481c28000, 0x688625d48b440800,
            0x2ece6d7d08cb0000, 0x166124e0aea2111, 0x4c0713a515a2012, 0xbc112d531120020,
            0x4aa399410200c00, 0x5eed17921df20804, 0x29702d9a03913401, 0x64106a101eb90004,
            0x29f8450109920004, 0xc7c12193bb40000, 0x2c5a43853d240000, 0x92423f76f134000,
            0xf40868b418070040, 0x909a8a100d82022, 0x46c222812208040, 0x7dd03496406e8014,
            0x24f011b900510204, 0x250577bfed0a602c, 0x79c866820c4b2002, 0x4c5315154114820,
            0x7731291c2f9f1000, 0x795040535cc10100, 0x28696b0019740003, 0x26da31d43f340170,
            0x4ba408744849010a, 0x2a4e1d053e758000, 0x4c3fedcc48062404, 0x8f997c4008f72000,
            0x34065144570d0000, 0x6b3920a4057ac008, 0x760d4021573a0000, 0x162e480310f20040,
            0x6a94439078a11000, 0x565925539deb4040, 0xa3081b7241ba8204, 0x45381b296d460008,
            0x58072ec028d90800, 0x3eea11c802b1204c, 0x57a3321893a00001, 0x30946dd84e268201,
            0x6c88089e3ccc1040, 0x85e28a91c200101, 0x394e240444530040, 0x5dc416262a990000,
    };

    const std::array<Bitboard, 64> bishop_magic_numbers = {
            0x1f165d9a51400a00, 0x7e48ffae265f0880, 0x69fd16f15a390060, 0x138c1f8e5f4b0023,
            0x215362b49550304, 0x270710a86a625040, 0x5be60bb257290032, 0x6fb82dd0480c0080,
            0x3e87ebd315504021, 0x2412196b38d50600, 0x96a5b8a4d720080, 0x2ad1524341091020,
            0x5c16540645c00424, 0x7b2013046a020d08, 0x425e02d9244c0821, 0x428516d00a908010,
            0x593867ec43ef4180, 0x136c210c136a8001, 0x51028a9946c50008, 0x3e98902520a30208,
            0xf9c674d68850500, 0x4a36048355200101, 0x21094e853dcbe0a0, 0x52c1a2b217970000,
            0x7c0b302d1add0000, 0x4430321860390044, 0x43093e242fd14d00, 0x50b513b54c079240,
            0x35e20e8331e4c054, 0x5a00258053e50400, 0x5c1101cb70ba1580, 0x31e10ad390cc0102,
            0x46825e3519db0000, 0x3934e76210581804, 0xa096f4268060000, 0x6444ae4963189001,
            0x2ab5378e7ee4400c, 0x460c836744530008, 0x5d11dd92beb4410, 0x9544750026400000,
            0xb94290342a8284c1, 0x60a4203c3a206000, 0x3273a83a609c0200, 0x20713b457028290a,
            0x74c400410b372480, 0x1b9153eb22c60000, 0x1adcfaff2f3a2201, 0x14acf9002e550004,
            0x5361520509ae2080, 0x38932950c9102004, 0x4dc6693420980018, 0x9210de1802a018,
            0x5b420a7d3a6c0818, 0x69182ef52aa4000a, 0x7870a7a429012000, 0x2424268025c20000,
            0xc572411b16c10000, 0x602122079ba80182, 0x320c67b70c228408, 0x241624d21a481000,
            0x6517e2004d584008, 0x2f4486a540a41000, 0x54811b8916a80086, 0xb0940a400493008,

    };


}

