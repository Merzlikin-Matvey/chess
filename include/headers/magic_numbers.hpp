#pragma once

#include <cstdint>
#include <array>

typedef uint64_t Bitboard;

extern "C" {
    uint64_t generate_rook_magic_number(uint8_t square);
    uint64_t generate_bishop_magic_number(uint8_t square);
}

namespace chess::magic_numbers{
    Bitboard generate_rook_magic_number(uint8_t square) {
        return ::generate_rook_magic_number(square);
    }

    std::array<Bitboard, 64> generate_rook_magic_numbers() {
        std::array<Bitboard, 64> magic_numbers{};
        for (uint8_t square = 0; square < 64; square++) {
            magic_numbers[square] = generate_rook_magic_number(square);
        }
        return magic_numbers;
    }

    // Можно вставить результат как константу в код ниже
    void fancy_print_rook_magic_numbers() {
        std::array<Bitboard, 64> magic_numbers = generate_rook_magic_numbers();
        for (uint8_t square = 0; square < 64; square += 4) {
            std::cout << "0x" << std::hex << magic_numbers[square] << ", "
                      << "0x"<< std::hex << magic_numbers[square + 1] << ", "
                      << "0x"<< std::hex << magic_numbers[square + 2] << ", "
                      << "0x"<< std::hex << magic_numbers[square + 3] << "," << std::endl;
        }
    }

    std::array<Bitboard, 64> rook_magic_numbers = {
            0x7dca766d50180000, 0xbfcd1c2002fe0200, 0x751266262c018110, 0xe5c145c0f10a0014,
            0x7049675360954212, 0x1d724a807d170020, 0x700a0e8361820000, 0x7ed40c3930a11000,
            0x18450121a60002, 0x544451af3a093008, 0x1a8428a80d620108, 0x353676c04d881000,
            0x3e4571440d301000, 0x291e4e28840c4000, 0x4399023459320600, 0x69033a5c1cd90080,
            0x4bcf150c6a560800, 0x4ce38137f781201, 0x2d5443530e3d0800, 0x87e13c52844a042c,
            0x202867c830d51000, 0x8f42f623aa34081, 0x14ec687838161400, 0x236d4280409e1058,
            0x12685c412d34c50f, 0x7bfa2c7f02940001, 0x4002119543920e20, 0x528a1506225f0500,
            0xe4334550c09b8020, 0x51380d50fc18088, 0x3f8e9a1bca203e00, 0xef069dee5e9c0a28,
            0x7f1a5a72613a0412, 0x1177b31c00211008, 0x728e3694465e2681, 0x406c7160270002c3,
            0x8d15f10823e018, 0x2219063330280020, 0xa4ca213c30f70200, 0x113105c451270002,
            0x2c7758e64b410004, 0x6315213700970000, 0x7c6b209e61c90161, 0x15814ea542460000,
            0x2942a23815100000, 0x4494113b3eb40000, 0x10b565fcd5c0000, 0x44bd129020410000,
            0x51dd02f477a30022, 0xbd0058b0b8c0020, 0x1172400820346008, 0x5aca0789cf180200,
            0x1ab35140451f0800, 0x76351d8a59a20280, 0x1e78e3ca76da0000, 0x34a9a460128b4121,
            0x44b5000c732c2101, 0x3622684b39404088, 0x2d58ab0004034108, 0x4c114370f822200,
            0xd2132de5d900000, 0x60c1632a2f420000, 0x5774489a00f42800, 0x913264ae26558908,
    };


    Bitboard generate_bishop_magic_number(uint8_t square) {
        return ::generate_bishop_magic_number(square);
    }

    std::array<Bitboard, 64> generate_bishop_magic_numbers() {
        std::array<Bitboard, 64> magic_numbers{};
        for (uint8_t square = 0; square < 64; square++) {
            magic_numbers[square] = generate_bishop_magic_number(square);
        }
        return magic_numbers;
    }

    // Можно вставить результат как константу в код ниже
    void fancy_print_bishop_magic_numbers() {
        std::array<Bitboard, 64> magic_numbers = generate_bishop_magic_numbers();
        for (uint8_t square = 0; square < 64; square += 4) {
            std::cout << "0x" << std::hex << magic_numbers[square] << ", "
                      << "0x"<< std::hex << magic_numbers[square + 1] << ", "
                      << "0x"<< std::hex << magic_numbers[square + 2] << ", "
                      << "0x"<< std::hex << magic_numbers[square + 3] << "," << std::endl;
        }
    }

    std::array<Bitboard, 64> bishop_magic_numbers = {
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

