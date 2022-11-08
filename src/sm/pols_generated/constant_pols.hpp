#ifndef CONSTANT_POLS_HPP
#define CONSTANT_POLS_HPP

#include <cstdint>
#include "goldilocks_base_field.hpp"
#include "zkassert.hpp"

class ConstantPol
{
private:
    Goldilocks::Element * _pAddress;
    uint64_t _degree;
    uint64_t _index;
public:
    ConstantPol(Goldilocks::Element * pAddress, uint64_t degree, uint64_t index) : _pAddress(pAddress), _degree(degree), _index(index) {};
    Goldilocks::Element & operator[](uint64_t i) { return _pAddress[i*270]; };
    Goldilocks::Element * operator=(Goldilocks::Element * pAddress) { _pAddress = pAddress; return _pAddress; };

    Goldilocks::Element * address (void) { return _pAddress; }
    uint64_t degree (void) { return _degree; }
    uint64_t index (void) { return _index; }
};

class GlobalConstantPols
{
public:
    ConstantPol L1;
    ConstantPol LLAST;
    ConstantPol BYTE;
    ConstantPol BYTE2;
private:
    void * _pAddress;
    uint64_t _degree;
public:

    GlobalConstantPols (void * pAddress, uint64_t degree) :
        L1((Goldilocks::Element *)((uint8_t *)pAddress + 0), degree, 0),
        LLAST((Goldilocks::Element *)((uint8_t *)pAddress + 8), degree, 1),
        BYTE((Goldilocks::Element *)((uint8_t *)pAddress + 16), degree, 2),
        BYTE2((Goldilocks::Element *)((uint8_t *)pAddress + 24), degree, 3),
        _pAddress(pAddress),
        _degree(degree) {};

    static uint64_t pilDegree (void) { return 8388608; }
    static uint64_t pilSize (void) { return 32; }
    static uint64_t numPols (void) { return 4; }

    void * address (void) { return _pAddress; }
    uint64_t degree (void) { return _degree; }
    uint64_t size (void) { return _degree*4*sizeof(Goldilocks::Element); }
};

class RomConstantPols
{
public:
    ConstantPol CONST0;
    ConstantPol CONST1;
    ConstantPol CONST2;
    ConstantPol CONST3;
    ConstantPol CONST4;
    ConstantPol CONST5;
    ConstantPol CONST6;
    ConstantPol CONST7;
    ConstantPol offset;
    ConstantPol inA;
    ConstantPol inB;
    ConstantPol inC;
    ConstantPol inROTL_C;
    ConstantPol inD;
    ConstantPol inE;
    ConstantPol inSR;
    ConstantPol inFREE;
    ConstantPol inCTX;
    ConstantPol inSP;
    ConstantPol inPC;
    ConstantPol inGAS;
    ConstantPol inMAXMEM;
    ConstantPol inHASHPOS;
    ConstantPol inSTEP;
    ConstantPol inRR;
    ConstantPol setA;
    ConstantPol setB;
    ConstantPol setC;
    ConstantPol setD;
    ConstantPol setE;
    ConstantPol setSR;
    ConstantPol setCTX;
    ConstantPol setSP;
    ConstantPol setPC;
    ConstantPol setGAS;
    ConstantPol setMAXMEM;
    ConstantPol setHASHPOS;
    ConstantPol JMP;
    ConstantPol JMPN;
    ConstantPol JMPC;
    ConstantPol setRR;
    ConstantPol incStack;
    ConstantPol incCode;
    ConstantPol isStack;
    ConstantPol isCode;
    ConstantPol isMem;
    ConstantPol ind;
    ConstantPol indRR;
    ConstantPol useCTX;
    ConstantPol mOp;
    ConstantPol mWR;
    ConstantPol sWR;
    ConstantPol sRD;
    ConstantPol arith;
    ConstantPol arithEq0;
    ConstantPol arithEq1;
    ConstantPol arithEq2;
    ConstantPol arithEq3;
    ConstantPol memAlign;
    ConstantPol memAlignWR;
    ConstantPol memAlignWR8;
    ConstantPol hashK;
    ConstantPol hashKLen;
    ConstantPol hashKDigest;
    ConstantPol hashP;
    ConstantPol hashPLen;
    ConstantPol hashPDigest;
    ConstantPol bin;
    ConstantPol binOpcode;
    ConstantPol assert_pol;
    ConstantPol line;
private:
    void * _pAddress;
    uint64_t _degree;
public:

