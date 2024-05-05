#pragma once

#include <cstdint>
#include <array>
#include <iostream>

typedef uint64_t Bitboard;


extern "C" {
    #include "C functions/magic_numbers.h"
}

namespace chess::magic_numbers{
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
            0x777f67fefe7b4873, 0xdd597efff65f58ec, 0x5fe97ddf58fed7ab, 0x41f77ffbfde7e146,
            0x5bfc72e24df527f8, 0x3f1ff9f8efef438d, 0x3f7635defdef7263, 0xdbffd7bfefe9079a,
            0xffe65dbb531fd7b7, 0xfeb3e57972bbd95a, 0x63adbb7ff31da317, 0xad5d7febf5fea8d4,
            0xfdabcff3dbcfe0c6, 0x76fffff72cfc8611, 0xc69e3f97f8778641, 0xfd3dff7fedfef087,
            0x5f76fdefe97fd4a1, 0xd777fcebadff2367, 0xf77e7f25de7e2a97, 0xffea5bfeff7b7796,
            0xd7bfbc7d78fe4e2a, 0x6aec7dfef67b06fb, 0xdff6feefcf7c8f54, 0xeded3b5b7fdfa45c,
            0xf94a5f9e7cfebb43, 0x5bfb7ffbffeec33a, 0xf5fff72fffdb3fe6, 0xf3fde5bfb77ec794,
            0x7df51fd937ffa861, 0xbdcffdfdff5e26bb, 0xb6ab3ffbf75f4095, 0x77bf77fbf5fd50b3,
            0x7f357def1fffbf00, 0x9fe9fba1dfbf0ae5, 0xefda750b5fdf7fd0, 0x79dd06ff47e696bd,
            0x1ebf7f3f7fdf9ea8, 0x7fdffffbe57efdc5, 0x3b547bf73e5b82c5, 0xbb7e3b4ffbfb2f63,
            0xe1bfdff5fe770624, 0xda3771fe110f59dc, 0xe6eb7ffdd9ee11f2, 0x7e3f6d14bfbf703b,
            0x7e33f7df6eebc550, 0xd6ffde6ffbff015c, 0x4ffb43ffe4ef0119, 0x7fbb5fdb707da5f5,
            0x778b1ee9ffba011c, 0xff7fffe77aff7029, 0x5ffd77a5ffff7713, 0x7fb73efeef7fd3e8,
            0x1bdaf73b9fbfe8e0, 0xdf7d5dedeabf1a34, 0x5dbf6f7f5b4e8277, 0xd7fa4bdf7c7cfd05,
            0x6feedc96fe7ffa2b, 0xdbfa79df7bf7aaa2, 0xedbefffe21fde373, 0x5fbb6ba7bffc29d3,
            0xfff77db437bbc9af, 0xbffffff7e7ff0a9e, 0x7b5fff73dd9f3149, 0x5ffdfdf77e4eb5a9,
    };


}

