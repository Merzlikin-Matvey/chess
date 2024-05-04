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
    constexpr std::array<Bitboard, 64> rook_magic_numbers = {
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

    constexpr std::array<Bitboard, 64> bishop_magic_numbers = {
            0x448a0f9308448000, 0x40156045e44d600, 0xf4417f0240de0000, 0x132344d454330600,
            0x1973634a1d1b4010, 0x2a2103f6c420020, 0x38dd09eb5bf70012, 0x40140926680e0800,
            0x434b450f08872402, 0x834411204810000, 0x20be12d60bd58400, 0x515a4a43c0c50001,
            0x17661d0ec2080008, 0x2a6ef96a201c0104, 0x7616781914ad0810, 0x4cab80725ec50510,
            0x29cc2670ec8a2800, 0x328643050d522200, 0x587e11aa6eac0000, 0x7dca766d50180000,
            0x37eb189f4e4a0004, 0x28e45e5760930100, 0xd53215d135044840, 0x7378522085240202,
            0x210b91713c4d0008, 0x155b60481d44008c, 0x3f3b1d3e20ca0200, 0x49ef118b253c0000,
            0x1d903a0156260800, 0x4b907b0450964a0e, 0x6245930023400c8, 0x50dc7d253e860380,
            0x130f0c7400350004, 0x75f23c292d309200, 0x483402c860230200, 0x6ec002d1511d0008,
            0x424b6976146f2411, 0x31b1094759820080, 0x48c0d8dc44630800, 0x54704a50725a1001,
            0x141e522ce8880000, 0x62c92b58574b0080, 0xd580666415660020, 0x443750e45e420100,
            0x3198222a4f740082, 0x42c2b504a4982d03, 0x5141393c09530204, 0x1a103f8868d02100,
            0x276312a8048e0000, 0x50391a6511243000, 0x12e50dc431a8102, 0x447e1252ac2c0412,
            0xc28849a10100010, 0x549ccfb640102c4, 0xc46235551113080, 0xfaae14f1a4200000,
            0x46cc403bfc120000, 0x488d69a80a361008, 0x588742b0009e0103, 0x483d208272820100,
            0x65251a1208922090, 0x9c0cf584ebe84000, 0xa34678342111000, 0x774acb52830008

    };


}