    RomConstantPols (void * pAddress, uint64_t degree) :
        CONST0((Goldilocks::Element *)((uint8_t *)pAddress + 32), degree, 4),
        CONST1((Goldilocks::Element *)((uint8_t *)pAddress + 40), degree, 5),
        CONST2((Goldilocks::Element *)((uint8_t *)pAddress + 48), degree, 6),
        CONST3((Goldilocks::Element *)((uint8_t *)pAddress + 56), degree, 7),
        CONST4((Goldilocks::Element *)((uint8_t *)pAddress + 64), degree, 8),
        CONST5((Goldilocks::Element *)((uint8_t *)pAddress + 72), degree, 9),
        CONST6((Goldilocks::Element *)((uint8_t *)pAddress + 80), degree, 10),
        CONST7((Goldilocks::Element *)((uint8_t *)pAddress + 88), degree, 11),
        offset((Goldilocks::Element *)((uint8_t *)pAddress + 96), degree, 12),
        inA((Goldilocks::Element *)((uint8_t *)pAddress + 104), degree, 13),
        inB((Goldilocks::Element *)((uint8_t *)pAddress + 112), degree, 14),
        inC((Goldilocks::Element *)((uint8_t *)pAddress + 120), degree, 15),
        inROTL_C((Goldilocks::Element *)((uint8_t *)pAddress + 128), degree, 16),
        inD((Goldilocks::Element *)((uint8_t *)pAddress + 136), degree, 17),
        inE((Goldilocks::Element *)((uint8_t *)pAddress + 144), degree, 18),
        inSR((Goldilocks::Element *)((uint8_t *)pAddress + 152), degree, 19),
        inFREE((Goldilocks::Element *)((uint8_t *)pAddress + 160), degree, 20),
        inCTX((Goldilocks::Element *)((uint8_t *)pAddress + 168), degree, 21),
        inSP((Goldilocks::Element *)((uint8_t *)pAddress + 176), degree, 22),
        inPC((Goldilocks::Element *)((uint8_t *)pAddress + 184), degree, 23),
        inGAS((Goldilocks::Element *)((uint8_t *)pAddress + 192), degree, 24),
        inMAXMEM((Goldilocks::Element *)((uint8_t *)pAddress + 200), degree, 25),
        inHASHPOS((Goldilocks::Element *)((uint8_t *)pAddress + 208), degree, 26),
        inSTEP((Goldilocks::Element *)((uint8_t *)pAddress + 216), degree, 27),
        inRR((Goldilocks::Element *)((uint8_t *)pAddress + 224), degree, 28),
        setA((Goldilocks::Element *)((uint8_t *)pAddress + 232), degree, 29),
        setB((Goldilocks::Element *)((uint8_t *)pAddress + 240), degree, 30),
        setC((Goldilocks::Element *)((uint8_t *)pAddress + 248), degree, 31),
        setD((Goldilocks::Element *)((uint8_t *)pAddress + 256), degree, 32),
        setE((Goldilocks::Element *)((uint8_t *)pAddress + 264), degree, 33),
        setSR((Goldilocks::Element *)((uint8_t *)pAddress + 272), degree, 34),
        setCTX((Goldilocks::Element *)((uint8_t *)pAddress + 280), degree, 35),
        setSP((Goldilocks::Element *)((uint8_t *)pAddress + 288), degree, 36),
        setPC((Goldilocks::Element *)((uint8_t *)pAddress + 296), degree, 37),
        setGAS((Goldilocks::Element *)((uint8_t *)pAddress + 304), degree, 38),
        setMAXMEM((Goldilocks::Element *)((uint8_t *)pAddress + 312), degree, 39),
        setHASHPOS((Goldilocks::Element *)((uint8_t *)pAddress + 320), degree, 40),
        JMP((Goldilocks::Element *)((uint8_t *)pAddress + 328), degree, 41),
        JMPN((Goldilocks::Element *)((uint8_t *)pAddress + 336), degree, 42),
        JMPC((Goldilocks::Element *)((uint8_t *)pAddress + 344), degree, 43),
        setRR((Goldilocks::Element *)((uint8_t *)pAddress + 352), degree, 44),
        incStack((Goldilocks::Element *)((uint8_t *)pAddress + 360), degree, 45),
        incCode((Goldilocks::Element *)((uint8_t *)pAddress + 368), degree, 46),
        isStack((Goldilocks::Element *)((uint8_t *)pAddress + 376), degree, 47),
        isCode((Goldilocks::Element *)((uint8_t *)pAddress + 384), degree, 48),
        isMem((Goldilocks::Element *)((uint8_t *)pAddress + 392), degree, 49),
        ind((Goldilocks::Element *)((uint8_t *)pAddress + 400), degree, 50),
        indRR((Goldilocks::Element *)((uint8_t *)pAddress + 408), degree, 51),
        useCTX((Goldilocks::Element *)((uint8_t *)pAddress + 416), degree, 52),
        mOp((Goldilocks::Element *)((uint8_t *)pAddress + 424), degree, 53),
        mWR((Goldilocks::Element *)((uint8_t *)pAddress + 432), degree, 54),
        sWR((Goldilocks::Element *)((uint8_t *)pAddress + 440), degree, 55),
        sRD((Goldilocks::Element *)((uint8_t *)pAddress + 448), degree, 56),
        arith((Goldilocks::Element *)((uint8_t *)pAddress + 456), degree, 57),
        arithEq0((Goldilocks::Element *)((uint8_t *)pAddress + 464), degree, 58),
        arithEq1((Goldilocks::Element *)((uint8_t *)pAddress + 472), degree, 59),
        arithEq2((Goldilocks::Element *)((uint8_t *)pAddress + 480), degree, 60),
        arithEq3((Goldilocks::Element *)((uint8_t *)pAddress + 488), degree, 61),
        memAlign((Goldilocks::Element *)((uint8_t *)pAddress + 496), degree, 62),
        memAlignWR((Goldilocks::Element *)((uint8_t *)pAddress + 504), degree, 63),
        memAlignWR8((Goldilocks::Element *)((uint8_t *)pAddress + 512), degree, 64),
        hashK((Goldilocks::Element *)((uint8_t *)pAddress + 520), degree, 65),
        hashKLen((Goldilocks::Element *)((uint8_t *)pAddress + 528), degree, 66),
        hashKDigest((Goldilocks::Element *)((uint8_t *)pAddress + 536), degree, 67),
        hashP((Goldilocks::Element *)((uint8_t *)pAddress + 544), degree, 68),
        hashPLen((Goldilocks::Element *)((uint8_t *)pAddress + 552), degree, 69),
        hashPDigest((Goldilocks::Element *)((uint8_t *)pAddress + 560), degree, 70),
        bin((Goldilocks::Element *)((uint8_t *)pAddress + 568), degree, 71),
        binOpcode((Goldilocks::Element *)((uint8_t *)pAddress + 576), degree, 72),
        assert_pol((Goldilocks::Element *)((uint8_t *)pAddress + 584), degree, 73),
        line((Goldilocks::Element *)((uint8_t *)pAddress + 592), degree, 74),
        _pAddress(pAddress),
        _degree(degree) {};

    static uint64_t pilDegree (void) { return 8388608; }
    static uint64_t pilSize (void) { return 568; }
    static uint64_t numPols (void) { return 71; }

