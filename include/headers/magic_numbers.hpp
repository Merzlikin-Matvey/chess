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

    Bitboard generate_vertical_pin_magic_number(uint8_t square){
        return ::_generate_vertical_pin_magic_number(square);
    }

    std::array<Bitboard, 64> generate_vertical_pin_magic_numbers() {
        std::array<Bitboard, 64> magic_numbers{};
        for (uint8_t square = 0; square < 64; square++) {
            magic_numbers[square] = generate_vertical_pin_magic_number(square);
        }
        return magic_numbers;
    }

    void fancy_print_vertical_pin_magic_numbers() {
        std::array<Bitboard, 64> magic_numbers = generate_vertical_pin_magic_numbers();
        for (uint8_t square = 0; square < 64; square += 4) {
            std::cout << "0x" << std::hex << magic_numbers[square] << ", "
                      << "0x"<< std::hex << magic_numbers[square + 1] << ", "
                      << "0x"<< std::hex << magic_numbers[square + 2] << ", "
                      << "0x"<< std::hex << magic_numbers[square + 3] << "," << std::endl;
        }
    }

    Bitboard generate_horizontal_pin_magic_number(uint8_t square){
        return ::_generate_horizontal_pin_magic_number(square);
    }

    std::array<Bitboard, 64> generate_horizontal_pin_magic_numbers() {
        std::array<Bitboard, 64> magic_numbers{};
        for (uint8_t square = 0; square < 64; square++) {
            magic_numbers[square] = generate_horizontal_pin_magic_number(square);
        }
        return magic_numbers;
    }

    void fancy_print_horizontal_pin_magic_numbers() {
        std::array<Bitboard, 64> magic_numbers = generate_horizontal_pin_magic_numbers();
        for (uint8_t square = 0; square < 64; square += 4) {
            std::cout << "0x" << std::hex << magic_numbers[square] << ", "
                      << "0x"<< std::hex << magic_numbers[square + 1] << ", "
                      << "0x"<< std::hex << magic_numbers[square + 2] << ", "
                      << "0x"<< std::hex << magic_numbers[square + 3] << "," << std::endl;
        }
    }

    Bitboard generate_up_right_pin_magic_number(uint8_t square){
        return ::_generate_up_right_pin_magic_number(square);
    }

    std::array<Bitboard, 64> generate_up_right_pin_magic_numbers() {
        std::array<Bitboard, 64> magic_numbers{};
        for (uint8_t square = 0; square < 64; square++) {
            magic_numbers[square] = generate_up_right_pin_magic_number(square);
        }
        return magic_numbers;
    }

    void fancy_print_up_right_pin_magic_numbers() {
        std::array<Bitboard, 64> magic_numbers = generate_up_right_pin_magic_numbers();
        for (uint8_t square = 0; square < 64; square += 4) {
            std::cout << "0x" << std::hex << magic_numbers[square] << ", "
                      << "0x"<< std::hex << magic_numbers[square + 1] << ", "
                      << "0x"<< std::hex << magic_numbers[square + 2] << ", "
                      << "0x"<< std::hex << magic_numbers[square + 3] << "," << std::endl;
        }
    }

    Bitboard generate_down_right_pin_magic_number(uint8_t square){
        return ::_generate_down_right_pin_magic_number(square);
    }

    std::array<Bitboard, 64> generate_down_right_pin_magic_numbers() {
        std::array<Bitboard, 64> magic_numbers{};
        for (uint8_t square = 0; square < 64; square++) {
            magic_numbers[square] = generate_down_right_pin_magic_number(square);
        }
        return magic_numbers;
    }

    void fancy_print_down_right_pin_magic_numbers() {
        std::array<Bitboard, 64> magic_numbers = generate_down_right_pin_magic_numbers();
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

    constexpr std::array<Bitboard, 64> vertical_pin_magic_numbers = {
            0x181180204502040, 0x4204192002081040, 0x41122030080c0081, 0x10210401814802,
            0x4008800220341, 0x44401261020084, 0x8402100100b82, 0x4402208801005,
            0x480308008204092, 0x4080080410062001, 0x1010081403812002, 0x1000310408480082,
            0x142040500880022, 0x1528040011014082, 0x1008102140810012, 0x108008004213041,
            0x4010002008800244, 0x2002000430405811, 0x804002001900631, 0x604081000810048,
            0x4104002a080084, 0x142246400801102, 0x6408400812220081, 0x4200a40081081,
            0x420088046401080, 0x200940940a040810, 0x1004081200a22001, 0x1000480801220084,
            0x5144048203002208, 0x281040400132042, 0x8010400565000a, 0x82502000400409,
            0x4080208800900402, 0x4801041008200240, 0x80402a000101306, 0x43d00088030a0c11,
            0x1048041020020081, 0x410408400002209, 0x281420010a00821, 0x5101a8020040441,
            0x4008022010020480, 0x420084130004002, 0xac8020420000310, 0x1282005008150401,
            0x8802a041081204, 0x26008111000244, 0x60104009000182, 0x52800c2010080041,
            0x1040220448200280, 0x224088120102040, 0x4090010402080120, 0x1008040104814112,
            0x884082200480001, 0x450210220080410c, 0x20041104a812081, 0x10054060800801,
            0x84004c220801008, 0x1005404204082040, 0x2810089120040200, 0x811408021002c0,
            0x4100208042080400, 0x10290400804200, 0x4100604810804201, 0x1300201005800840
    };

    constexpr std::array<Bitboard, 64> horizontal_pin_magic_numbers = {
            0x100001204054008, 0x1301004020801810, 0xd00001010000551, 0x4900040001000088,
            0x1100420010822068, 0x808000020410000, 0x4100210002100040, 0x200407008001200,
            0x1000800002040, 0x2043000048400800, 0x225002040000001, 0x4e09004001000020,
            0x11000900020002, 0x21000020000084, 0x4040008004018, 0x81000000502080,
            0x180090000100000, 0x823700000500e1, 0x44050000020020, 0x412202018120000,
            0x1113101044060000, 0x1200210009020400, 0x1000410000000020, 0x4002420000100000,
            0x100000300110000, 0x1000300640081, 0x1026500212901, 0xa020500000,
            0x4001090100c0000, 0x2201000808201000, 0x2004104100641000, 0x28000200040008,
            0x200005051010000, 0x1400091407002204, 0x2000108040400000, 0x5181000809000000,
            0x8404210100200, 0x40000021000001, 0x42000c002c040000, 0x4001052040800000,
            0x3040001400a10001, 0x120001009430000, 0x5420000000050000, 0x100090800090008,
            0x20a400004110002, 0x2400000040210108, 0x20001050001c0412, 0x110180020020014,
            0x10000000600902, 0x40260024000301, 0x1002020000000d00, 0x240010804106900,
            0x9003000001100, 0x4180042210016100, 0x3040002042084101, 0x482020001022040,
            0x90054100101, 0x2000820004003, 0x113004000004d, 0x200340010012019,
            0x58080a10000611, 0x28019008010c21, 0x1800e001400041, 0x2002400040204002,
    };

    constexpr std::array<Bitboard, 64> up_right_pin_magic_numbers = {
            0x100220900480200, 0x28900c204440000, 0x6060205044042100, 0x20084044000012,
            0x1490b4001005000, 0x4118082701000020, 0x804003821000000, 0x5800210020000420,
            0x405344022021, 0x400028014020100, 0x2800080442024300, 0x400600820100001,
            0xa10220944010080, 0x890412000a4040, 0x100024c00000004, 0x480000800000141,
            0x5012d200820800, 0x1102112020109, 0x82004002401600, 0x4354002808150000,
            0x5040400421200001, 0x410a0110020008, 0x840500400204040, 0x46404000000000,
            0x1442060310, 0x1088200028804b00, 0x838082408210822, 0x4041008101034100,
            0x10420100884090, 0x808410008026500, 0x140124812020100, 0x20a668002000040,
            0x204401410438, 0x4200001000202a00, 0x101400a800401440, 0x800402200500580,
            0x241008040021282, 0x202090041040403, 0x4290809002a0300, 0x8084050000008,
            0x808120026010301, 0x10010010992504, 0x240200c10405010, 0x8000021010031c0,
            0x44040400820, 0x60012051000042, 0x82070420805400, 0x12500220100004,
            0x11001020140001e0, 0x280100000100298, 0xa00024083a1014, 0x8211301010020,
            0x34010540204, 0x2000080425004194, 0x2640422090002, 0x4810480801101105,
            0x8140001000000, 0x80008822280, 0x4000500100141300, 0x14000100841422,
            0x8841444440, 0x201042104260, 0x1008420480480, 0x2208021a01040,
    };

    constexpr std::array<Bitboard, 64> down_right_pin_magic_numbers = {
            0x80000006080, 0xa81000002080008, 0x6840540a48a00060, 0x200840480e400000,
            0x1022104020800128, 0x4472022020090001, 0x1304290b2010400e, 0x428410800410440,
            0x50000a0020460010, 0x2100620010400010, 0x90835800483040a, 0x660200944000010,
            0x4100011422802800, 0x301c1012086000, 0x8008030100420, 0x120042060120,
            0x203040a461000004, 0x530008020044000, 0x110209240200100, 0x420a5040100000,
            0x200230808241022, 0x5010400028034020, 0x281a06160e40, 0x1001209c1008,
            0x820120000002221, 0x210101052002000, 0x82304120380013, 0x19401000e104000,
            0x500409424020240, 0x5008230009410840, 0x2288088201080282, 0x40100820820990,
            0x8024aa100020c82, 0x128208200a085a06, 0x103005010280800, 0x182002300280108,
            0x500410c00020104, 0x330060040404, 0x1020220210, 0x1240000000826524,
            0x402261620100401, 0x12010908020a0420, 0x100284102803040, 0x1302410c010202,
            0x940088202820108, 0x4021051240480410, 0x2000124100400404, 0x800000040084104,
            0xa02022109080402, 0x102301208040008, 0x14020804a480440, 0x81404620104400e,
            0x605032024840018, 0x862002041032002, 0x201008850012003, 0x47110400802,
            0x18100c0208010800, 0x1a00202028280804, 0x2000010462122204, 0x82104c022010440,
            0x282400400a8a1160, 0x10008000003612f, 0x1000081014403120, 0x88020022001000
    };


}