    void * address (void) { return _pAddress; }
    uint64_t degree (void) { return _degree; }
    uint64_t size (void) { return _degree*71*sizeof(Goldilocks::Element); }
};

class Byte4ConstantPols
{
public:
    ConstantPol SET;
private:
    void * _pAddress;
    uint64_t _degree;
public:

    Byte4ConstantPols (void * pAddress, uint64_t degree) :
        SET((Goldilocks::Element *)((uint8_t *)pAddress + 600), degree, 75),
        _pAddress(pAddress),
        _degree(degree) {};

    static uint64_t pilDegree (void) { return 8388608; }
    static uint64_t pilSize (void) { return 8; }
    static uint64_t numPols (void) { return 1; }

    void * address (void) { return _pAddress; }
    uint64_t degree (void) { return _degree; }
    uint64_t size (void) { return _degree*1*sizeof(Goldilocks::Element); }
};

class MemAlignConstantPols
{
public:
    ConstantPol BYTE2A;
    ConstantPol BYTE2B;
    ConstantPol BYTE_C3072;
    ConstantPol FACTOR[8];
    ConstantPol FACTORV[8];
    ConstantPol STEP;
    ConstantPol WR256;
    ConstantPol WR8;
    ConstantPol OFFSET;
    ConstantPol RESET;
    ConstantPol SELM1;
private:
    void * _pAddress;
    uint64_t _degree;
public:

    MemAlignConstantPols (void * pAddress, uint64_t degree) :
        BYTE2A((Goldilocks::Element *)((uint8_t *)pAddress + 608), degree, 76),
        BYTE2B((Goldilocks::Element *)((uint8_t *)pAddress + 616), degree, 77),
        BYTE_C3072((Goldilocks::Element *)((uint8_t *)pAddress + 624), degree, 78),
        FACTOR{
            ConstantPol((Goldilocks::Element *)((uint8_t *)pAddress + 632), degree, 79),
            ConstantPol((Goldilocks::Element *)((uint8_t *)pAddress + 640), degree, 80),
            ConstantPol((Goldilocks::Element *)((uint8_t *)pAddress + 648), degree, 81),
            ConstantPol((Goldilocks::Element *)((uint8_t *)pAddress + 656), degree, 82),
            ConstantPol((Goldilocks::Element *)((uint8_t *)pAddress + 664), degree, 83),
            ConstantPol((Goldilocks::Element *)((uint8_t *)pAddress + 672), degree, 84),
            ConstantPol((Goldilocks::Element *)((uint8_t *)pAddress + 680), degree, 85),
            ConstantPol((Goldilocks::Element *)((uint8_t *)pAddress + 688), degree, 86)
        },
        FACTORV{
            ConstantPol((Goldilocks::Element *)((uint8_t *)pAddress + 696), degree, 87),
            ConstantPol((Goldilocks::Element *)((uint8_t *)pAddress + 704), degree, 88),
            ConstantPol((Goldilocks::Element *)((uint8_t *)pAddress + 712), degree, 89),
            ConstantPol((Goldilocks::Element *)((uint8_t *)pAddress + 720), degree, 90),
            ConstantPol((Goldilocks::Element *)((uint8_t *)pAddress + 728), degree, 91),
            ConstantPol((Goldilocks::Element *)((uint8_t *)pAddress + 736), degree, 92),
            ConstantPol((Goldilocks::Element *)((uint8_t *)pAddress + 744), degree, 93),
            ConstantPol((Goldilocks::Element *)((uint8_t *)pAddress + 752), degree, 94)
        },
        STEP((Goldilocks::Element *)((uint8_t *)pAddress + 760), degree, 95),
        WR256((Goldilocks::Element *)((uint8_t *)pAddress + 768), degree, 96),
        WR8((Goldilocks::Element *)((uint8_t *)pAddress + 776), degree, 97),
        OFFSET((Goldilocks::Element *)((uint8_t *)pAddress + 784), degree, 98),
        RESET((Goldilocks::Element *)((uint8_t *)pAddress + 792), degree, 99),
        SELM1((Goldilocks::Element *)((uint8_t *)pAddress + 800), degree, 100),
        _pAddress(pAddress),
        _degree(degree) {};

    static uint64_t pilDegree (void) { return 8388608; }
    static uint64_t pilSize (void) { return 200; }
    static uint64_t numPols (void) { return 25; }

    void * address (void) { return _pAddress; }
    uint64_t degree (void) { return _degree; }
    uint64_t size (void) { return _degree*25*sizeof(Goldilocks::Element); }
};

class ArithConstantPols
{
public:
    ConstantPol BYTE2_BIT19;
    ConstantPol SEL_BYTE2_BIT19;
    ConstantPol GL_SIGNED_4BITS_C0;
    ConstantPol GL_SIGNED_4BITS_C1;
    ConstantPol GL_SIGNED_4BITS_C2;
    ConstantPol GL_SIGNED_18BITS;
    ConstantPol CLK[32];
private:
    void * _pAddress;
    uint64_t _degree;
public:

    ArithConstantPols (void * pAddress, uint64_t degree) :
        BYTE2_BIT19((Goldilocks::Element *)((uint8_t *)pAddress + 808), degree, 101),
        SEL_BYTE2_BIT19((Goldilocks::Element *)((uint8_t *)pAddress + 816), degree, 102),
        GL_SIGNED_4BITS_C0((Goldilocks::Element *)((uint8_t *)pAddress + 824), degree, 103),
        GL_SIGNED_4BITS_C1((Goldilocks::Element *)((uint8_t *)pAddress + 832), degree, 104),
        GL_SIGNED_4BITS_C2((Goldilocks::Element *)((uint8_t *)pAddress + 840), degree, 105),
        GL_SIGNED_18BITS((Goldilocks::Element *)((uint8_t *)pAddress + 848), degree, 106),
        CLK{
            ConstantPol((Goldilocks::Element *)((uint8_t *)pAddress + 856), degree, 107),
            ConstantPol((Goldilocks::Element *)((uint8_t *)pAddress + 864), degree, 108),
            ConstantPol((Goldilocks::Element *)((uint8_t *)pAddress + 872), degree, 109),
            ConstantPol((Goldilocks::Element *)((uint8_t *)pAddress + 880), degree, 110),
            ConstantPol((Goldilocks::Element *)((uint8_t *)pAddress + 888), degree, 111),
            ConstantPol((Goldilocks::Element *)((uint8_t *)pAddress + 896), degree, 112),
            ConstantPol((Goldilocks::Element *)((uint8_t *)pAddress + 904), degree, 113),
            ConstantPol((Goldilocks::Element *)((uint8_t *)pAddress + 912), degree, 114),
            ConstantPol((Goldilocks::Element *)((uint8_t *)pAddress + 920), degree, 115),
            ConstantPol((Goldilocks::Element *)((uint8_t *)pAddress + 928), degree, 116),
            ConstantPol((Goldilocks::Element *)((uint8_t *)pAddress + 936), degree, 117),
            ConstantPol((Goldilocks::Element *)((uint8_t *)pAddress + 944), degree, 118),
            ConstantPol((Goldilocks::Element *)((uint8_t *)pAddress + 952), degree, 119),
            ConstantPol((Goldilocks::Element *)((uint8_t *)pAddress + 960), degree, 120),
            ConstantPol((Goldilocks::Element *)((uint8_t *)pAddress + 968), degree, 121),
            ConstantPol((Goldilocks::Element *)((uint8_t *)pAddress + 976), degree, 122),
            ConstantPol((Goldilocks::Element *)((uint8_t *)pAddress + 984), degree, 123),
            ConstantPol((Goldilocks::Element *)((uint8_t *)pAddress + 992), degree, 124),
            ConstantPol((Goldilocks::Element *)((uint8_t *)pAddress + 1000), degree, 125),
            ConstantPol((Goldilocks::Element *)((uint8_t *)pAddress + 1008), degree, 126),
            ConstantPol((Goldilocks::Element *)((uint8_t *)pAddress + 1016), degree, 127),
            ConstantPol((Goldilocks::Element *)((uint8_t *)pAddress + 1024), degree, 128),
            ConstantPol((Goldilocks::Element *)((uint8_t *)pAddress + 1032), degree, 129),
            ConstantPol((Goldilocks::Element *)((uint8_t *)pAddress + 1040), degree, 130),
            ConstantPol((Goldilocks::Element *)((uint8_t *)pAddress + 1048), degree, 131),
            ConstantPol((Goldilocks::Element *)((uint8_t *)pAddress + 1056), degree, 132),
            ConstantPol((Goldilocks::Element *)((uint8_t *)pAddress + 1064), degree, 133),
            ConstantPol((Goldilocks::Element *)((uint8_t *)pAddress + 1072), degree, 134),
            ConstantPol((Goldilocks::Element *)((uint8_t *)pAddress + 1080), degree, 135),
            ConstantPol((Goldilocks::Element *)((uint8_t *)pAddress + 1088), degree, 136),
            ConstantPol((Goldilocks::Element *)((uint8_t *)pAddress + 1096), degree, 137),
            ConstantPol((Goldilocks::Element *)((uint8_t *)pAddress + 1104), degree, 138)
        },
        _pAddress(pAddress),
        _degree(degree) {};

    static uint64_t pilDegree (void) { return 8388608; }
    static uint64_t pilSize (void) { return 304; }
    static uint64_t numPols (void) { return 38; }

    void * address (void) { return _pAddress; }
    uint64_t degree (void) { return _degree; }
    uint64_t size (void) { return _degree*38*sizeof(Goldilocks::Element); }
};

class BinaryConstantPols
{
public:
    ConstantPol P_OPCODE;
    ConstantPol P_A;
    ConstantPol P_B;
    ConstantPol P_CIN;
    ConstantPol P_LAST;
    ConstantPol P_USE_CARRY;
    ConstantPol P_C;
    ConstantPol P_COUT;
    ConstantPol RESET;
    ConstantPol FACTOR[8];
private:
    void * _pAddress;
    uint64_t _degree;
public:

    BinaryConstantPols (void * pAddress, uint64_t degree) :
        P_OPCODE((Goldilocks::Element *)((uint8_t *)pAddress + 1112), degree, 139),
        P_A((Goldilocks::Element *)((uint8_t *)pAddress + 1120), degree, 140),
        P_B((Goldilocks::Element *)((uint8_t *)pAddress + 1128), degree, 141),
        P_CIN((Goldilocks::Element *)((uint8_t *)pAddress + 1136), degree, 142),
        P_LAST((Goldilocks::Element *)((uint8_t *)pAddress + 1144), degree, 143),
        P_USE_CARRY((Goldilocks::Element *)((uint8_t *)pAddress + 1152), degree, 144),
        P_C((Goldilocks::Element *)((uint8_t *)pAddress + 1160), degree, 145),
        P_COUT((Goldilocks::Element *)((uint8_t *)pAddress + 1168), degree, 146),
        RESET((Goldilocks::Element *)((uint8_t *)pAddress + 1176), degree, 147),
        FACTOR{
            ConstantPol((Goldilocks::Element *)((uint8_t *)pAddress + 1184), degree, 148),
            ConstantPol((Goldilocks::Element *)((uint8_t *)pAddress + 1192), degree, 149),
            ConstantPol((Goldilocks::Element *)((uint8_t *)pAddress + 1200), degree, 150),
            ConstantPol((Goldilocks::Element *)((uint8_t *)pAddress + 1208), degree, 151),
            ConstantPol((Goldilocks::Element *)((uint8_t *)pAddress + 1216), degree, 152),
            ConstantPol((Goldilocks::Element *)((uint8_t *)pAddress + 1224), degree, 153),
            ConstantPol((Goldilocks::Element *)((uint8_t *)pAddress + 1232), degree, 154),
            ConstantPol((Goldilocks::Element *)((uint8_t *)pAddress + 1240), degree, 155)
        },
        _pAddress(pAddress),
        _degree(degree) {};

    static uint64_t pilDegree (void) { return 8388608; }
    static uint64_t pilSize (void) { return 136; }
    static uint64_t numPols (void) { return 17; }

    void * address (void) { return _pAddress; }
    uint64_t degree (void) { return _degree; }
    uint64_t size (void) { return _degree*17*sizeof(Goldilocks::Element); }
};

class PoseidonGConstantPols
{
public:
    ConstantPol LAST;
    ConstantPol LATCH;
    ConstantPol LASTBLOCK;
    ConstantPol PARTIAL;
    ConstantPol C[12];
private:
    void * _pAddress;
    uint64_t _degree;
public:

    PoseidonGConstantPols (void * pAddress, uint64_t degree) :
        LAST((Goldilocks::Element *)((uint8_t *)pAddress + 1248), degree, 156),
        LATCH((Goldilocks::Element *)((uint8_t *)pAddress + 1256), degree, 157),
        LASTBLOCK((Goldilocks::Element *)((uint8_t *)pAddress + 1264), degree, 158),
        PARTIAL((Goldilocks::Element *)((uint8_t *)pAddress + 1272), degree, 159),
        C{
            ConstantPol((Goldilocks::Element *)((uint8_t *)pAddress + 1280), degree, 160),
            ConstantPol((Goldilocks::Element *)((uint8_t *)pAddress + 1288), degree, 161),
            ConstantPol((Goldilocks::Element *)((uint8_t *)pAddress + 1296), degree, 162),
            ConstantPol((Goldilocks::Element *)((uint8_t *)pAddress + 1304), degree, 163),
            ConstantPol((Goldilocks::Element *)((uint8_t *)pAddress + 1312), degree, 164),
            ConstantPol((Goldilocks::Element *)((uint8_t *)pAddress + 1320), degree, 165),
            ConstantPol((Goldilocks::Element *)((uint8_t *)pAddress + 1328), degree, 166),
            ConstantPol((Goldilocks::Element *)((uint8_t *)pAddress + 1336), degree, 167),
            ConstantPol((Goldilocks::Element *)((uint8_t *)pAddress + 1344), degree, 168),
            ConstantPol((Goldilocks::Element *)((uint8_t *)pAddress + 1352), degree, 169),
            ConstantPol((Goldilocks::Element *)((uint8_t *)pAddress + 1360), degree, 170),
            ConstantPol((Goldilocks::Element *)((uint8_t *)pAddress + 1368), degree, 171)
        },
        _pAddress(pAddress),
        _degree(degree) {};

    static uint64_t pilDegree (void) { return 8388608; }
    static uint64_t pilSize (void) { return 128; }
    static uint64_t numPols (void) { return 16; }

    void * address (void) { return _pAddress; }
    uint64_t degree (void) { return _degree; }
    uint64_t size (void) { return _degree*16*sizeof(Goldilocks::Element); }
};

class PaddingPGConstantPols
{
public:
    ConstantPol F[8];
    ConstantPol lastBlock;
    ConstantPol k_crOffset;
    ConstantPol k_crF0;
    ConstantPol k_crF1;
    ConstantPol k_crF2;
    ConstantPol k_crF3;
    ConstantPol k_crF4;
    ConstantPol k_crF5;
    ConstantPol k_crF6;
    ConstantPol k_crF7;
private:
    void * _pAddress;
    uint64_t _degree;
public:

    PaddingPGConstantPols (void * pAddress, uint64_t degree) :
        F{
            ConstantPol((Goldilocks::Element *)((uint8_t *)pAddress + 1376), degree, 172),
            ConstantPol((Goldilocks::Element *)((uint8_t *)pAddress + 1384), degree, 173),
            ConstantPol((Goldilocks::Element *)((uint8_t *)pAddress + 1392), degree, 174),
            ConstantPol((Goldilocks::Element *)((uint8_t *)pAddress + 1400), degree, 175),
            ConstantPol((Goldilocks::Element *)((uint8_t *)pAddress + 1408), degree, 176),
            ConstantPol((Goldilocks::Element *)((uint8_t *)pAddress + 1416), degree, 177),
            ConstantPol((Goldilocks::Element *)((uint8_t *)pAddress + 1424), degree, 178),
            ConstantPol((Goldilocks::Element *)((uint8_t *)pAddress + 1432), degree, 179)
        },
        lastBlock((Goldilocks::Element *)((uint8_t *)pAddress + 1440), degree, 180),
        k_crOffset((Goldilocks::Element *)((uint8_t *)pAddress + 1448), degree, 181),
        k_crF0((Goldilocks::Element *)((uint8_t *)pAddress + 1456), degree, 182),
        k_crF1((Goldilocks::Element *)((uint8_t *)pAddress + 1464), degree, 183),
        k_crF2((Goldilocks::Element *)((uint8_t *)pAddress + 1472), degree, 184),
        k_crF3((Goldilocks::Element *)((uint8_t *)pAddress + 1480), degree, 185),
        k_crF4((Goldilocks::Element *)((uint8_t *)pAddress + 1488), degree, 186),
        k_crF5((Goldilocks::Element *)((uint8_t *)pAddress + 1496), degree, 187),
        k_crF6((Goldilocks::Element *)((uint8_t *)pAddress + 1504), degree, 188),
        k_crF7((Goldilocks::Element *)((uint8_t *)pAddress + 1512), degree, 189),
        _pAddress(pAddress),
        _degree(degree) {};

    static uint64_t pilDegree (void) { return 8388608; }
    static uint64_t pilSize (void) { return 144; }
    static uint64_t numPols (void) { return 18; }

    void * address (void) { return _pAddress; }
    uint64_t degree (void) { return _degree; }
    uint64_t size (void) { return _degree*18*sizeof(Goldilocks::Element); }
};

class StorageConstantPols
{
public:
    ConstantPol rHash;
    ConstantPol rHashType;
    ConstantPol rLatchGet;
    ConstantPol rLatchSet;
    ConstantPol rClimbRkey;
    ConstantPol rClimbSiblingRkey;
    ConstantPol rClimbSiblingRkeyN;
    ConstantPol rRotateLevel;
    ConstantPol rJmpz;
    ConstantPol rJmp;
    ConstantPol rConst0;
    ConstantPol rConst1;
    ConstantPol rConst2;
    ConstantPol rConst3;
    ConstantPol rAddress;
    ConstantPol rLine;
    ConstantPol rInFree;
    ConstantPol rInNewRoot;
    ConstantPol rInOldRoot;
    ConstantPol rInRkey;
    ConstantPol rInRkeyBit;
    ConstantPol rInSiblingRkey;
    ConstantPol rInSiblingValueHash;
    ConstantPol rSetHashLeft;
    ConstantPol rSetHashRight;
    ConstantPol rSetLevel;
    ConstantPol rSetNewRoot;
    ConstantPol rSetOldRoot;
    ConstantPol rSetRkey;
    ConstantPol rSetRkeyBit;
    ConstantPol rSetSiblingRkey;
    ConstantPol rSetSiblingValueHash;
    ConstantPol rSetValueHigh;
    ConstantPol rSetValueLow;
private:
    void * _pAddress;
    uint64_t _degree;
public:

    StorageConstantPols (void * pAddress, uint64_t degree) :
        rHash((Goldilocks::Element *)((uint8_t *)pAddress + 1520), degree, 190),
        rHashType((Goldilocks::Element *)((uint8_t *)pAddress + 1528), degree, 191),
        rLatchGet((Goldilocks::Element *)((uint8_t *)pAddress + 1536), degree, 192),
        rLatchSet((Goldilocks::Element *)((uint8_t *)pAddress + 1544), degree, 193),
        rClimbRkey((Goldilocks::Element *)((uint8_t *)pAddress + 1552), degree, 194),
        rClimbSiblingRkey((Goldilocks::Element *)((uint8_t *)pAddress + 1560), degree, 195),
        rClimbSiblingRkeyN((Goldilocks::Element *)((uint8_t *)pAddress + 1568), degree, 196),
        rRotateLevel((Goldilocks::Element *)((uint8_t *)pAddress + 1576), degree, 197),
        rJmpz((Goldilocks::Element *)((uint8_t *)pAddress + 1584), degree, 198),
        rJmp((Goldilocks::Element *)((uint8_t *)pAddress + 1592), degree, 199),
        rConst0((Goldilocks::Element *)((uint8_t *)pAddress + 1600), degree, 200),
        rConst1((Goldilocks::Element *)((uint8_t *)pAddress + 1608), degree, 201),
        rConst2((Goldilocks::Element *)((uint8_t *)pAddress + 1616), degree, 202),
        rConst3((Goldilocks::Element *)((uint8_t *)pAddress + 1624), degree, 203),
        rAddress((Goldilocks::Element *)((uint8_t *)pAddress + 1632), degree, 204),
        rLine((Goldilocks::Element *)((uint8_t *)pAddress + 1640), degree, 205),
        rInFree((Goldilocks::Element *)((uint8_t *)pAddress + 1648), degree, 206),
        rInNewRoot((Goldilocks::Element *)((uint8_t *)pAddress + 1656), degree, 207),
        rInOldRoot((Goldilocks::Element *)((uint8_t *)pAddress + 1664), degree, 208),
        rInRkey((Goldilocks::Element *)((uint8_t *)pAddress + 1672), degree, 209),
        rInRkeyBit((Goldilocks::Element *)((uint8_t *)pAddress + 1680), degree, 210),
        rInSiblingRkey((Goldilocks::Element *)((uint8_t *)pAddress + 1688), degree, 211),
        rInSiblingValueHash((Goldilocks::Element *)((uint8_t *)pAddress + 1696), degree, 212),
        rSetHashLeft((Goldilocks::Element *)((uint8_t *)pAddress + 1704), degree, 213),
        rSetHashRight((Goldilocks::Element *)((uint8_t *)pAddress + 1712), degree, 214),
        rSetLevel((Goldilocks::Element *)((uint8_t *)pAddress + 1720), degree, 215),
        rSetNewRoot((Goldilocks::Element *)((uint8_t *)pAddress + 1728), degree, 216),
        rSetOldRoot((Goldilocks::Element *)((uint8_t *)pAddress + 1736), degree, 217),
        rSetRkey((Goldilocks::Element *)((uint8_t *)pAddress + 1744), degree, 218),
        rSetRkeyBit((Goldilocks::Element *)((uint8_t *)pAddress + 1752), degree, 219),
        rSetSiblingRkey((Goldilocks::Element *)((uint8_t *)pAddress + 1760), degree, 220),
        rSetSiblingValueHash((Goldilocks::Element *)((uint8_t *)pAddress + 1768), degree, 221),
        rSetValueHigh((Goldilocks::Element *)((uint8_t *)pAddress + 1776), degree, 222),
        rSetValueLow((Goldilocks::Element *)((uint8_t *)pAddress + 1784), degree, 223),
        _pAddress(pAddress),
        _degree(degree) {};

    static uint64_t pilDegree (void) { return 8388608; }
    static uint64_t pilSize (void) { return 272; }
    static uint64_t numPols (void) { return 34; }

    void * address (void) { return _pAddress; }
    uint64_t degree (void) { return _degree; }
    uint64_t size (void) { return _degree*34*sizeof(Goldilocks::Element); }
};

class KeccakFConstantPols
{
public:
    ConstantPol ConnA;
    ConstantPol ConnB;
    ConstantPol ConnC;
    ConstantPol GateType;
    ConstantPol kGateType;
    ConstantPol kA;
    ConstantPol kB;
    ConstantPol kC;
private:
    void * _pAddress;
    uint64_t _degree;
public:

    KeccakFConstantPols (void * pAddress, uint64_t degree) :
        ConnA((Goldilocks::Element *)((uint8_t *)pAddress + 1792), degree, 224),
        ConnB((Goldilocks::Element *)((uint8_t *)pAddress + 1800), degree, 225),
        ConnC((Goldilocks::Element *)((uint8_t *)pAddress + 1808), degree, 226),
        GateType((Goldilocks::Element *)((uint8_t *)pAddress + 1816), degree, 227),
        kGateType((Goldilocks::Element *)((uint8_t *)pAddress + 1824), degree, 228),
        kA((Goldilocks::Element *)((uint8_t *)pAddress + 1832), degree, 229),
        kB((Goldilocks::Element *)((uint8_t *)pAddress + 1840), degree, 230),
        kC((Goldilocks::Element *)((uint8_t *)pAddress + 1848), degree, 231),
        _pAddress(pAddress),
        _degree(degree) {};

    static uint64_t pilDegree (void) { return 8388608; }
    static uint64_t pilSize (void) { return 64; }
    static uint64_t numPols (void) { return 8; }

    void * address (void) { return _pAddress; }
    uint64_t degree (void) { return _degree; }
    uint64_t size (void) { return _degree*8*sizeof(Goldilocks::Element); }
};

class Nine2OneConstantPols
{
public:
    ConstantPol Field9latch;
    ConstantPol Factor;
private:
    void * _pAddress;
    uint64_t _degree;
public:

    Nine2OneConstantPols (void * pAddress, uint64_t degree) :
        Field9latch((Goldilocks::Element *)((uint8_t *)pAddress + 1856), degree, 232),
        Factor((Goldilocks::Element *)((uint8_t *)pAddress + 1864), degree, 233),
        _pAddress(pAddress),
        _degree(degree) {};

    static uint64_t pilDegree (void) { return 8388608; }
    static uint64_t pilSize (void) { return 16; }
    static uint64_t numPols (void) { return 2; }

    void * address (void) { return _pAddress; }
    uint64_t degree (void) { return _degree; }
    uint64_t size (void) { return _degree*2*sizeof(Goldilocks::Element); }
};

class PaddingKKBitConstantPols
{
public:
    ConstantPol r8Id;
    ConstantPol sOutId;
    ConstantPol latchR8;
    ConstantPol Fr8;
    ConstantPol rBitValid;
    ConstantPol latchSOut;
    ConstantPol FSOut0;
    ConstantPol FSOut1;
    ConstantPol FSOut2;
    ConstantPol FSOut3;
    ConstantPol FSOut4;
    ConstantPol FSOut5;
    ConstantPol FSOut6;
    ConstantPol FSOut7;
    ConstantPol ConnSOutBit;
    ConstantPol ConnSInBit;
    ConstantPol ConnNine2OneBit;
private:
    void * _pAddress;
    uint64_t _degree;
public:

    PaddingKKBitConstantPols (void * pAddress, uint64_t degree) :
        r8Id((Goldilocks::Element *)((uint8_t *)pAddress + 1872), degree, 234),
        sOutId((Goldilocks::Element *)((uint8_t *)pAddress + 1880), degree, 235),
        latchR8((Goldilocks::Element *)((uint8_t *)pAddress + 1888), degree, 236),
        Fr8((Goldilocks::Element *)((uint8_t *)pAddress + 1896), degree, 237),
        rBitValid((Goldilocks::Element *)((uint8_t *)pAddress + 1904), degree, 238),
        latchSOut((Goldilocks::Element *)((uint8_t *)pAddress + 1912), degree, 239),
        FSOut0((Goldilocks::Element *)((uint8_t *)pAddress + 1920), degree, 240),
        FSOut1((Goldilocks::Element *)((uint8_t *)pAddress + 1928), degree, 241),
        FSOut2((Goldilocks::Element *)((uint8_t *)pAddress + 1936), degree, 242),
        FSOut3((Goldilocks::Element *)((uint8_t *)pAddress + 1944), degree, 243),
        FSOut4((Goldilocks::Element *)((uint8_t *)pAddress + 1952), degree, 244),
        FSOut5((Goldilocks::Element *)((uint8_t *)pAddress + 1960), degree, 245),
        FSOut6((Goldilocks::Element *)((uint8_t *)pAddress + 1968), degree, 246),
        FSOut7((Goldilocks::Element *)((uint8_t *)pAddress + 1976), degree, 247),
        ConnSOutBit((Goldilocks::Element *)((uint8_t *)pAddress + 1984), degree, 248),
        ConnSInBit((Goldilocks::Element *)((uint8_t *)pAddress + 1992), degree, 249),
        ConnNine2OneBit((Goldilocks::Element *)((uint8_t *)pAddress + 2000), degree, 250),
        _pAddress(pAddress),
        _degree(degree) {};

    static uint64_t pilDegree (void) { return 8388608; }
    static uint64_t pilSize (void) { return 136; }
    static uint64_t numPols (void) { return 17; }

    void * address (void) { return _pAddress; }
    uint64_t degree (void) { return _degree; }
    uint64_t size (void) { return _degree*17*sizeof(Goldilocks::Element); }
};

class PaddingKKConstantPols
{
public:
    ConstantPol r8Id;
    ConstantPol lastBlock;
    ConstantPol lastBlockLatch;
    ConstantPol r8valid;
    ConstantPol sOutId;
    ConstantPol forceLastHash;
    ConstantPol k_crOffset;
    ConstantPol k_crF0;
    ConstantPol k_crF1;
    ConstantPol k_crF2;
    ConstantPol k_crF3;
    ConstantPol k_crF4;
    ConstantPol k_crF5;
    ConstantPol k_crF6;
    ConstantPol k_crF7;
    ConstantPol crValid;
private:
    void * _pAddress;
    uint64_t _degree;
public:

    PaddingKKConstantPols (void * pAddress, uint64_t degree) :
        r8Id((Goldilocks::Element *)((uint8_t *)pAddress + 2008), degree, 251),
        lastBlock((Goldilocks::Element *)((uint8_t *)pAddress + 2016), degree, 252),
        lastBlockLatch((Goldilocks::Element *)((uint8_t *)pAddress + 2024), degree, 253),
        r8valid((Goldilocks::Element *)((uint8_t *)pAddress + 2032), degree, 254),
        sOutId((Goldilocks::Element *)((uint8_t *)pAddress + 2040), degree, 255),
        forceLastHash((Goldilocks::Element *)((uint8_t *)pAddress + 2048), degree, 256),
        k_crOffset((Goldilocks::Element *)((uint8_t *)pAddress + 2056), degree, 257),
        k_crF0((Goldilocks::Element *)((uint8_t *)pAddress + 2064), degree, 258),
        k_crF1((Goldilocks::Element *)((uint8_t *)pAddress + 2072), degree, 259),
        k_crF2((Goldilocks::Element *)((uint8_t *)pAddress + 2080), degree, 260),
        k_crF3((Goldilocks::Element *)((uint8_t *)pAddress + 2088), degree, 261),
        k_crF4((Goldilocks::Element *)((uint8_t *)pAddress + 2096), degree, 262),
        k_crF5((Goldilocks::Element *)((uint8_t *)pAddress + 2104), degree, 263),
        k_crF6((Goldilocks::Element *)((uint8_t *)pAddress + 2112), degree, 264),
        k_crF7((Goldilocks::Element *)((uint8_t *)pAddress + 2120), degree, 265),
        crValid((Goldilocks::Element *)((uint8_t *)pAddress + 2128), degree, 266),
        _pAddress(pAddress),
        _degree(degree) {};

    static uint64_t pilDegree (void) { return 8388608; }
    static uint64_t pilSize (void) { return 128; }
    static uint64_t numPols (void) { return 16; }

    void * address (void) { return _pAddress; }
    uint64_t degree (void) { return _degree; }
    uint64_t size (void) { return _degree*16*sizeof(Goldilocks::Element); }
};

class MemConstantPols
{
public:
    ConstantPol INCS;
    ConstantPol ISNOTLAST;
private:
    void * _pAddress;
    uint64_t _degree;
public:

    MemConstantPols (void * pAddress, uint64_t degree) :
        INCS((Goldilocks::Element *)((uint8_t *)pAddress + 2136), degree, 267),
        ISNOTLAST((Goldilocks::Element *)((uint8_t *)pAddress + 2144), degree, 268),
        _pAddress(pAddress),
        _degree(degree) {};

    static uint64_t pilDegree (void) { return 8388608; }
    static uint64_t pilSize (void) { return 16; }
    static uint64_t numPols (void) { return 2; }

    void * address (void) { return _pAddress; }
    uint64_t degree (void) { return _degree; }
    uint64_t size (void) { return _degree*2*sizeof(Goldilocks::Element); }
};

class MainConstantPols
{
public:
    ConstantPol STEP;
private:
    void * _pAddress;
    uint64_t _degree;
public:

    MainConstantPols (void * pAddress, uint64_t degree) :
        STEP((Goldilocks::Element *)((uint8_t *)pAddress + 2152), degree, 269),
        _pAddress(pAddress),
        _degree(degree) {};

    static uint64_t pilDegree (void) { return 8388608; }
    static uint64_t pilSize (void) { return 8; }
    static uint64_t numPols (void) { return 1; }

    void * address (void) { return _pAddress; }
    uint64_t degree (void) { return _degree; }
    uint64_t size (void) { return _degree*1*sizeof(Goldilocks::Element); }
};

class ConstantPols
{
public:
    GlobalConstantPols Global;
    RomConstantPols Rom;
    Byte4ConstantPols Byte4;
    MemAlignConstantPols MemAlign;
    ArithConstantPols Arith;
    BinaryConstantPols Binary;
    PoseidonGConstantPols PoseidonG;
    PaddingPGConstantPols PaddingPG;
    StorageConstantPols Storage;
    KeccakFConstantPols KeccakF;
    Nine2OneConstantPols Nine2One;
    PaddingKKBitConstantPols PaddingKKBit;
    PaddingKKConstantPols PaddingKK;
    MemConstantPols Mem;
    MainConstantPols Main;
private:
    void * _pAddress;
    uint64_t _degree;
public:

    ConstantPols (void * pAddress, uint64_t degree) :
        Global(pAddress, degree),
        Rom(pAddress, degree),
        Byte4(pAddress, degree),
        MemAlign(pAddress, degree),
        Arith(pAddress, degree),
        Binary(pAddress, degree),
        PoseidonG(pAddress, degree),
        PaddingPG(pAddress, degree),
        Storage(pAddress, degree),
        KeccakF(pAddress, degree),
        Nine2One(pAddress, degree),
        PaddingKKBit(pAddress, degree),
        PaddingKK(pAddress, degree),
        Mem(pAddress, degree),
        Main(pAddress, degree),
        _pAddress(pAddress),
        _degree(degree) {}

    static uint64_t pilSize (void) { return 18119393280; }
    static uint64_t pilDegree (void) { return 8388608; }
    static uint64_t numPols (void) { return 270; }

    void * address (void) { return _pAddress; }
    uint64_t degree (void) { return _degree; }
    uint64_t size (void) { return _degree*270*sizeof(Goldilocks::Element); }

    Goldilocks::Element &getElement (uint64_t pol, uint64_t evaluation)
    {
        zkassert((pol < numPols()) && (evaluation < degree()));
        return ((Goldilocks::Element *)_pAddress)[pol + evaluation * numPols()];
    }
};

#endif // CONSTANT_POLS_HPP
