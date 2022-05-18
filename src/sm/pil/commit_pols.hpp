#ifndef COMMIT_POLS_HPP
#define COMMIT_POLS_HPP

#include <cstdint>
#include "ff/ff.hpp"

class Byte4CommitPols
{
public:
    uint16_t * freeIN;
    uint32_t * out;

    Byte4CommitPols (void * pAddress)
    {
        freeIN = (uint16_t *)((uint8_t *)pAddress + 0);
        out = (uint32_t *)((uint8_t *)pAddress + 8388608);
    }

    Byte4CommitPols (void * pAddress, uint64_t degree)
    {
        freeIN = (uint16_t *)((uint8_t *)pAddress + 0);
        out = (uint32_t *)((uint8_t *)pAddress + 4);
    }

    static uint64_t degree (void) { return 4194304; }
    static uint64_t size (void) { return 20; }
};

class MemAlignCommitPols
{
public:
    uint8_t * inM;
    uint8_t * inV;
    uint8_t * wr;
    uint32_t * m0[8];
    uint32_t * m1[8];
    uint32_t * w0[8];
    uint32_t * w1[8];
    uint32_t * v[8];
    uint8_t * offset;
    uint8_t * selW;
    FieldElement * factorV[8];

    MemAlignCommitPols (void * pAddress)
    {
        inM = (uint8_t *)((uint8_t *)pAddress + 41943040);
        inV = (uint8_t *)((uint8_t *)pAddress + 46137344);
        wr = (uint8_t *)((uint8_t *)pAddress + 50331648);
        m0[0] = (uint32_t *)((uint8_t *)pAddress + 54525952);
        m0[1] = (uint32_t *)((uint8_t *)pAddress + 88080384);
        m0[2] = (uint32_t *)((uint8_t *)pAddress + 121634816);
        m0[3] = (uint32_t *)((uint8_t *)pAddress + 155189248);
        m0[4] = (uint32_t *)((uint8_t *)pAddress + 188743680);
        m0[5] = (uint32_t *)((uint8_t *)pAddress + 222298112);
        m0[6] = (uint32_t *)((uint8_t *)pAddress + 255852544);
        m0[7] = (uint32_t *)((uint8_t *)pAddress + 289406976);
        m1[0] = (uint32_t *)((uint8_t *)pAddress + 322961408);
        m1[1] = (uint32_t *)((uint8_t *)pAddress + 356515840);
        m1[2] = (uint32_t *)((uint8_t *)pAddress + 390070272);
        m1[3] = (uint32_t *)((uint8_t *)pAddress + 423624704);
        m1[4] = (uint32_t *)((uint8_t *)pAddress + 457179136);
        m1[5] = (uint32_t *)((uint8_t *)pAddress + 490733568);
        m1[6] = (uint32_t *)((uint8_t *)pAddress + 524288000);
        m1[7] = (uint32_t *)((uint8_t *)pAddress + 557842432);
        w0[0] = (uint32_t *)((uint8_t *)pAddress + 591396864);
        w0[1] = (uint32_t *)((uint8_t *)pAddress + 624951296);
        w0[2] = (uint32_t *)((uint8_t *)pAddress + 658505728);
        w0[3] = (uint32_t *)((uint8_t *)pAddress + 692060160);
        w0[4] = (uint32_t *)((uint8_t *)pAddress + 725614592);
        w0[5] = (uint32_t *)((uint8_t *)pAddress + 759169024);
        w0[6] = (uint32_t *)((uint8_t *)pAddress + 792723456);
        w0[7] = (uint32_t *)((uint8_t *)pAddress + 826277888);
        w1[0] = (uint32_t *)((uint8_t *)pAddress + 859832320);
        w1[1] = (uint32_t *)((uint8_t *)pAddress + 893386752);
        w1[2] = (uint32_t *)((uint8_t *)pAddress + 926941184);
        w1[3] = (uint32_t *)((uint8_t *)pAddress + 960495616);
        w1[4] = (uint32_t *)((uint8_t *)pAddress + 994050048);
        w1[5] = (uint32_t *)((uint8_t *)pAddress + 1027604480);
        w1[6] = (uint32_t *)((uint8_t *)pAddress + 1061158912);
        w1[7] = (uint32_t *)((uint8_t *)pAddress + 1094713344);
        v[0] = (uint32_t *)((uint8_t *)pAddress + 1128267776);
        v[1] = (uint32_t *)((uint8_t *)pAddress + 1161822208);
        v[2] = (uint32_t *)((uint8_t *)pAddress + 1195376640);
        v[3] = (uint32_t *)((uint8_t *)pAddress + 1228931072);
        v[4] = (uint32_t *)((uint8_t *)pAddress + 1262485504);
        v[5] = (uint32_t *)((uint8_t *)pAddress + 1296039936);
        v[6] = (uint32_t *)((uint8_t *)pAddress + 1329594368);
        v[7] = (uint32_t *)((uint8_t *)pAddress + 1363148800);
        offset = (uint8_t *)((uint8_t *)pAddress + 1396703232);
        selW = (uint8_t *)((uint8_t *)pAddress + 1400897536);
        factorV[0] = (FieldElement *)((uint8_t *)pAddress + 1405091840);
        factorV[1] = (FieldElement *)((uint8_t *)pAddress + 1438646272);
        factorV[2] = (FieldElement *)((uint8_t *)pAddress + 1472200704);
        factorV[3] = (FieldElement *)((uint8_t *)pAddress + 1505755136);
        factorV[4] = (FieldElement *)((uint8_t *)pAddress + 1539309568);
        factorV[5] = (FieldElement *)((uint8_t *)pAddress + 1572864000);
        factorV[6] = (FieldElement *)((uint8_t *)pAddress + 1606418432);
        factorV[7] = (FieldElement *)((uint8_t *)pAddress + 1639972864);
    }

    MemAlignCommitPols (void * pAddress, uint64_t degree)
    {
        inM = (uint8_t *)((uint8_t *)pAddress + 0);
        inV = (uint8_t *)((uint8_t *)pAddress + 2);
        wr = (uint8_t *)((uint8_t *)pAddress + 4);
        m0[0] = (uint32_t *)((uint8_t *)pAddress + 6);
        m0[1] = (uint32_t *)((uint8_t *)pAddress + 22);
        m0[2] = (uint32_t *)((uint8_t *)pAddress + 38);
        m0[3] = (uint32_t *)((uint8_t *)pAddress + 54);
        m0[4] = (uint32_t *)((uint8_t *)pAddress + 70);
        m0[5] = (uint32_t *)((uint8_t *)pAddress + 86);
        m0[6] = (uint32_t *)((uint8_t *)pAddress + 102);
        m0[7] = (uint32_t *)((uint8_t *)pAddress + 118);
        m1[0] = (uint32_t *)((uint8_t *)pAddress + 134);
        m1[1] = (uint32_t *)((uint8_t *)pAddress + 150);
        m1[2] = (uint32_t *)((uint8_t *)pAddress + 166);
        m1[3] = (uint32_t *)((uint8_t *)pAddress + 182);
        m1[4] = (uint32_t *)((uint8_t *)pAddress + 198);
        m1[5] = (uint32_t *)((uint8_t *)pAddress + 214);
        m1[6] = (uint32_t *)((uint8_t *)pAddress + 230);
        m1[7] = (uint32_t *)((uint8_t *)pAddress + 246);
        w0[0] = (uint32_t *)((uint8_t *)pAddress + 262);
        w0[1] = (uint32_t *)((uint8_t *)pAddress + 278);
        w0[2] = (uint32_t *)((uint8_t *)pAddress + 294);
        w0[3] = (uint32_t *)((uint8_t *)pAddress + 310);
        w0[4] = (uint32_t *)((uint8_t *)pAddress + 326);
        w0[5] = (uint32_t *)((uint8_t *)pAddress + 342);
        w0[6] = (uint32_t *)((uint8_t *)pAddress + 358);
        w0[7] = (uint32_t *)((uint8_t *)pAddress + 374);
        w1[0] = (uint32_t *)((uint8_t *)pAddress + 390);
        w1[1] = (uint32_t *)((uint8_t *)pAddress + 406);
        w1[2] = (uint32_t *)((uint8_t *)pAddress + 422);
        w1[3] = (uint32_t *)((uint8_t *)pAddress + 438);
        w1[4] = (uint32_t *)((uint8_t *)pAddress + 454);
        w1[5] = (uint32_t *)((uint8_t *)pAddress + 470);
        w1[6] = (uint32_t *)((uint8_t *)pAddress + 486);
        w1[7] = (uint32_t *)((uint8_t *)pAddress + 502);
        v[0] = (uint32_t *)((uint8_t *)pAddress + 518);
        v[1] = (uint32_t *)((uint8_t *)pAddress + 534);
        v[2] = (uint32_t *)((uint8_t *)pAddress + 550);
        v[3] = (uint32_t *)((uint8_t *)pAddress + 566);
        v[4] = (uint32_t *)((uint8_t *)pAddress + 582);
        v[5] = (uint32_t *)((uint8_t *)pAddress + 598);
        v[6] = (uint32_t *)((uint8_t *)pAddress + 614);
        v[7] = (uint32_t *)((uint8_t *)pAddress + 630);
        offset = (uint8_t *)((uint8_t *)pAddress + 646);
        selW = (uint8_t *)((uint8_t *)pAddress + 648);
        factorV[0] = (FieldElement *)((uint8_t *)pAddress + 650);
        factorV[1] = (FieldElement *)((uint8_t *)pAddress + 666);
        factorV[2] = (FieldElement *)((uint8_t *)pAddress + 682);
        factorV[3] = (FieldElement *)((uint8_t *)pAddress + 698);
        factorV[4] = (FieldElement *)((uint8_t *)pAddress + 714);
        factorV[5] = (FieldElement *)((uint8_t *)pAddress + 730);
        factorV[6] = (FieldElement *)((uint8_t *)pAddress + 746);
        factorV[7] = (FieldElement *)((uint8_t *)pAddress + 762);
    }

    static uint64_t degree (void) { return 4194304; }
    static uint64_t size (void) { return 778; }
};

class ArithCommitPols
{
public:
    FieldElement * x1[16];
    FieldElement * y1[16];
    FieldElement * x2[16];
    FieldElement * y2[16];
    FieldElement * x3[16];
    FieldElement * y3[16];
    FieldElement * s[16];
    FieldElement * q0[16];
    FieldElement * q1[16];
    FieldElement * q2[16];
    FieldElement * selEq[4];
    FieldElement * carryL[3];
    FieldElement * carryH[3];

    ArithCommitPols (void * pAddress)
    {
        x1[0] = (FieldElement *)((uint8_t *)pAddress + 1673527296);
        x1[1] = (FieldElement *)((uint8_t *)pAddress + 1707081728);
        x1[2] = (FieldElement *)((uint8_t *)pAddress + 1740636160);
        x1[3] = (FieldElement *)((uint8_t *)pAddress + 1774190592);
        x1[4] = (FieldElement *)((uint8_t *)pAddress + 1807745024);
        x1[5] = (FieldElement *)((uint8_t *)pAddress + 1841299456);
        x1[6] = (FieldElement *)((uint8_t *)pAddress + 1874853888);
        x1[7] = (FieldElement *)((uint8_t *)pAddress + 1908408320);
        x1[8] = (FieldElement *)((uint8_t *)pAddress + 1941962752);
        x1[9] = (FieldElement *)((uint8_t *)pAddress + 1975517184);
        x1[10] = (FieldElement *)((uint8_t *)pAddress + 2009071616);
        x1[11] = (FieldElement *)((uint8_t *)pAddress + 2042626048);
        x1[12] = (FieldElement *)((uint8_t *)pAddress + 2076180480);
        x1[13] = (FieldElement *)((uint8_t *)pAddress + 2109734912);
        x1[14] = (FieldElement *)((uint8_t *)pAddress + 2143289344);
        x1[15] = (FieldElement *)((uint8_t *)pAddress + 2176843776);
        y1[0] = (FieldElement *)((uint8_t *)pAddress + 2210398208);
        y1[1] = (FieldElement *)((uint8_t *)pAddress + 2243952640);
        y1[2] = (FieldElement *)((uint8_t *)pAddress + 2277507072);
        y1[3] = (FieldElement *)((uint8_t *)pAddress + 2311061504);
        y1[4] = (FieldElement *)((uint8_t *)pAddress + 2344615936);
        y1[5] = (FieldElement *)((uint8_t *)pAddress + 2378170368);
        y1[6] = (FieldElement *)((uint8_t *)pAddress + 2411724800);
        y1[7] = (FieldElement *)((uint8_t *)pAddress + 2445279232);
        y1[8] = (FieldElement *)((uint8_t *)pAddress + 2478833664);
        y1[9] = (FieldElement *)((uint8_t *)pAddress + 2512388096);
        y1[10] = (FieldElement *)((uint8_t *)pAddress + 2545942528);
        y1[11] = (FieldElement *)((uint8_t *)pAddress + 2579496960);
        y1[12] = (FieldElement *)((uint8_t *)pAddress + 2613051392);
        y1[13] = (FieldElement *)((uint8_t *)pAddress + 2646605824);
        y1[14] = (FieldElement *)((uint8_t *)pAddress + 2680160256);
        y1[15] = (FieldElement *)((uint8_t *)pAddress + 2713714688);
        x2[0] = (FieldElement *)((uint8_t *)pAddress + 2747269120);
        x2[1] = (FieldElement *)((uint8_t *)pAddress + 2780823552);
        x2[2] = (FieldElement *)((uint8_t *)pAddress + 2814377984);
        x2[3] = (FieldElement *)((uint8_t *)pAddress + 2847932416);
        x2[4] = (FieldElement *)((uint8_t *)pAddress + 2881486848);
        x2[5] = (FieldElement *)((uint8_t *)pAddress + 2915041280);
        x2[6] = (FieldElement *)((uint8_t *)pAddress + 2948595712);
        x2[7] = (FieldElement *)((uint8_t *)pAddress + 2982150144);
        x2[8] = (FieldElement *)((uint8_t *)pAddress + 3015704576);
        x2[9] = (FieldElement *)((uint8_t *)pAddress + 3049259008);
        x2[10] = (FieldElement *)((uint8_t *)pAddress + 3082813440);
        x2[11] = (FieldElement *)((uint8_t *)pAddress + 3116367872);
        x2[12] = (FieldElement *)((uint8_t *)pAddress + 3149922304);
        x2[13] = (FieldElement *)((uint8_t *)pAddress + 3183476736);
        x2[14] = (FieldElement *)((uint8_t *)pAddress + 3217031168);
        x2[15] = (FieldElement *)((uint8_t *)pAddress + 3250585600);
        y2[0] = (FieldElement *)((uint8_t *)pAddress + 3284140032);
        y2[1] = (FieldElement *)((uint8_t *)pAddress + 3317694464);
        y2[2] = (FieldElement *)((uint8_t *)pAddress + 3351248896);
        y2[3] = (FieldElement *)((uint8_t *)pAddress + 3384803328);
        y2[4] = (FieldElement *)((uint8_t *)pAddress + 3418357760);
        y2[5] = (FieldElement *)((uint8_t *)pAddress + 3451912192);
        y2[6] = (FieldElement *)((uint8_t *)pAddress + 3485466624);
        y2[7] = (FieldElement *)((uint8_t *)pAddress + 3519021056);
        y2[8] = (FieldElement *)((uint8_t *)pAddress + 3552575488);
        y2[9] = (FieldElement *)((uint8_t *)pAddress + 3586129920);
        y2[10] = (FieldElement *)((uint8_t *)pAddress + 3619684352);
        y2[11] = (FieldElement *)((uint8_t *)pAddress + 3653238784);
        y2[12] = (FieldElement *)((uint8_t *)pAddress + 3686793216);
        y2[13] = (FieldElement *)((uint8_t *)pAddress + 3720347648);
        y2[14] = (FieldElement *)((uint8_t *)pAddress + 3753902080);
        y2[15] = (FieldElement *)((uint8_t *)pAddress + 3787456512);
        x3[0] = (FieldElement *)((uint8_t *)pAddress + 3821010944);
        x3[1] = (FieldElement *)((uint8_t *)pAddress + 3854565376);
        x3[2] = (FieldElement *)((uint8_t *)pAddress + 3888119808);
        x3[3] = (FieldElement *)((uint8_t *)pAddress + 3921674240);
        x3[4] = (FieldElement *)((uint8_t *)pAddress + 3955228672);
        x3[5] = (FieldElement *)((uint8_t *)pAddress + 3988783104);
        x3[6] = (FieldElement *)((uint8_t *)pAddress + 4022337536);
        x3[7] = (FieldElement *)((uint8_t *)pAddress + 4055891968);
        x3[8] = (FieldElement *)((uint8_t *)pAddress + 4089446400);
        x3[9] = (FieldElement *)((uint8_t *)pAddress + 4123000832);
        x3[10] = (FieldElement *)((uint8_t *)pAddress + 4156555264);
        x3[11] = (FieldElement *)((uint8_t *)pAddress + 4190109696);
        x3[12] = (FieldElement *)((uint8_t *)pAddress + 4223664128);
        x3[13] = (FieldElement *)((uint8_t *)pAddress + 4257218560);
        x3[14] = (FieldElement *)((uint8_t *)pAddress + 4290772992);
        x3[15] = (FieldElement *)((uint8_t *)pAddress + 4324327424);
        y3[0] = (FieldElement *)((uint8_t *)pAddress + 4357881856);
        y3[1] = (FieldElement *)((uint8_t *)pAddress + 4391436288);
        y3[2] = (FieldElement *)((uint8_t *)pAddress + 4424990720);
        y3[3] = (FieldElement *)((uint8_t *)pAddress + 4458545152);
        y3[4] = (FieldElement *)((uint8_t *)pAddress + 4492099584);
        y3[5] = (FieldElement *)((uint8_t *)pAddress + 4525654016);
        y3[6] = (FieldElement *)((uint8_t *)pAddress + 4559208448);
        y3[7] = (FieldElement *)((uint8_t *)pAddress + 4592762880);
        y3[8] = (FieldElement *)((uint8_t *)pAddress + 4626317312);
        y3[9] = (FieldElement *)((uint8_t *)pAddress + 4659871744);
        y3[10] = (FieldElement *)((uint8_t *)pAddress + 4693426176);
        y3[11] = (FieldElement *)((uint8_t *)pAddress + 4726980608);
        y3[12] = (FieldElement *)((uint8_t *)pAddress + 4760535040);
        y3[13] = (FieldElement *)((uint8_t *)pAddress + 4794089472);
        y3[14] = (FieldElement *)((uint8_t *)pAddress + 4827643904);
        y3[15] = (FieldElement *)((uint8_t *)pAddress + 4861198336);
        s[0] = (FieldElement *)((uint8_t *)pAddress + 4894752768);
        s[1] = (FieldElement *)((uint8_t *)pAddress + 4928307200);
        s[2] = (FieldElement *)((uint8_t *)pAddress + 4961861632);
        s[3] = (FieldElement *)((uint8_t *)pAddress + 4995416064);
        s[4] = (FieldElement *)((uint8_t *)pAddress + 5028970496);
        s[5] = (FieldElement *)((uint8_t *)pAddress + 5062524928);
        s[6] = (FieldElement *)((uint8_t *)pAddress + 5096079360);
        s[7] = (FieldElement *)((uint8_t *)pAddress + 5129633792);
        s[8] = (FieldElement *)((uint8_t *)pAddress + 5163188224);
        s[9] = (FieldElement *)((uint8_t *)pAddress + 5196742656);
        s[10] = (FieldElement *)((uint8_t *)pAddress + 5230297088);
        s[11] = (FieldElement *)((uint8_t *)pAddress + 5263851520);
        s[12] = (FieldElement *)((uint8_t *)pAddress + 5297405952);
        s[13] = (FieldElement *)((uint8_t *)pAddress + 5330960384);
        s[14] = (FieldElement *)((uint8_t *)pAddress + 5364514816);
        s[15] = (FieldElement *)((uint8_t *)pAddress + 5398069248);
        q0[0] = (FieldElement *)((uint8_t *)pAddress + 5431623680);
        q0[1] = (FieldElement *)((uint8_t *)pAddress + 5465178112);
        q0[2] = (FieldElement *)((uint8_t *)pAddress + 5498732544);
        q0[3] = (FieldElement *)((uint8_t *)pAddress + 5532286976);
        q0[4] = (FieldElement *)((uint8_t *)pAddress + 5565841408);
        q0[5] = (FieldElement *)((uint8_t *)pAddress + 5599395840);
        q0[6] = (FieldElement *)((uint8_t *)pAddress + 5632950272);
        q0[7] = (FieldElement *)((uint8_t *)pAddress + 5666504704);
        q0[8] = (FieldElement *)((uint8_t *)pAddress + 5700059136);
        q0[9] = (FieldElement *)((uint8_t *)pAddress + 5733613568);
        q0[10] = (FieldElement *)((uint8_t *)pAddress + 5767168000);
        q0[11] = (FieldElement *)((uint8_t *)pAddress + 5800722432);
        q0[12] = (FieldElement *)((uint8_t *)pAddress + 5834276864);
        q0[13] = (FieldElement *)((uint8_t *)pAddress + 5867831296);
        q0[14] = (FieldElement *)((uint8_t *)pAddress + 5901385728);
        q0[15] = (FieldElement *)((uint8_t *)pAddress + 5934940160);
        q1[0] = (FieldElement *)((uint8_t *)pAddress + 5968494592);
        q1[1] = (FieldElement *)((uint8_t *)pAddress + 6002049024);
        q1[2] = (FieldElement *)((uint8_t *)pAddress + 6035603456);
        q1[3] = (FieldElement *)((uint8_t *)pAddress + 6069157888);
        q1[4] = (FieldElement *)((uint8_t *)pAddress + 6102712320);
        q1[5] = (FieldElement *)((uint8_t *)pAddress + 6136266752);
        q1[6] = (FieldElement *)((uint8_t *)pAddress + 6169821184);
        q1[7] = (FieldElement *)((uint8_t *)pAddress + 6203375616);
        q1[8] = (FieldElement *)((uint8_t *)pAddress + 6236930048);
        q1[9] = (FieldElement *)((uint8_t *)pAddress + 6270484480);
        q1[10] = (FieldElement *)((uint8_t *)pAddress + 6304038912);
        q1[11] = (FieldElement *)((uint8_t *)pAddress + 6337593344);
        q1[12] = (FieldElement *)((uint8_t *)pAddress + 6371147776);
        q1[13] = (FieldElement *)((uint8_t *)pAddress + 6404702208);
        q1[14] = (FieldElement *)((uint8_t *)pAddress + 6438256640);
        q1[15] = (FieldElement *)((uint8_t *)pAddress + 6471811072);
        q2[0] = (FieldElement *)((uint8_t *)pAddress + 6505365504);
        q2[1] = (FieldElement *)((uint8_t *)pAddress + 6538919936);
        q2[2] = (FieldElement *)((uint8_t *)pAddress + 6572474368);
        q2[3] = (FieldElement *)((uint8_t *)pAddress + 6606028800);
        q2[4] = (FieldElement *)((uint8_t *)pAddress + 6639583232);
        q2[5] = (FieldElement *)((uint8_t *)pAddress + 6673137664);
        q2[6] = (FieldElement *)((uint8_t *)pAddress + 6706692096);
        q2[7] = (FieldElement *)((uint8_t *)pAddress + 6740246528);
        q2[8] = (FieldElement *)((uint8_t *)pAddress + 6773800960);
        q2[9] = (FieldElement *)((uint8_t *)pAddress + 6807355392);
        q2[10] = (FieldElement *)((uint8_t *)pAddress + 6840909824);
        q2[11] = (FieldElement *)((uint8_t *)pAddress + 6874464256);
        q2[12] = (FieldElement *)((uint8_t *)pAddress + 6908018688);
        q2[13] = (FieldElement *)((uint8_t *)pAddress + 6941573120);
        q2[14] = (FieldElement *)((uint8_t *)pAddress + 6975127552);
        q2[15] = (FieldElement *)((uint8_t *)pAddress + 7008681984);
        selEq[0] = (FieldElement *)((uint8_t *)pAddress + 7042236416);
        selEq[1] = (FieldElement *)((uint8_t *)pAddress + 7075790848);
        selEq[2] = (FieldElement *)((uint8_t *)pAddress + 7109345280);
        selEq[3] = (FieldElement *)((uint8_t *)pAddress + 7142899712);
        carryL[0] = (FieldElement *)((uint8_t *)pAddress + 7176454144);
        carryL[1] = (FieldElement *)((uint8_t *)pAddress + 7210008576);
        carryL[2] = (FieldElement *)((uint8_t *)pAddress + 7243563008);
        carryH[0] = (FieldElement *)((uint8_t *)pAddress + 7277117440);
        carryH[1] = (FieldElement *)((uint8_t *)pAddress + 7310671872);
        carryH[2] = (FieldElement *)((uint8_t *)pAddress + 7344226304);
    }

    ArithCommitPols (void * pAddress, uint64_t degree)
    {
        x1[0] = (FieldElement *)((uint8_t *)pAddress + 0);
        x1[1] = (FieldElement *)((uint8_t *)pAddress + 16);
        x1[2] = (FieldElement *)((uint8_t *)pAddress + 32);
        x1[3] = (FieldElement *)((uint8_t *)pAddress + 48);
        x1[4] = (FieldElement *)((uint8_t *)pAddress + 64);
        x1[5] = (FieldElement *)((uint8_t *)pAddress + 80);
        x1[6] = (FieldElement *)((uint8_t *)pAddress + 96);
        x1[7] = (FieldElement *)((uint8_t *)pAddress + 112);
        x1[8] = (FieldElement *)((uint8_t *)pAddress + 128);
        x1[9] = (FieldElement *)((uint8_t *)pAddress + 144);
        x1[10] = (FieldElement *)((uint8_t *)pAddress + 160);
        x1[11] = (FieldElement *)((uint8_t *)pAddress + 176);
        x1[12] = (FieldElement *)((uint8_t *)pAddress + 192);
        x1[13] = (FieldElement *)((uint8_t *)pAddress + 208);
        x1[14] = (FieldElement *)((uint8_t *)pAddress + 224);
        x1[15] = (FieldElement *)((uint8_t *)pAddress + 240);
        y1[0] = (FieldElement *)((uint8_t *)pAddress + 256);
        y1[1] = (FieldElement *)((uint8_t *)pAddress + 272);
        y1[2] = (FieldElement *)((uint8_t *)pAddress + 288);
        y1[3] = (FieldElement *)((uint8_t *)pAddress + 304);
        y1[4] = (FieldElement *)((uint8_t *)pAddress + 320);
        y1[5] = (FieldElement *)((uint8_t *)pAddress + 336);
        y1[6] = (FieldElement *)((uint8_t *)pAddress + 352);
        y1[7] = (FieldElement *)((uint8_t *)pAddress + 368);
        y1[8] = (FieldElement *)((uint8_t *)pAddress + 384);
        y1[9] = (FieldElement *)((uint8_t *)pAddress + 400);
        y1[10] = (FieldElement *)((uint8_t *)pAddress + 416);
        y1[11] = (FieldElement *)((uint8_t *)pAddress + 432);
        y1[12] = (FieldElement *)((uint8_t *)pAddress + 448);
        y1[13] = (FieldElement *)((uint8_t *)pAddress + 464);
        y1[14] = (FieldElement *)((uint8_t *)pAddress + 480);
        y1[15] = (FieldElement *)((uint8_t *)pAddress + 496);
        x2[0] = (FieldElement *)((uint8_t *)pAddress + 512);
        x2[1] = (FieldElement *)((uint8_t *)pAddress + 528);
        x2[2] = (FieldElement *)((uint8_t *)pAddress + 544);
        x2[3] = (FieldElement *)((uint8_t *)pAddress + 560);
        x2[4] = (FieldElement *)((uint8_t *)pAddress + 576);
        x2[5] = (FieldElement *)((uint8_t *)pAddress + 592);
        x2[6] = (FieldElement *)((uint8_t *)pAddress + 608);
        x2[7] = (FieldElement *)((uint8_t *)pAddress + 624);
        x2[8] = (FieldElement *)((uint8_t *)pAddress + 640);
        x2[9] = (FieldElement *)((uint8_t *)pAddress + 656);
        x2[10] = (FieldElement *)((uint8_t *)pAddress + 672);
        x2[11] = (FieldElement *)((uint8_t *)pAddress + 688);
        x2[12] = (FieldElement *)((uint8_t *)pAddress + 704);
        x2[13] = (FieldElement *)((uint8_t *)pAddress + 720);
        x2[14] = (FieldElement *)((uint8_t *)pAddress + 736);
        x2[15] = (FieldElement *)((uint8_t *)pAddress + 752);
        y2[0] = (FieldElement *)((uint8_t *)pAddress + 768);
        y2[1] = (FieldElement *)((uint8_t *)pAddress + 784);
        y2[2] = (FieldElement *)((uint8_t *)pAddress + 800);
        y2[3] = (FieldElement *)((uint8_t *)pAddress + 816);
        y2[4] = (FieldElement *)((uint8_t *)pAddress + 832);
        y2[5] = (FieldElement *)((uint8_t *)pAddress + 848);
        y2[6] = (FieldElement *)((uint8_t *)pAddress + 864);
        y2[7] = (FieldElement *)((uint8_t *)pAddress + 880);
        y2[8] = (FieldElement *)((uint8_t *)pAddress + 896);
        y2[9] = (FieldElement *)((uint8_t *)pAddress + 912);
        y2[10] = (FieldElement *)((uint8_t *)pAddress + 928);
        y2[11] = (FieldElement *)((uint8_t *)pAddress + 944);
        y2[12] = (FieldElement *)((uint8_t *)pAddress + 960);
        y2[13] = (FieldElement *)((uint8_t *)pAddress + 976);
        y2[14] = (FieldElement *)((uint8_t *)pAddress + 992);
        y2[15] = (FieldElement *)((uint8_t *)pAddress + 1008);
        x3[0] = (FieldElement *)((uint8_t *)pAddress + 1024);
        x3[1] = (FieldElement *)((uint8_t *)pAddress + 1040);
        x3[2] = (FieldElement *)((uint8_t *)pAddress + 1056);
        x3[3] = (FieldElement *)((uint8_t *)pAddress + 1072);
        x3[4] = (FieldElement *)((uint8_t *)pAddress + 1088);
        x3[5] = (FieldElement *)((uint8_t *)pAddress + 1104);
        x3[6] = (FieldElement *)((uint8_t *)pAddress + 1120);
        x3[7] = (FieldElement *)((uint8_t *)pAddress + 1136);
        x3[8] = (FieldElement *)((uint8_t *)pAddress + 1152);
        x3[9] = (FieldElement *)((uint8_t *)pAddress + 1168);
        x3[10] = (FieldElement *)((uint8_t *)pAddress + 1184);
        x3[11] = (FieldElement *)((uint8_t *)pAddress + 1200);
        x3[12] = (FieldElement *)((uint8_t *)pAddress + 1216);
        x3[13] = (FieldElement *)((uint8_t *)pAddress + 1232);
        x3[14] = (FieldElement *)((uint8_t *)pAddress + 1248);
        x3[15] = (FieldElement *)((uint8_t *)pAddress + 1264);
        y3[0] = (FieldElement *)((uint8_t *)pAddress + 1280);
        y3[1] = (FieldElement *)((uint8_t *)pAddress + 1296);
        y3[2] = (FieldElement *)((uint8_t *)pAddress + 1312);
        y3[3] = (FieldElement *)((uint8_t *)pAddress + 1328);
        y3[4] = (FieldElement *)((uint8_t *)pAddress + 1344);
        y3[5] = (FieldElement *)((uint8_t *)pAddress + 1360);
        y3[6] = (FieldElement *)((uint8_t *)pAddress + 1376);
        y3[7] = (FieldElement *)((uint8_t *)pAddress + 1392);
        y3[8] = (FieldElement *)((uint8_t *)pAddress + 1408);
        y3[9] = (FieldElement *)((uint8_t *)pAddress + 1424);
        y3[10] = (FieldElement *)((uint8_t *)pAddress + 1440);
        y3[11] = (FieldElement *)((uint8_t *)pAddress + 1456);
        y3[12] = (FieldElement *)((uint8_t *)pAddress + 1472);
        y3[13] = (FieldElement *)((uint8_t *)pAddress + 1488);
        y3[14] = (FieldElement *)((uint8_t *)pAddress + 1504);
        y3[15] = (FieldElement *)((uint8_t *)pAddress + 1520);
        s[0] = (FieldElement *)((uint8_t *)pAddress + 1536);
        s[1] = (FieldElement *)((uint8_t *)pAddress + 1552);
        s[2] = (FieldElement *)((uint8_t *)pAddress + 1568);
        s[3] = (FieldElement *)((uint8_t *)pAddress + 1584);
        s[4] = (FieldElement *)((uint8_t *)pAddress + 1600);
        s[5] = (FieldElement *)((uint8_t *)pAddress + 1616);
        s[6] = (FieldElement *)((uint8_t *)pAddress + 1632);
        s[7] = (FieldElement *)((uint8_t *)pAddress + 1648);
        s[8] = (FieldElement *)((uint8_t *)pAddress + 1664);
        s[9] = (FieldElement *)((uint8_t *)pAddress + 1680);
        s[10] = (FieldElement *)((uint8_t *)pAddress + 1696);
        s[11] = (FieldElement *)((uint8_t *)pAddress + 1712);
        s[12] = (FieldElement *)((uint8_t *)pAddress + 1728);
        s[13] = (FieldElement *)((uint8_t *)pAddress + 1744);
        s[14] = (FieldElement *)((uint8_t *)pAddress + 1760);
        s[15] = (FieldElement *)((uint8_t *)pAddress + 1776);
        q0[0] = (FieldElement *)((uint8_t *)pAddress + 1792);
        q0[1] = (FieldElement *)((uint8_t *)pAddress + 1808);
        q0[2] = (FieldElement *)((uint8_t *)pAddress + 1824);
        q0[3] = (FieldElement *)((uint8_t *)pAddress + 1840);
        q0[4] = (FieldElement *)((uint8_t *)pAddress + 1856);
        q0[5] = (FieldElement *)((uint8_t *)pAddress + 1872);
        q0[6] = (FieldElement *)((uint8_t *)pAddress + 1888);
        q0[7] = (FieldElement *)((uint8_t *)pAddress + 1904);
        q0[8] = (FieldElement *)((uint8_t *)pAddress + 1920);
        q0[9] = (FieldElement *)((uint8_t *)pAddress + 1936);
        q0[10] = (FieldElement *)((uint8_t *)pAddress + 1952);
        q0[11] = (FieldElement *)((uint8_t *)pAddress + 1968);
        q0[12] = (FieldElement *)((uint8_t *)pAddress + 1984);
        q0[13] = (FieldElement *)((uint8_t *)pAddress + 2000);
        q0[14] = (FieldElement *)((uint8_t *)pAddress + 2016);
        q0[15] = (FieldElement *)((uint8_t *)pAddress + 2032);
        q1[0] = (FieldElement *)((uint8_t *)pAddress + 2048);
        q1[1] = (FieldElement *)((uint8_t *)pAddress + 2064);
        q1[2] = (FieldElement *)((uint8_t *)pAddress + 2080);
        q1[3] = (FieldElement *)((uint8_t *)pAddress + 2096);
        q1[4] = (FieldElement *)((uint8_t *)pAddress + 2112);
        q1[5] = (FieldElement *)((uint8_t *)pAddress + 2128);
        q1[6] = (FieldElement *)((uint8_t *)pAddress + 2144);
        q1[7] = (FieldElement *)((uint8_t *)pAddress + 2160);
        q1[8] = (FieldElement *)((uint8_t *)pAddress + 2176);
        q1[9] = (FieldElement *)((uint8_t *)pAddress + 2192);
        q1[10] = (FieldElement *)((uint8_t *)pAddress + 2208);
        q1[11] = (FieldElement *)((uint8_t *)pAddress + 2224);
        q1[12] = (FieldElement *)((uint8_t *)pAddress + 2240);
        q1[13] = (FieldElement *)((uint8_t *)pAddress + 2256);
        q1[14] = (FieldElement *)((uint8_t *)pAddress + 2272);
        q1[15] = (FieldElement *)((uint8_t *)pAddress + 2288);
        q2[0] = (FieldElement *)((uint8_t *)pAddress + 2304);
        q2[1] = (FieldElement *)((uint8_t *)pAddress + 2320);
        q2[2] = (FieldElement *)((uint8_t *)pAddress + 2336);
        q2[3] = (FieldElement *)((uint8_t *)pAddress + 2352);
        q2[4] = (FieldElement *)((uint8_t *)pAddress + 2368);
        q2[5] = (FieldElement *)((uint8_t *)pAddress + 2384);
        q2[6] = (FieldElement *)((uint8_t *)pAddress + 2400);
        q2[7] = (FieldElement *)((uint8_t *)pAddress + 2416);
        q2[8] = (FieldElement *)((uint8_t *)pAddress + 2432);
        q2[9] = (FieldElement *)((uint8_t *)pAddress + 2448);
        q2[10] = (FieldElement *)((uint8_t *)pAddress + 2464);
        q2[11] = (FieldElement *)((uint8_t *)pAddress + 2480);
        q2[12] = (FieldElement *)((uint8_t *)pAddress + 2496);
        q2[13] = (FieldElement *)((uint8_t *)pAddress + 2512);
        q2[14] = (FieldElement *)((uint8_t *)pAddress + 2528);
        q2[15] = (FieldElement *)((uint8_t *)pAddress + 2544);
        selEq[0] = (FieldElement *)((uint8_t *)pAddress + 2560);
        selEq[1] = (FieldElement *)((uint8_t *)pAddress + 2576);
        selEq[2] = (FieldElement *)((uint8_t *)pAddress + 2592);
        selEq[3] = (FieldElement *)((uint8_t *)pAddress + 2608);
        carryL[0] = (FieldElement *)((uint8_t *)pAddress + 2624);
        carryL[1] = (FieldElement *)((uint8_t *)pAddress + 2640);
        carryL[2] = (FieldElement *)((uint8_t *)pAddress + 2656);
        carryH[0] = (FieldElement *)((uint8_t *)pAddress + 2672);
        carryH[1] = (FieldElement *)((uint8_t *)pAddress + 2688);
        carryH[2] = (FieldElement *)((uint8_t *)pAddress + 2704);
    }

    static uint64_t degree (void) { return 4194304; }
    static uint64_t size (void) { return 2720; }
};

class BinaryCommitPols
{
public:
    uint8_t * freeInA;
    uint8_t * freeInB;
    uint8_t * freeInC;
    uint32_t * a0;
    uint32_t * a1;
    uint32_t * a2;
    uint32_t * a3;
    uint32_t * a4;
    uint32_t * a5;
    uint32_t * a6;
    uint32_t * a7;
    uint32_t * b0;
    uint32_t * b1;
    uint32_t * b2;
    uint32_t * b3;
    uint32_t * b4;
    uint32_t * b5;
    uint32_t * b6;
    uint32_t * b7;
    uint32_t * c0;
    uint32_t * c1;
    uint32_t * c2;
    uint32_t * c3;
    uint32_t * c4;
    uint32_t * c5;
    uint32_t * c6;
    uint32_t * c7;
    uint32_t * c0Temp;
    uint8_t * opcode;
    uint8_t * cIn;
    uint8_t * cOut;
    uint8_t * last;
    uint8_t * useCarry;

    BinaryCommitPols (void * pAddress)
    {
        freeInA = (uint8_t *)((uint8_t *)pAddress + 7377780736);
        freeInB = (uint8_t *)((uint8_t *)pAddress + 7381975040);
        freeInC = (uint8_t *)((uint8_t *)pAddress + 7386169344);
        a0 = (uint32_t *)((uint8_t *)pAddress + 7390363648);
        a1 = (uint32_t *)((uint8_t *)pAddress + 7423918080);
        a2 = (uint32_t *)((uint8_t *)pAddress + 7457472512);
        a3 = (uint32_t *)((uint8_t *)pAddress + 7491026944);
        a4 = (uint32_t *)((uint8_t *)pAddress + 7524581376);
        a5 = (uint32_t *)((uint8_t *)pAddress + 7558135808);
        a6 = (uint32_t *)((uint8_t *)pAddress + 7591690240);
        a7 = (uint32_t *)((uint8_t *)pAddress + 7625244672);
        b0 = (uint32_t *)((uint8_t *)pAddress + 7658799104);
        b1 = (uint32_t *)((uint8_t *)pAddress + 7692353536);
        b2 = (uint32_t *)((uint8_t *)pAddress + 7725907968);
        b3 = (uint32_t *)((uint8_t *)pAddress + 7759462400);
        b4 = (uint32_t *)((uint8_t *)pAddress + 7793016832);
        b5 = (uint32_t *)((uint8_t *)pAddress + 7826571264);
        b6 = (uint32_t *)((uint8_t *)pAddress + 7860125696);
        b7 = (uint32_t *)((uint8_t *)pAddress + 7893680128);
        c0 = (uint32_t *)((uint8_t *)pAddress + 7927234560);
        c1 = (uint32_t *)((uint8_t *)pAddress + 7960788992);
        c2 = (uint32_t *)((uint8_t *)pAddress + 7994343424);
        c3 = (uint32_t *)((uint8_t *)pAddress + 8027897856);
        c4 = (uint32_t *)((uint8_t *)pAddress + 8061452288);
        c5 = (uint32_t *)((uint8_t *)pAddress + 8095006720);
        c6 = (uint32_t *)((uint8_t *)pAddress + 8128561152);
        c7 = (uint32_t *)((uint8_t *)pAddress + 8162115584);
        c0Temp = (uint32_t *)((uint8_t *)pAddress + 8195670016);
        opcode = (uint8_t *)((uint8_t *)pAddress + 8229224448);
        cIn = (uint8_t *)((uint8_t *)pAddress + 8233418752);
        cOut = (uint8_t *)((uint8_t *)pAddress + 8237613056);
        last = (uint8_t *)((uint8_t *)pAddress + 8241807360);
        useCarry = (uint8_t *)((uint8_t *)pAddress + 8246001664);
    }

    BinaryCommitPols (void * pAddress, uint64_t degree)
    {
        freeInA = (uint8_t *)((uint8_t *)pAddress + 0);
        freeInB = (uint8_t *)((uint8_t *)pAddress + 2);
        freeInC = (uint8_t *)((uint8_t *)pAddress + 4);
        a0 = (uint32_t *)((uint8_t *)pAddress + 6);
        a1 = (uint32_t *)((uint8_t *)pAddress + 22);
        a2 = (uint32_t *)((uint8_t *)pAddress + 38);
        a3 = (uint32_t *)((uint8_t *)pAddress + 54);
        a4 = (uint32_t *)((uint8_t *)pAddress + 70);
        a5 = (uint32_t *)((uint8_t *)pAddress + 86);
        a6 = (uint32_t *)((uint8_t *)pAddress + 102);
        a7 = (uint32_t *)((uint8_t *)pAddress + 118);
        b0 = (uint32_t *)((uint8_t *)pAddress + 134);
        b1 = (uint32_t *)((uint8_t *)pAddress + 150);
        b2 = (uint32_t *)((uint8_t *)pAddress + 166);
        b3 = (uint32_t *)((uint8_t *)pAddress + 182);
        b4 = (uint32_t *)((uint8_t *)pAddress + 198);
        b5 = (uint32_t *)((uint8_t *)pAddress + 214);
        b6 = (uint32_t *)((uint8_t *)pAddress + 230);
        b7 = (uint32_t *)((uint8_t *)pAddress + 246);
        c0 = (uint32_t *)((uint8_t *)pAddress + 262);
        c1 = (uint32_t *)((uint8_t *)pAddress + 278);
        c2 = (uint32_t *)((uint8_t *)pAddress + 294);
        c3 = (uint32_t *)((uint8_t *)pAddress + 310);
        c4 = (uint32_t *)((uint8_t *)pAddress + 326);
        c5 = (uint32_t *)((uint8_t *)pAddress + 342);
        c6 = (uint32_t *)((uint8_t *)pAddress + 358);
        c7 = (uint32_t *)((uint8_t *)pAddress + 374);
        c0Temp = (uint32_t *)((uint8_t *)pAddress + 390);
        opcode = (uint8_t *)((uint8_t *)pAddress + 406);
        cIn = (uint8_t *)((uint8_t *)pAddress + 408);
        cOut = (uint8_t *)((uint8_t *)pAddress + 410);
        last = (uint8_t *)((uint8_t *)pAddress + 412);
        useCarry = (uint8_t *)((uint8_t *)pAddress + 414);
    }

    static uint64_t degree (void) { return 4194304; }
    static uint64_t size (void) { return 416; }
};

class PoseidonGCommitPols
{
public:
    FieldElement * in0;
    FieldElement * in1;
    FieldElement * in2;
    FieldElement * in3;
    FieldElement * in4;
    FieldElement * in5;
    FieldElement * in6;
    FieldElement * in7;
    FieldElement * hashType;
    FieldElement * cap1;
    FieldElement * cap2;
    FieldElement * cap3;
    FieldElement * hash0;
    FieldElement * hash1;
    FieldElement * hash2;
    FieldElement * hash3;

    PoseidonGCommitPols (void * pAddress)
    {
        in0 = (FieldElement *)((uint8_t *)pAddress + 8250195968);
        in1 = (FieldElement *)((uint8_t *)pAddress + 8283750400);
        in2 = (FieldElement *)((uint8_t *)pAddress + 8317304832);
        in3 = (FieldElement *)((uint8_t *)pAddress + 8350859264);
        in4 = (FieldElement *)((uint8_t *)pAddress + 8384413696);
        in5 = (FieldElement *)((uint8_t *)pAddress + 8417968128);
        in6 = (FieldElement *)((uint8_t *)pAddress + 8451522560);
        in7 = (FieldElement *)((uint8_t *)pAddress + 8485076992);
        hashType = (FieldElement *)((uint8_t *)pAddress + 8518631424);
        cap1 = (FieldElement *)((uint8_t *)pAddress + 8552185856);
        cap2 = (FieldElement *)((uint8_t *)pAddress + 8585740288);
        cap3 = (FieldElement *)((uint8_t *)pAddress + 8619294720);
        hash0 = (FieldElement *)((uint8_t *)pAddress + 8652849152);
        hash1 = (FieldElement *)((uint8_t *)pAddress + 8686403584);
        hash2 = (FieldElement *)((uint8_t *)pAddress + 8719958016);
        hash3 = (FieldElement *)((uint8_t *)pAddress + 8753512448);
    }

    PoseidonGCommitPols (void * pAddress, uint64_t degree)
    {
        in0 = (FieldElement *)((uint8_t *)pAddress + 0);
        in1 = (FieldElement *)((uint8_t *)pAddress + 16);
        in2 = (FieldElement *)((uint8_t *)pAddress + 32);
        in3 = (FieldElement *)((uint8_t *)pAddress + 48);
        in4 = (FieldElement *)((uint8_t *)pAddress + 64);
        in5 = (FieldElement *)((uint8_t *)pAddress + 80);
        in6 = (FieldElement *)((uint8_t *)pAddress + 96);
        in7 = (FieldElement *)((uint8_t *)pAddress + 112);
        hashType = (FieldElement *)((uint8_t *)pAddress + 128);
        cap1 = (FieldElement *)((uint8_t *)pAddress + 144);
        cap2 = (FieldElement *)((uint8_t *)pAddress + 160);
        cap3 = (FieldElement *)((uint8_t *)pAddress + 176);
        hash0 = (FieldElement *)((uint8_t *)pAddress + 192);
        hash1 = (FieldElement *)((uint8_t *)pAddress + 208);
        hash2 = (FieldElement *)((uint8_t *)pAddress + 224);
        hash3 = (FieldElement *)((uint8_t *)pAddress + 240);
    }

    static uint64_t degree (void) { return 4194304; }
    static uint64_t size (void) { return 256; }
};

class PaddingPGCommitPols
{
public:
    FieldElement * acc[8];
    FieldElement * freeIn;
    FieldElement * addr;
    FieldElement * rem;
    FieldElement * remInv;
    FieldElement * spare;
    FieldElement * firstHash;
    FieldElement * curHash0;
    FieldElement * curHash1;
    FieldElement * curHash2;
    FieldElement * curHash3;
    FieldElement * prevHash0;
    FieldElement * prevHash1;
    FieldElement * prevHash2;
    FieldElement * prevHash3;
    FieldElement * len;
    FieldElement * crOffset;
    FieldElement * crLen;
    FieldElement * crOffsetInv;
    FieldElement * crF0;
    FieldElement * crF1;
    FieldElement * crF2;
    FieldElement * crF3;
    FieldElement * crF4;
    FieldElement * crF5;
    FieldElement * crF6;
    FieldElement * crF7;
    FieldElement * crV0;
    FieldElement * crV1;
    FieldElement * crV2;
    FieldElement * crV3;
    FieldElement * crV4;
    FieldElement * crV5;
    FieldElement * crV6;
    FieldElement * crV7;

    PaddingPGCommitPols (void * pAddress)
    {
        acc[0] = (FieldElement *)((uint8_t *)pAddress + 8787066880);
        acc[1] = (FieldElement *)((uint8_t *)pAddress + 8820621312);
        acc[2] = (FieldElement *)((uint8_t *)pAddress + 8854175744);
        acc[3] = (FieldElement *)((uint8_t *)pAddress + 8887730176);
        acc[4] = (FieldElement *)((uint8_t *)pAddress + 8921284608);
        acc[5] = (FieldElement *)((uint8_t *)pAddress + 8954839040);
        acc[6] = (FieldElement *)((uint8_t *)pAddress + 8988393472);
        acc[7] = (FieldElement *)((uint8_t *)pAddress + 9021947904);
        freeIn = (FieldElement *)((uint8_t *)pAddress + 9055502336);
        addr = (FieldElement *)((uint8_t *)pAddress + 9089056768);
        rem = (FieldElement *)((uint8_t *)pAddress + 9122611200);
        remInv = (FieldElement *)((uint8_t *)pAddress + 9156165632);
        spare = (FieldElement *)((uint8_t *)pAddress + 9189720064);
        firstHash = (FieldElement *)((uint8_t *)pAddress + 9223274496);
        curHash0 = (FieldElement *)((uint8_t *)pAddress + 9256828928);
        curHash1 = (FieldElement *)((uint8_t *)pAddress + 9290383360);
        curHash2 = (FieldElement *)((uint8_t *)pAddress + 9323937792);
        curHash3 = (FieldElement *)((uint8_t *)pAddress + 9357492224);
        prevHash0 = (FieldElement *)((uint8_t *)pAddress + 9391046656);
        prevHash1 = (FieldElement *)((uint8_t *)pAddress + 9424601088);
        prevHash2 = (FieldElement *)((uint8_t *)pAddress + 9458155520);
        prevHash3 = (FieldElement *)((uint8_t *)pAddress + 9491709952);
        len = (FieldElement *)((uint8_t *)pAddress + 9525264384);
        crOffset = (FieldElement *)((uint8_t *)pAddress + 9558818816);
        crLen = (FieldElement *)((uint8_t *)pAddress + 9592373248);
        crOffsetInv = (FieldElement *)((uint8_t *)pAddress + 9625927680);
        crF0 = (FieldElement *)((uint8_t *)pAddress + 9659482112);
        crF1 = (FieldElement *)((uint8_t *)pAddress + 9693036544);
        crF2 = (FieldElement *)((uint8_t *)pAddress + 9726590976);
        crF3 = (FieldElement *)((uint8_t *)pAddress + 9760145408);
        crF4 = (FieldElement *)((uint8_t *)pAddress + 9793699840);
        crF5 = (FieldElement *)((uint8_t *)pAddress + 9827254272);
        crF6 = (FieldElement *)((uint8_t *)pAddress + 9860808704);
        crF7 = (FieldElement *)((uint8_t *)pAddress + 9894363136);
        crV0 = (FieldElement *)((uint8_t *)pAddress + 9927917568);
        crV1 = (FieldElement *)((uint8_t *)pAddress + 9961472000);
        crV2 = (FieldElement *)((uint8_t *)pAddress + 9995026432);
        crV3 = (FieldElement *)((uint8_t *)pAddress + 10028580864);
        crV4 = (FieldElement *)((uint8_t *)pAddress + 10062135296);
        crV5 = (FieldElement *)((uint8_t *)pAddress + 10095689728);
        crV6 = (FieldElement *)((uint8_t *)pAddress + 10129244160);
        crV7 = (FieldElement *)((uint8_t *)pAddress + 10162798592);
    }

    PaddingPGCommitPols (void * pAddress, uint64_t degree)
    {
        acc[0] = (FieldElement *)((uint8_t *)pAddress + 0);
        acc[1] = (FieldElement *)((uint8_t *)pAddress + 16);
        acc[2] = (FieldElement *)((uint8_t *)pAddress + 32);
        acc[3] = (FieldElement *)((uint8_t *)pAddress + 48);
        acc[4] = (FieldElement *)((uint8_t *)pAddress + 64);
        acc[5] = (FieldElement *)((uint8_t *)pAddress + 80);
        acc[6] = (FieldElement *)((uint8_t *)pAddress + 96);
        acc[7] = (FieldElement *)((uint8_t *)pAddress + 112);
        freeIn = (FieldElement *)((uint8_t *)pAddress + 128);
        addr = (FieldElement *)((uint8_t *)pAddress + 144);
        rem = (FieldElement *)((uint8_t *)pAddress + 160);
        remInv = (FieldElement *)((uint8_t *)pAddress + 176);
        spare = (FieldElement *)((uint8_t *)pAddress + 192);
        firstHash = (FieldElement *)((uint8_t *)pAddress + 208);
        curHash0 = (FieldElement *)((uint8_t *)pAddress + 224);
        curHash1 = (FieldElement *)((uint8_t *)pAddress + 240);
        curHash2 = (FieldElement *)((uint8_t *)pAddress + 256);
        curHash3 = (FieldElement *)((uint8_t *)pAddress + 272);
        prevHash0 = (FieldElement *)((uint8_t *)pAddress + 288);
        prevHash1 = (FieldElement *)((uint8_t *)pAddress + 304);
        prevHash2 = (FieldElement *)((uint8_t *)pAddress + 320);
        prevHash3 = (FieldElement *)((uint8_t *)pAddress + 336);
        len = (FieldElement *)((uint8_t *)pAddress + 352);
        crOffset = (FieldElement *)((uint8_t *)pAddress + 368);
        crLen = (FieldElement *)((uint8_t *)pAddress + 384);
        crOffsetInv = (FieldElement *)((uint8_t *)pAddress + 400);
        crF0 = (FieldElement *)((uint8_t *)pAddress + 416);
        crF1 = (FieldElement *)((uint8_t *)pAddress + 432);
        crF2 = (FieldElement *)((uint8_t *)pAddress + 448);
        crF3 = (FieldElement *)((uint8_t *)pAddress + 464);
        crF4 = (FieldElement *)((uint8_t *)pAddress + 480);
        crF5 = (FieldElement *)((uint8_t *)pAddress + 496);
        crF6 = (FieldElement *)((uint8_t *)pAddress + 512);
        crF7 = (FieldElement *)((uint8_t *)pAddress + 528);
        crV0 = (FieldElement *)((uint8_t *)pAddress + 544);
        crV1 = (FieldElement *)((uint8_t *)pAddress + 560);
        crV2 = (FieldElement *)((uint8_t *)pAddress + 576);
        crV3 = (FieldElement *)((uint8_t *)pAddress + 592);
        crV4 = (FieldElement *)((uint8_t *)pAddress + 608);
        crV5 = (FieldElement *)((uint8_t *)pAddress + 624);
        crV6 = (FieldElement *)((uint8_t *)pAddress + 640);
        crV7 = (FieldElement *)((uint8_t *)pAddress + 656);
    }

    static uint64_t degree (void) { return 4194304; }
    static uint64_t size (void) { return 672; }
};

class StorageCommitPols
{
public:
    uint64_t * free0;
    uint64_t * free1;
    uint64_t * free2;
    uint64_t * free3;
    uint64_t * hashLeft0;
    uint64_t * hashLeft1;
    uint64_t * hashLeft2;
    uint64_t * hashLeft3;
    uint64_t * hashRight0;
    uint64_t * hashRight1;
    uint64_t * hashRight2;
    uint64_t * hashRight3;
    uint64_t * oldRoot0;
    uint64_t * oldRoot1;
    uint64_t * oldRoot2;
    uint64_t * oldRoot3;
    uint64_t * newRoot0;
    uint64_t * newRoot1;
    uint64_t * newRoot2;
    uint64_t * newRoot3;
    uint64_t * valueLow0;
    uint64_t * valueLow1;
    uint64_t * valueLow2;
    uint64_t * valueLow3;
    uint64_t * valueHigh0;
    uint64_t * valueHigh1;
    uint64_t * valueHigh2;
    uint64_t * valueHigh3;
    uint64_t * siblingValueHash0;
    uint64_t * siblingValueHash1;
    uint64_t * siblingValueHash2;
    uint64_t * siblingValueHash3;
    uint64_t * rkey0;
    uint64_t * rkey1;
    uint64_t * rkey2;
    uint64_t * rkey3;
    uint64_t * siblingRkey0;
    uint64_t * siblingRkey1;
    uint64_t * siblingRkey2;
    uint64_t * siblingRkey3;
    uint64_t * rkeyBit;
    uint64_t * level0;
    uint64_t * level1;
    uint64_t * level2;
    uint64_t * level3;
    uint64_t * pc;
    uint8_t * selOldRoot;
    uint8_t * selNewRoot;
    uint8_t * selValueLow;
    uint8_t * selValueHigh;
    uint8_t * selSiblingValueHash;
    uint8_t * selRkey;
    uint8_t * selRkeyBit;
    uint8_t * selSiblingRkey;
    uint8_t * selFree;
    uint8_t * setHashLeft;
    uint8_t * setHashRight;
    uint8_t * setOldRoot;
    uint8_t * setNewRoot;
    uint8_t * setValueLow;
    uint8_t * setValueHigh;
    uint8_t * setSiblingValueHash;
    uint8_t * setRkey;
    uint8_t * setSiblingRkey;
    uint8_t * setRkeyBit;
    uint8_t * setLevel;
    uint8_t * iHash;
    uint8_t * iHashType;
    uint8_t * iLatchSet;
    uint8_t * iLatchGet;
    uint8_t * iClimbRkey;
    uint8_t * iClimbSiblingRkey;
    uint8_t * iClimbSiblingRkeyN;
    uint8_t * iRotateLevel;
    uint8_t * iJmpz;
    uint8_t * iJmp;
    uint64_t * iConst0;
    uint64_t * iConst1;
    uint64_t * iConst2;
    uint64_t * iConst3;
    uint64_t * iAddress;
    FieldElement * op0inv;

    StorageCommitPols (void * pAddress)
    {
        free0 = (uint64_t *)((uint8_t *)pAddress + 10196353024);
        free1 = (uint64_t *)((uint8_t *)pAddress + 10229907456);
        free2 = (uint64_t *)((uint8_t *)pAddress + 10263461888);
        free3 = (uint64_t *)((uint8_t *)pAddress + 10297016320);
        hashLeft0 = (uint64_t *)((uint8_t *)pAddress + 10330570752);
        hashLeft1 = (uint64_t *)((uint8_t *)pAddress + 10364125184);
        hashLeft2 = (uint64_t *)((uint8_t *)pAddress + 10397679616);
        hashLeft3 = (uint64_t *)((uint8_t *)pAddress + 10431234048);
        hashRight0 = (uint64_t *)((uint8_t *)pAddress + 10464788480);
        hashRight1 = (uint64_t *)((uint8_t *)pAddress + 10498342912);
        hashRight2 = (uint64_t *)((uint8_t *)pAddress + 10531897344);
        hashRight3 = (uint64_t *)((uint8_t *)pAddress + 10565451776);
        oldRoot0 = (uint64_t *)((uint8_t *)pAddress + 10599006208);
        oldRoot1 = (uint64_t *)((uint8_t *)pAddress + 10632560640);
        oldRoot2 = (uint64_t *)((uint8_t *)pAddress + 10666115072);
        oldRoot3 = (uint64_t *)((uint8_t *)pAddress + 10699669504);
        newRoot0 = (uint64_t *)((uint8_t *)pAddress + 10733223936);
        newRoot1 = (uint64_t *)((uint8_t *)pAddress + 10766778368);
        newRoot2 = (uint64_t *)((uint8_t *)pAddress + 10800332800);
        newRoot3 = (uint64_t *)((uint8_t *)pAddress + 10833887232);
        valueLow0 = (uint64_t *)((uint8_t *)pAddress + 10867441664);
        valueLow1 = (uint64_t *)((uint8_t *)pAddress + 10900996096);
        valueLow2 = (uint64_t *)((uint8_t *)pAddress + 10934550528);
        valueLow3 = (uint64_t *)((uint8_t *)pAddress + 10968104960);
        valueHigh0 = (uint64_t *)((uint8_t *)pAddress + 11001659392);
        valueHigh1 = (uint64_t *)((uint8_t *)pAddress + 11035213824);
        valueHigh2 = (uint64_t *)((uint8_t *)pAddress + 11068768256);
        valueHigh3 = (uint64_t *)((uint8_t *)pAddress + 11102322688);
        siblingValueHash0 = (uint64_t *)((uint8_t *)pAddress + 11135877120);
        siblingValueHash1 = (uint64_t *)((uint8_t *)pAddress + 11169431552);
        siblingValueHash2 = (uint64_t *)((uint8_t *)pAddress + 11202985984);
        siblingValueHash3 = (uint64_t *)((uint8_t *)pAddress + 11236540416);
        rkey0 = (uint64_t *)((uint8_t *)pAddress + 11270094848);
        rkey1 = (uint64_t *)((uint8_t *)pAddress + 11303649280);
        rkey2 = (uint64_t *)((uint8_t *)pAddress + 11337203712);
        rkey3 = (uint64_t *)((uint8_t *)pAddress + 11370758144);
        siblingRkey0 = (uint64_t *)((uint8_t *)pAddress + 11404312576);
        siblingRkey1 = (uint64_t *)((uint8_t *)pAddress + 11437867008);
        siblingRkey2 = (uint64_t *)((uint8_t *)pAddress + 11471421440);
        siblingRkey3 = (uint64_t *)((uint8_t *)pAddress + 11504975872);
        rkeyBit = (uint64_t *)((uint8_t *)pAddress + 11538530304);
        level0 = (uint64_t *)((uint8_t *)pAddress + 11572084736);
        level1 = (uint64_t *)((uint8_t *)pAddress + 11605639168);
        level2 = (uint64_t *)((uint8_t *)pAddress + 11639193600);
        level3 = (uint64_t *)((uint8_t *)pAddress + 11672748032);
        pc = (uint64_t *)((uint8_t *)pAddress + 11706302464);
        selOldRoot = (uint8_t *)((uint8_t *)pAddress + 11739856896);
        selNewRoot = (uint8_t *)((uint8_t *)pAddress + 11744051200);
        selValueLow = (uint8_t *)((uint8_t *)pAddress + 11748245504);
        selValueHigh = (uint8_t *)((uint8_t *)pAddress + 11752439808);
        selSiblingValueHash = (uint8_t *)((uint8_t *)pAddress + 11756634112);
        selRkey = (uint8_t *)((uint8_t *)pAddress + 11760828416);
        selRkeyBit = (uint8_t *)((uint8_t *)pAddress + 11765022720);
        selSiblingRkey = (uint8_t *)((uint8_t *)pAddress + 11769217024);
        selFree = (uint8_t *)((uint8_t *)pAddress + 11773411328);
        setHashLeft = (uint8_t *)((uint8_t *)pAddress + 11777605632);
        setHashRight = (uint8_t *)((uint8_t *)pAddress + 11781799936);
        setOldRoot = (uint8_t *)((uint8_t *)pAddress + 11785994240);
        setNewRoot = (uint8_t *)((uint8_t *)pAddress + 11790188544);
        setValueLow = (uint8_t *)((uint8_t *)pAddress + 11794382848);
        setValueHigh = (uint8_t *)((uint8_t *)pAddress + 11798577152);
        setSiblingValueHash = (uint8_t *)((uint8_t *)pAddress + 11802771456);
        setRkey = (uint8_t *)((uint8_t *)pAddress + 11806965760);
        setSiblingRkey = (uint8_t *)((uint8_t *)pAddress + 11811160064);
        setRkeyBit = (uint8_t *)((uint8_t *)pAddress + 11815354368);
        setLevel = (uint8_t *)((uint8_t *)pAddress + 11819548672);
        iHash = (uint8_t *)((uint8_t *)pAddress + 11823742976);
        iHashType = (uint8_t *)((uint8_t *)pAddress + 11827937280);
        iLatchSet = (uint8_t *)((uint8_t *)pAddress + 11832131584);
        iLatchGet = (uint8_t *)((uint8_t *)pAddress + 11836325888);
        iClimbRkey = (uint8_t *)((uint8_t *)pAddress + 11840520192);
        iClimbSiblingRkey = (uint8_t *)((uint8_t *)pAddress + 11844714496);
        iClimbSiblingRkeyN = (uint8_t *)((uint8_t *)pAddress + 11848908800);
        iRotateLevel = (uint8_t *)((uint8_t *)pAddress + 11853103104);
        iJmpz = (uint8_t *)((uint8_t *)pAddress + 11857297408);
        iJmp = (uint8_t *)((uint8_t *)pAddress + 11861491712);
        iConst0 = (uint64_t *)((uint8_t *)pAddress + 11865686016);
        iConst1 = (uint64_t *)((uint8_t *)pAddress + 11899240448);
        iConst2 = (uint64_t *)((uint8_t *)pAddress + 11932794880);
        iConst3 = (uint64_t *)((uint8_t *)pAddress + 11966349312);
        iAddress = (uint64_t *)((uint8_t *)pAddress + 11999903744);
        op0inv = (FieldElement *)((uint8_t *)pAddress + 12033458176);
    }

    StorageCommitPols (void * pAddress, uint64_t degree)
    {
        free0 = (uint64_t *)((uint8_t *)pAddress + 0);
        free1 = (uint64_t *)((uint8_t *)pAddress + 16);
        free2 = (uint64_t *)((uint8_t *)pAddress + 32);
        free3 = (uint64_t *)((uint8_t *)pAddress + 48);
        hashLeft0 = (uint64_t *)((uint8_t *)pAddress + 64);
        hashLeft1 = (uint64_t *)((uint8_t *)pAddress + 80);
        hashLeft2 = (uint64_t *)((uint8_t *)pAddress + 96);
        hashLeft3 = (uint64_t *)((uint8_t *)pAddress + 112);
        hashRight0 = (uint64_t *)((uint8_t *)pAddress + 128);
        hashRight1 = (uint64_t *)((uint8_t *)pAddress + 144);
        hashRight2 = (uint64_t *)((uint8_t *)pAddress + 160);
        hashRight3 = (uint64_t *)((uint8_t *)pAddress + 176);
        oldRoot0 = (uint64_t *)((uint8_t *)pAddress + 192);
        oldRoot1 = (uint64_t *)((uint8_t *)pAddress + 208);
        oldRoot2 = (uint64_t *)((uint8_t *)pAddress + 224);
        oldRoot3 = (uint64_t *)((uint8_t *)pAddress + 240);
        newRoot0 = (uint64_t *)((uint8_t *)pAddress + 256);
        newRoot1 = (uint64_t *)((uint8_t *)pAddress + 272);
        newRoot2 = (uint64_t *)((uint8_t *)pAddress + 288);
        newRoot3 = (uint64_t *)((uint8_t *)pAddress + 304);
        valueLow0 = (uint64_t *)((uint8_t *)pAddress + 320);
        valueLow1 = (uint64_t *)((uint8_t *)pAddress + 336);
        valueLow2 = (uint64_t *)((uint8_t *)pAddress + 352);
        valueLow3 = (uint64_t *)((uint8_t *)pAddress + 368);
        valueHigh0 = (uint64_t *)((uint8_t *)pAddress + 384);
        valueHigh1 = (uint64_t *)((uint8_t *)pAddress + 400);
        valueHigh2 = (uint64_t *)((uint8_t *)pAddress + 416);
        valueHigh3 = (uint64_t *)((uint8_t *)pAddress + 432);
        siblingValueHash0 = (uint64_t *)((uint8_t *)pAddress + 448);
        siblingValueHash1 = (uint64_t *)((uint8_t *)pAddress + 464);
        siblingValueHash2 = (uint64_t *)((uint8_t *)pAddress + 480);
        siblingValueHash3 = (uint64_t *)((uint8_t *)pAddress + 496);
        rkey0 = (uint64_t *)((uint8_t *)pAddress + 512);
        rkey1 = (uint64_t *)((uint8_t *)pAddress + 528);
        rkey2 = (uint64_t *)((uint8_t *)pAddress + 544);
        rkey3 = (uint64_t *)((uint8_t *)pAddress + 560);
        siblingRkey0 = (uint64_t *)((uint8_t *)pAddress + 576);
        siblingRkey1 = (uint64_t *)((uint8_t *)pAddress + 592);
        siblingRkey2 = (uint64_t *)((uint8_t *)pAddress + 608);
        siblingRkey3 = (uint64_t *)((uint8_t *)pAddress + 624);
        rkeyBit = (uint64_t *)((uint8_t *)pAddress + 640);
        level0 = (uint64_t *)((uint8_t *)pAddress + 656);
        level1 = (uint64_t *)((uint8_t *)pAddress + 672);
        level2 = (uint64_t *)((uint8_t *)pAddress + 688);
        level3 = (uint64_t *)((uint8_t *)pAddress + 704);
        pc = (uint64_t *)((uint8_t *)pAddress + 720);
        selOldRoot = (uint8_t *)((uint8_t *)pAddress + 736);
        selNewRoot = (uint8_t *)((uint8_t *)pAddress + 738);
        selValueLow = (uint8_t *)((uint8_t *)pAddress + 740);
        selValueHigh = (uint8_t *)((uint8_t *)pAddress + 742);
        selSiblingValueHash = (uint8_t *)((uint8_t *)pAddress + 744);
        selRkey = (uint8_t *)((uint8_t *)pAddress + 746);
        selRkeyBit = (uint8_t *)((uint8_t *)pAddress + 748);
        selSiblingRkey = (uint8_t *)((uint8_t *)pAddress + 750);
        selFree = (uint8_t *)((uint8_t *)pAddress + 752);
        setHashLeft = (uint8_t *)((uint8_t *)pAddress + 754);
        setHashRight = (uint8_t *)((uint8_t *)pAddress + 756);
        setOldRoot = (uint8_t *)((uint8_t *)pAddress + 758);
        setNewRoot = (uint8_t *)((uint8_t *)pAddress + 760);
        setValueLow = (uint8_t *)((uint8_t *)pAddress + 762);
        setValueHigh = (uint8_t *)((uint8_t *)pAddress + 764);
        setSiblingValueHash = (uint8_t *)((uint8_t *)pAddress + 766);
        setRkey = (uint8_t *)((uint8_t *)pAddress + 768);
        setSiblingRkey = (uint8_t *)((uint8_t *)pAddress + 770);
        setRkeyBit = (uint8_t *)((uint8_t *)pAddress + 772);
        setLevel = (uint8_t *)((uint8_t *)pAddress + 774);
        iHash = (uint8_t *)((uint8_t *)pAddress + 776);
        iHashType = (uint8_t *)((uint8_t *)pAddress + 778);
        iLatchSet = (uint8_t *)((uint8_t *)pAddress + 780);
        iLatchGet = (uint8_t *)((uint8_t *)pAddress + 782);
        iClimbRkey = (uint8_t *)((uint8_t *)pAddress + 784);
        iClimbSiblingRkey = (uint8_t *)((uint8_t *)pAddress + 786);
        iClimbSiblingRkeyN = (uint8_t *)((uint8_t *)pAddress + 788);
        iRotateLevel = (uint8_t *)((uint8_t *)pAddress + 790);
        iJmpz = (uint8_t *)((uint8_t *)pAddress + 792);
        iJmp = (uint8_t *)((uint8_t *)pAddress + 794);
        iConst0 = (uint64_t *)((uint8_t *)pAddress + 796);
        iConst1 = (uint64_t *)((uint8_t *)pAddress + 812);
        iConst2 = (uint64_t *)((uint8_t *)pAddress + 828);
        iConst3 = (uint64_t *)((uint8_t *)pAddress + 844);
        iAddress = (uint64_t *)((uint8_t *)pAddress + 860);
        op0inv = (FieldElement *)((uint8_t *)pAddress + 876);
    }

    static uint64_t degree (void) { return 4194304; }
    static uint64_t size (void) { return 892; }
};

class NormGate9CommitPols
{
public:
    FieldElement * freeA;
    FieldElement * freeB;
    FieldElement * gateType;
    FieldElement * freeANorm;
    FieldElement * freeBNorm;
    FieldElement * freeCNorm;
    FieldElement * a;
    FieldElement * b;
    FieldElement * c;

    NormGate9CommitPols (void * pAddress)
    {
        freeA = (FieldElement *)((uint8_t *)pAddress + 12067012608);
        freeB = (FieldElement *)((uint8_t *)pAddress + 12100567040);
        gateType = (FieldElement *)((uint8_t *)pAddress + 12134121472);
        freeANorm = (FieldElement *)((uint8_t *)pAddress + 12167675904);
        freeBNorm = (FieldElement *)((uint8_t *)pAddress + 12201230336);
        freeCNorm = (FieldElement *)((uint8_t *)pAddress + 12234784768);
        a = (FieldElement *)((uint8_t *)pAddress + 12268339200);
        b = (FieldElement *)((uint8_t *)pAddress + 12301893632);
        c = (FieldElement *)((uint8_t *)pAddress + 12335448064);
    }

    NormGate9CommitPols (void * pAddress, uint64_t degree)
    {
        freeA = (FieldElement *)((uint8_t *)pAddress + 0);
        freeB = (FieldElement *)((uint8_t *)pAddress + 16);
        gateType = (FieldElement *)((uint8_t *)pAddress + 32);
        freeANorm = (FieldElement *)((uint8_t *)pAddress + 48);
        freeBNorm = (FieldElement *)((uint8_t *)pAddress + 64);
        freeCNorm = (FieldElement *)((uint8_t *)pAddress + 80);
        a = (FieldElement *)((uint8_t *)pAddress + 96);
        b = (FieldElement *)((uint8_t *)pAddress + 112);
        c = (FieldElement *)((uint8_t *)pAddress + 128);
    }

    static uint64_t degree (void) { return 4194304; }
    static uint64_t size (void) { return 144; }
};

class KeccakFCommitPols
{
public:
    FieldElement * a;
    FieldElement * b;
    FieldElement * c;

    KeccakFCommitPols (void * pAddress)
    {
        a = (FieldElement *)((uint8_t *)pAddress + 12369002496);
        b = (FieldElement *)((uint8_t *)pAddress + 12402556928);
        c = (FieldElement *)((uint8_t *)pAddress + 12436111360);
    }

    KeccakFCommitPols (void * pAddress, uint64_t degree)
    {
        a = (FieldElement *)((uint8_t *)pAddress + 0);
        b = (FieldElement *)((uint8_t *)pAddress + 16);
        c = (FieldElement *)((uint8_t *)pAddress + 32);
    }

    static uint64_t degree (void) { return 4194304; }
    static uint64_t size (void) { return 48; }
};

class Nine2OneCommitPols
{
public:
    FieldElement * bit;
    FieldElement * field9;

    Nine2OneCommitPols (void * pAddress)
    {
        bit = (FieldElement *)((uint8_t *)pAddress + 12469665792);
        field9 = (FieldElement *)((uint8_t *)pAddress + 12503220224);
    }

    Nine2OneCommitPols (void * pAddress, uint64_t degree)
    {
        bit = (FieldElement *)((uint8_t *)pAddress + 0);
        field9 = (FieldElement *)((uint8_t *)pAddress + 16);
    }

    static uint64_t degree (void) { return 4194304; }
    static uint64_t size (void) { return 32; }
};

class PaddingKKBitCommitPols
{
public:
    FieldElement * rBit;
    FieldElement * sOutBit;
    FieldElement * r8;
    FieldElement * connected;
    FieldElement * sOut0;
    FieldElement * sOut1;
    FieldElement * sOut2;
    FieldElement * sOut3;
    FieldElement * sOut4;
    FieldElement * sOut5;
    FieldElement * sOut6;
    FieldElement * sOut7;

    PaddingKKBitCommitPols (void * pAddress)
    {
        rBit = (FieldElement *)((uint8_t *)pAddress + 12536774656);
        sOutBit = (FieldElement *)((uint8_t *)pAddress + 12570329088);
        r8 = (FieldElement *)((uint8_t *)pAddress + 12603883520);
        connected = (FieldElement *)((uint8_t *)pAddress + 12637437952);
        sOut0 = (FieldElement *)((uint8_t *)pAddress + 12670992384);
        sOut1 = (FieldElement *)((uint8_t *)pAddress + 12704546816);
        sOut2 = (FieldElement *)((uint8_t *)pAddress + 12738101248);
        sOut3 = (FieldElement *)((uint8_t *)pAddress + 12771655680);
        sOut4 = (FieldElement *)((uint8_t *)pAddress + 12805210112);
        sOut5 = (FieldElement *)((uint8_t *)pAddress + 12838764544);
        sOut6 = (FieldElement *)((uint8_t *)pAddress + 12872318976);
        sOut7 = (FieldElement *)((uint8_t *)pAddress + 12905873408);
    }

    PaddingKKBitCommitPols (void * pAddress, uint64_t degree)
    {
        rBit = (FieldElement *)((uint8_t *)pAddress + 0);
        sOutBit = (FieldElement *)((uint8_t *)pAddress + 16);
        r8 = (FieldElement *)((uint8_t *)pAddress + 32);
        connected = (FieldElement *)((uint8_t *)pAddress + 48);
        sOut0 = (FieldElement *)((uint8_t *)pAddress + 64);
        sOut1 = (FieldElement *)((uint8_t *)pAddress + 80);
        sOut2 = (FieldElement *)((uint8_t *)pAddress + 96);
        sOut3 = (FieldElement *)((uint8_t *)pAddress + 112);
        sOut4 = (FieldElement *)((uint8_t *)pAddress + 128);
        sOut5 = (FieldElement *)((uint8_t *)pAddress + 144);
        sOut6 = (FieldElement *)((uint8_t *)pAddress + 160);
        sOut7 = (FieldElement *)((uint8_t *)pAddress + 176);
    }

    static uint64_t degree (void) { return 4194304; }
    static uint64_t size (void) { return 192; }
};

class PaddingKKCommitPols
{
public:
    FieldElement * freeIn;
    FieldElement * connected;
    FieldElement * addr;
    FieldElement * rem;
    FieldElement * remInv;
    FieldElement * spare;
    FieldElement * firstHash;
    FieldElement * len;
    FieldElement * hash0;
    FieldElement * hash1;
    FieldElement * hash2;
    FieldElement * hash3;
    FieldElement * hash4;
    FieldElement * hash5;
    FieldElement * hash6;
    FieldElement * hash7;
    FieldElement * crOffset;
    FieldElement * crLen;
    FieldElement * crOffsetInv;
    FieldElement * crF0;
    FieldElement * crF1;
    FieldElement * crF2;
    FieldElement * crF3;
    FieldElement * crF4;
    FieldElement * crF5;
    FieldElement * crF6;
    FieldElement * crF7;
    FieldElement * crV0;
    FieldElement * crV1;
    FieldElement * crV2;
    FieldElement * crV3;
    FieldElement * crV4;
    FieldElement * crV5;
    FieldElement * crV6;
    FieldElement * crV7;

    PaddingKKCommitPols (void * pAddress)
    {
        freeIn = (FieldElement *)((uint8_t *)pAddress + 12939427840);
        connected = (FieldElement *)((uint8_t *)pAddress + 12972982272);
        addr = (FieldElement *)((uint8_t *)pAddress + 13006536704);
        rem = (FieldElement *)((uint8_t *)pAddress + 13040091136);
        remInv = (FieldElement *)((uint8_t *)pAddress + 13073645568);
        spare = (FieldElement *)((uint8_t *)pAddress + 13107200000);
        firstHash = (FieldElement *)((uint8_t *)pAddress + 13140754432);
        len = (FieldElement *)((uint8_t *)pAddress + 13174308864);
        hash0 = (FieldElement *)((uint8_t *)pAddress + 13207863296);
        hash1 = (FieldElement *)((uint8_t *)pAddress + 13241417728);
        hash2 = (FieldElement *)((uint8_t *)pAddress + 13274972160);
        hash3 = (FieldElement *)((uint8_t *)pAddress + 13308526592);
        hash4 = (FieldElement *)((uint8_t *)pAddress + 13342081024);
        hash5 = (FieldElement *)((uint8_t *)pAddress + 13375635456);
        hash6 = (FieldElement *)((uint8_t *)pAddress + 13409189888);
        hash7 = (FieldElement *)((uint8_t *)pAddress + 13442744320);
        crOffset = (FieldElement *)((uint8_t *)pAddress + 13476298752);
        crLen = (FieldElement *)((uint8_t *)pAddress + 13509853184);
        crOffsetInv = (FieldElement *)((uint8_t *)pAddress + 13543407616);
        crF0 = (FieldElement *)((uint8_t *)pAddress + 13576962048);
        crF1 = (FieldElement *)((uint8_t *)pAddress + 13610516480);
        crF2 = (FieldElement *)((uint8_t *)pAddress + 13644070912);
        crF3 = (FieldElement *)((uint8_t *)pAddress + 13677625344);
        crF4 = (FieldElement *)((uint8_t *)pAddress + 13711179776);
        crF5 = (FieldElement *)((uint8_t *)pAddress + 13744734208);
        crF6 = (FieldElement *)((uint8_t *)pAddress + 13778288640);
        crF7 = (FieldElement *)((uint8_t *)pAddress + 13811843072);
        crV0 = (FieldElement *)((uint8_t *)pAddress + 13845397504);
        crV1 = (FieldElement *)((uint8_t *)pAddress + 13878951936);
        crV2 = (FieldElement *)((uint8_t *)pAddress + 13912506368);
        crV3 = (FieldElement *)((uint8_t *)pAddress + 13946060800);
        crV4 = (FieldElement *)((uint8_t *)pAddress + 13979615232);
        crV5 = (FieldElement *)((uint8_t *)pAddress + 14013169664);
        crV6 = (FieldElement *)((uint8_t *)pAddress + 14046724096);
        crV7 = (FieldElement *)((uint8_t *)pAddress + 14080278528);
    }

    PaddingKKCommitPols (void * pAddress, uint64_t degree)
    {
        freeIn = (FieldElement *)((uint8_t *)pAddress + 0);
        connected = (FieldElement *)((uint8_t *)pAddress + 16);
        addr = (FieldElement *)((uint8_t *)pAddress + 32);
        rem = (FieldElement *)((uint8_t *)pAddress + 48);
        remInv = (FieldElement *)((uint8_t *)pAddress + 64);
        spare = (FieldElement *)((uint8_t *)pAddress + 80);
        firstHash = (FieldElement *)((uint8_t *)pAddress + 96);
        len = (FieldElement *)((uint8_t *)pAddress + 112);
        hash0 = (FieldElement *)((uint8_t *)pAddress + 128);
        hash1 = (FieldElement *)((uint8_t *)pAddress + 144);
        hash2 = (FieldElement *)((uint8_t *)pAddress + 160);
        hash3 = (FieldElement *)((uint8_t *)pAddress + 176);
        hash4 = (FieldElement *)((uint8_t *)pAddress + 192);
        hash5 = (FieldElement *)((uint8_t *)pAddress + 208);
        hash6 = (FieldElement *)((uint8_t *)pAddress + 224);
        hash7 = (FieldElement *)((uint8_t *)pAddress + 240);
        crOffset = (FieldElement *)((uint8_t *)pAddress + 256);
        crLen = (FieldElement *)((uint8_t *)pAddress + 272);
        crOffsetInv = (FieldElement *)((uint8_t *)pAddress + 288);
        crF0 = (FieldElement *)((uint8_t *)pAddress + 304);
        crF1 = (FieldElement *)((uint8_t *)pAddress + 320);
        crF2 = (FieldElement *)((uint8_t *)pAddress + 336);
        crF3 = (FieldElement *)((uint8_t *)pAddress + 352);
        crF4 = (FieldElement *)((uint8_t *)pAddress + 368);
        crF5 = (FieldElement *)((uint8_t *)pAddress + 384);
        crF6 = (FieldElement *)((uint8_t *)pAddress + 400);
        crF7 = (FieldElement *)((uint8_t *)pAddress + 416);
        crV0 = (FieldElement *)((uint8_t *)pAddress + 432);
        crV1 = (FieldElement *)((uint8_t *)pAddress + 448);
        crV2 = (FieldElement *)((uint8_t *)pAddress + 464);
        crV3 = (FieldElement *)((uint8_t *)pAddress + 480);
        crV4 = (FieldElement *)((uint8_t *)pAddress + 496);
        crV5 = (FieldElement *)((uint8_t *)pAddress + 512);
        crV6 = (FieldElement *)((uint8_t *)pAddress + 528);
        crV7 = (FieldElement *)((uint8_t *)pAddress + 544);
    }

    static uint64_t degree (void) { return 4194304; }
    static uint64_t size (void) { return 560; }
};

class MemCommitPols
{
public:
    FieldElement * addr;
    FieldElement * step;
    FieldElement * mOp;
    FieldElement * mWr;
    FieldElement * val[8];
    FieldElement * lastAccess;

    MemCommitPols (void * pAddress)
    {
        addr = (FieldElement *)((uint8_t *)pAddress + 14113832960);
        step = (FieldElement *)((uint8_t *)pAddress + 14147387392);
        mOp = (FieldElement *)((uint8_t *)pAddress + 14180941824);
        mWr = (FieldElement *)((uint8_t *)pAddress + 14214496256);
        val[0] = (FieldElement *)((uint8_t *)pAddress + 14248050688);
        val[1] = (FieldElement *)((uint8_t *)pAddress + 14281605120);
        val[2] = (FieldElement *)((uint8_t *)pAddress + 14315159552);
        val[3] = (FieldElement *)((uint8_t *)pAddress + 14348713984);
        val[4] = (FieldElement *)((uint8_t *)pAddress + 14382268416);
        val[5] = (FieldElement *)((uint8_t *)pAddress + 14415822848);
        val[6] = (FieldElement *)((uint8_t *)pAddress + 14449377280);
        val[7] = (FieldElement *)((uint8_t *)pAddress + 14482931712);
        lastAccess = (FieldElement *)((uint8_t *)pAddress + 14516486144);
    }

    MemCommitPols (void * pAddress, uint64_t degree)
    {
        addr = (FieldElement *)((uint8_t *)pAddress + 0);
        step = (FieldElement *)((uint8_t *)pAddress + 16);
        mOp = (FieldElement *)((uint8_t *)pAddress + 32);
        mWr = (FieldElement *)((uint8_t *)pAddress + 48);
        val[0] = (FieldElement *)((uint8_t *)pAddress + 64);
        val[1] = (FieldElement *)((uint8_t *)pAddress + 80);
        val[2] = (FieldElement *)((uint8_t *)pAddress + 96);
        val[3] = (FieldElement *)((uint8_t *)pAddress + 112);
        val[4] = (FieldElement *)((uint8_t *)pAddress + 128);
        val[5] = (FieldElement *)((uint8_t *)pAddress + 144);
        val[6] = (FieldElement *)((uint8_t *)pAddress + 160);
        val[7] = (FieldElement *)((uint8_t *)pAddress + 176);
        lastAccess = (FieldElement *)((uint8_t *)pAddress + 192);
    }

    static uint64_t degree (void) { return 4194304; }
    static uint64_t size (void) { return 208; }
};

class MainCommitPols
{
public:
    uint32_t * A7;
    uint32_t * A6;
    uint32_t * A5;
    uint32_t * A4;
    uint32_t * A3;
    uint32_t * A2;
    uint32_t * A1;
    FieldElement * A0;
    uint32_t * B7;
    uint32_t * B6;
    uint32_t * B5;
    uint32_t * B4;
    uint32_t * B3;
    uint32_t * B2;
    uint32_t * B1;
    FieldElement * B0;
    uint32_t * C7;
    uint32_t * C6;
    uint32_t * C5;
    uint32_t * C4;
    uint32_t * C3;
    uint32_t * C2;
    uint32_t * C1;
    FieldElement * C0;
    uint32_t * D7;
    uint32_t * D6;
    uint32_t * D5;
    uint32_t * D4;
    uint32_t * D3;
    uint32_t * D2;
    uint32_t * D1;
    FieldElement * D0;
    uint32_t * E7;
    uint32_t * E6;
    uint32_t * E5;
    uint32_t * E4;
    uint32_t * E3;
    uint32_t * E2;
    uint32_t * E1;
    FieldElement * E0;
    uint32_t * SR7;
    uint32_t * SR6;
    uint32_t * SR5;
    uint32_t * SR4;
    uint32_t * SR3;
    uint32_t * SR2;
    uint32_t * SR1;
    uint32_t * SR0;
    uint32_t * CTX;
    uint16_t * SP;
    uint32_t * PC;
    uint64_t * GAS;
    uint32_t * MAXMEM;
    uint32_t * zkPC;
    uint32_t * RR;
    uint32_t * HASHPOS;
    FieldElement * CONST7;
    FieldElement * CONST6;
    FieldElement * CONST5;
    FieldElement * CONST4;
    FieldElement * CONST3;
    FieldElement * CONST2;
    FieldElement * CONST1;
    FieldElement * CONST0;
    FieldElement * FREE7;
    FieldElement * FREE6;
    FieldElement * FREE5;
    FieldElement * FREE4;
    FieldElement * FREE3;
    FieldElement * FREE2;
    FieldElement * FREE1;
    FieldElement * FREE0;
    FieldElement * inA;
    FieldElement * inB;
    FieldElement * inC;
    FieldElement * inD;
    FieldElement * inE;
    FieldElement * inSR;
    FieldElement * inFREE;
    FieldElement * inCTX;
    FieldElement * inSP;
    FieldElement * inPC;
    FieldElement * inGAS;
    FieldElement * inMAXMEM;
    FieldElement * inSTEP;
    FieldElement * inRR;
    FieldElement * inHASHPOS;
    uint8_t * setA;
    uint8_t * setB;
    uint8_t * setC;
    uint8_t * setD;
    uint8_t * setE;
    uint8_t * setSR;
    uint8_t * setCTX;
    uint8_t * setSP;
    uint8_t * setPC;
    uint8_t * setGAS;
    uint8_t * setMAXMEM;
    uint8_t * JMP;
    uint8_t * JMPC;
    uint8_t * setRR;
    uint8_t * setHASHPOS;
    uint32_t * offset;
    int32_t * incStack;
    int32_t * incCode;
    uint8_t * isStack;
    uint8_t * isCode;
    uint8_t * isMem;
    uint8_t * ind;
    uint8_t * indRR;
    uint8_t * useCTX;
    uint8_t * mOp;
    uint8_t * mWR;
    uint8_t * sWR;
    uint8_t * sRD;
    uint8_t * arith;
    uint8_t * arithEq0;
    uint8_t * arithEq1;
    uint8_t * arithEq2;
    uint8_t * arithEq3;
    uint8_t * memAlign;
    uint8_t * memAlignWR;
    uint8_t * hashK;
    uint8_t * hashKLen;
    uint8_t * hashKDigest;
    uint8_t * hashP;
    uint8_t * hashPLen;
    uint8_t * hashPDigest;
    uint8_t * bin;
    uint8_t * binOpcode;
    uint8_t * assert;
    uint8_t * opcodeRomMap;
    uint8_t * isNeg;
    uint8_t * isMaxMem;
    FieldElement * sKeyI[4];
    FieldElement * sKey[4];

    MainCommitPols (void * pAddress)
    {
        A7 = (uint32_t *)((uint8_t *)pAddress + 14550040576);
        A6 = (uint32_t *)((uint8_t *)pAddress + 14583595008);
        A5 = (uint32_t *)((uint8_t *)pAddress + 14617149440);
        A4 = (uint32_t *)((uint8_t *)pAddress + 14650703872);
        A3 = (uint32_t *)((uint8_t *)pAddress + 14684258304);
        A2 = (uint32_t *)((uint8_t *)pAddress + 14717812736);
        A1 = (uint32_t *)((uint8_t *)pAddress + 14751367168);
        A0 = (FieldElement *)((uint8_t *)pAddress + 14784921600);
        B7 = (uint32_t *)((uint8_t *)pAddress + 14818476032);
        B6 = (uint32_t *)((uint8_t *)pAddress + 14852030464);
        B5 = (uint32_t *)((uint8_t *)pAddress + 14885584896);
        B4 = (uint32_t *)((uint8_t *)pAddress + 14919139328);
        B3 = (uint32_t *)((uint8_t *)pAddress + 14952693760);
        B2 = (uint32_t *)((uint8_t *)pAddress + 14986248192);
        B1 = (uint32_t *)((uint8_t *)pAddress + 15019802624);
        B0 = (FieldElement *)((uint8_t *)pAddress + 15053357056);
        C7 = (uint32_t *)((uint8_t *)pAddress + 15086911488);
        C6 = (uint32_t *)((uint8_t *)pAddress + 15120465920);
        C5 = (uint32_t *)((uint8_t *)pAddress + 15154020352);
        C4 = (uint32_t *)((uint8_t *)pAddress + 15187574784);
        C3 = (uint32_t *)((uint8_t *)pAddress + 15221129216);
        C2 = (uint32_t *)((uint8_t *)pAddress + 15254683648);
        C1 = (uint32_t *)((uint8_t *)pAddress + 15288238080);
        C0 = (FieldElement *)((uint8_t *)pAddress + 15321792512);
        D7 = (uint32_t *)((uint8_t *)pAddress + 15355346944);
        D6 = (uint32_t *)((uint8_t *)pAddress + 15388901376);
        D5 = (uint32_t *)((uint8_t *)pAddress + 15422455808);
        D4 = (uint32_t *)((uint8_t *)pAddress + 15456010240);
        D3 = (uint32_t *)((uint8_t *)pAddress + 15489564672);
        D2 = (uint32_t *)((uint8_t *)pAddress + 15523119104);
        D1 = (uint32_t *)((uint8_t *)pAddress + 15556673536);
        D0 = (FieldElement *)((uint8_t *)pAddress + 15590227968);
        E7 = (uint32_t *)((uint8_t *)pAddress + 15623782400);
        E6 = (uint32_t *)((uint8_t *)pAddress + 15657336832);
        E5 = (uint32_t *)((uint8_t *)pAddress + 15690891264);
        E4 = (uint32_t *)((uint8_t *)pAddress + 15724445696);
        E3 = (uint32_t *)((uint8_t *)pAddress + 15758000128);
        E2 = (uint32_t *)((uint8_t *)pAddress + 15791554560);
        E1 = (uint32_t *)((uint8_t *)pAddress + 15825108992);
        E0 = (FieldElement *)((uint8_t *)pAddress + 15858663424);
        SR7 = (uint32_t *)((uint8_t *)pAddress + 15892217856);
        SR6 = (uint32_t *)((uint8_t *)pAddress + 15925772288);
        SR5 = (uint32_t *)((uint8_t *)pAddress + 15959326720);
        SR4 = (uint32_t *)((uint8_t *)pAddress + 15992881152);
        SR3 = (uint32_t *)((uint8_t *)pAddress + 16026435584);
        SR2 = (uint32_t *)((uint8_t *)pAddress + 16059990016);
        SR1 = (uint32_t *)((uint8_t *)pAddress + 16093544448);
        SR0 = (uint32_t *)((uint8_t *)pAddress + 16127098880);
        CTX = (uint32_t *)((uint8_t *)pAddress + 16160653312);
        SP = (uint16_t *)((uint8_t *)pAddress + 16194207744);
        PC = (uint32_t *)((uint8_t *)pAddress + 16202596352);
        GAS = (uint64_t *)((uint8_t *)pAddress + 16236150784);
        MAXMEM = (uint32_t *)((uint8_t *)pAddress + 16269705216);
        zkPC = (uint32_t *)((uint8_t *)pAddress + 16303259648);
        RR = (uint32_t *)((uint8_t *)pAddress + 16336814080);
        HASHPOS = (uint32_t *)((uint8_t *)pAddress + 16370368512);
        CONST7 = (FieldElement *)((uint8_t *)pAddress + 16403922944);
        CONST6 = (FieldElement *)((uint8_t *)pAddress + 16437477376);
        CONST5 = (FieldElement *)((uint8_t *)pAddress + 16471031808);
        CONST4 = (FieldElement *)((uint8_t *)pAddress + 16504586240);
        CONST3 = (FieldElement *)((uint8_t *)pAddress + 16538140672);
        CONST2 = (FieldElement *)((uint8_t *)pAddress + 16571695104);
        CONST1 = (FieldElement *)((uint8_t *)pAddress + 16605249536);
        CONST0 = (FieldElement *)((uint8_t *)pAddress + 16638803968);
        FREE7 = (FieldElement *)((uint8_t *)pAddress + 16672358400);
        FREE6 = (FieldElement *)((uint8_t *)pAddress + 16705912832);
        FREE5 = (FieldElement *)((uint8_t *)pAddress + 16739467264);
        FREE4 = (FieldElement *)((uint8_t *)pAddress + 16773021696);
        FREE3 = (FieldElement *)((uint8_t *)pAddress + 16806576128);
        FREE2 = (FieldElement *)((uint8_t *)pAddress + 16840130560);
        FREE1 = (FieldElement *)((uint8_t *)pAddress + 16873684992);
        FREE0 = (FieldElement *)((uint8_t *)pAddress + 16907239424);
        inA = (FieldElement *)((uint8_t *)pAddress + 16940793856);
        inB = (FieldElement *)((uint8_t *)pAddress + 16974348288);
        inC = (FieldElement *)((uint8_t *)pAddress + 17007902720);
        inD = (FieldElement *)((uint8_t *)pAddress + 17041457152);
        inE = (FieldElement *)((uint8_t *)pAddress + 17075011584);
        inSR = (FieldElement *)((uint8_t *)pAddress + 17108566016);
        inFREE = (FieldElement *)((uint8_t *)pAddress + 17142120448);
        inCTX = (FieldElement *)((uint8_t *)pAddress + 17175674880);
        inSP = (FieldElement *)((uint8_t *)pAddress + 17209229312);
        inPC = (FieldElement *)((uint8_t *)pAddress + 17242783744);
        inGAS = (FieldElement *)((uint8_t *)pAddress + 17276338176);
        inMAXMEM = (FieldElement *)((uint8_t *)pAddress + 17309892608);
        inSTEP = (FieldElement *)((uint8_t *)pAddress + 17343447040);
        inRR = (FieldElement *)((uint8_t *)pAddress + 17377001472);
        inHASHPOS = (FieldElement *)((uint8_t *)pAddress + 17410555904);
        setA = (uint8_t *)((uint8_t *)pAddress + 17444110336);
        setB = (uint8_t *)((uint8_t *)pAddress + 17448304640);
        setC = (uint8_t *)((uint8_t *)pAddress + 17452498944);
        setD = (uint8_t *)((uint8_t *)pAddress + 17456693248);
        setE = (uint8_t *)((uint8_t *)pAddress + 17460887552);
        setSR = (uint8_t *)((uint8_t *)pAddress + 17465081856);
        setCTX = (uint8_t *)((uint8_t *)pAddress + 17469276160);
        setSP = (uint8_t *)((uint8_t *)pAddress + 17473470464);
        setPC = (uint8_t *)((uint8_t *)pAddress + 17477664768);
        setGAS = (uint8_t *)((uint8_t *)pAddress + 17481859072);
        setMAXMEM = (uint8_t *)((uint8_t *)pAddress + 17486053376);
        JMP = (uint8_t *)((uint8_t *)pAddress + 17490247680);
        JMPC = (uint8_t *)((uint8_t *)pAddress + 17494441984);
        setRR = (uint8_t *)((uint8_t *)pAddress + 17498636288);
        setHASHPOS = (uint8_t *)((uint8_t *)pAddress + 17502830592);
        offset = (uint32_t *)((uint8_t *)pAddress + 17507024896);
        incStack = (int32_t *)((uint8_t *)pAddress + 17540579328);
        incCode = (int32_t *)((uint8_t *)pAddress + 17557356544);
        isStack = (uint8_t *)((uint8_t *)pAddress + 17574133760);
        isCode = (uint8_t *)((uint8_t *)pAddress + 17578328064);
        isMem = (uint8_t *)((uint8_t *)pAddress + 17582522368);
        ind = (uint8_t *)((uint8_t *)pAddress + 17586716672);
        indRR = (uint8_t *)((uint8_t *)pAddress + 17590910976);
        useCTX = (uint8_t *)((uint8_t *)pAddress + 17595105280);
        mOp = (uint8_t *)((uint8_t *)pAddress + 17599299584);
        mWR = (uint8_t *)((uint8_t *)pAddress + 17603493888);
        sWR = (uint8_t *)((uint8_t *)pAddress + 17607688192);
        sRD = (uint8_t *)((uint8_t *)pAddress + 17611882496);
        arith = (uint8_t *)((uint8_t *)pAddress + 17616076800);
        arithEq0 = (uint8_t *)((uint8_t *)pAddress + 17620271104);
        arithEq1 = (uint8_t *)((uint8_t *)pAddress + 17624465408);
        arithEq2 = (uint8_t *)((uint8_t *)pAddress + 17628659712);
        arithEq3 = (uint8_t *)((uint8_t *)pAddress + 17632854016);
        memAlign = (uint8_t *)((uint8_t *)pAddress + 17637048320);
        memAlignWR = (uint8_t *)((uint8_t *)pAddress + 17641242624);
        hashK = (uint8_t *)((uint8_t *)pAddress + 17645436928);
        hashKLen = (uint8_t *)((uint8_t *)pAddress + 17649631232);
        hashKDigest = (uint8_t *)((uint8_t *)pAddress + 17653825536);
        hashP = (uint8_t *)((uint8_t *)pAddress + 17658019840);
        hashPLen = (uint8_t *)((uint8_t *)pAddress + 17662214144);
        hashPDigest = (uint8_t *)((uint8_t *)pAddress + 17666408448);
        bin = (uint8_t *)((uint8_t *)pAddress + 17670602752);
        binOpcode = (uint8_t *)((uint8_t *)pAddress + 17674797056);
        assert = (uint8_t *)((uint8_t *)pAddress + 17678991360);
        opcodeRomMap = (uint8_t *)((uint8_t *)pAddress + 17683185664);
        isNeg = (uint8_t *)((uint8_t *)pAddress + 17687379968);
        isMaxMem = (uint8_t *)((uint8_t *)pAddress + 17691574272);
        sKeyI[0] = (FieldElement *)((uint8_t *)pAddress + 17695768576);
        sKeyI[1] = (FieldElement *)((uint8_t *)pAddress + 17729323008);
        sKeyI[2] = (FieldElement *)((uint8_t *)pAddress + 17762877440);
        sKeyI[3] = (FieldElement *)((uint8_t *)pAddress + 17796431872);
        sKey[0] = (FieldElement *)((uint8_t *)pAddress + 17829986304);
        sKey[1] = (FieldElement *)((uint8_t *)pAddress + 17863540736);
        sKey[2] = (FieldElement *)((uint8_t *)pAddress + 17897095168);
        sKey[3] = (FieldElement *)((uint8_t *)pAddress + 17930649600);
    }

    MainCommitPols (void * pAddress, uint64_t degree)
    {
        A7 = (uint32_t *)((uint8_t *)pAddress + 0);
        A6 = (uint32_t *)((uint8_t *)pAddress + 16);
        A5 = (uint32_t *)((uint8_t *)pAddress + 32);
        A4 = (uint32_t *)((uint8_t *)pAddress + 48);
        A3 = (uint32_t *)((uint8_t *)pAddress + 64);
        A2 = (uint32_t *)((uint8_t *)pAddress + 80);
        A1 = (uint32_t *)((uint8_t *)pAddress + 96);
        A0 = (FieldElement *)((uint8_t *)pAddress + 112);
        B7 = (uint32_t *)((uint8_t *)pAddress + 128);
        B6 = (uint32_t *)((uint8_t *)pAddress + 144);
        B5 = (uint32_t *)((uint8_t *)pAddress + 160);
        B4 = (uint32_t *)((uint8_t *)pAddress + 176);
        B3 = (uint32_t *)((uint8_t *)pAddress + 192);
        B2 = (uint32_t *)((uint8_t *)pAddress + 208);
        B1 = (uint32_t *)((uint8_t *)pAddress + 224);
        B0 = (FieldElement *)((uint8_t *)pAddress + 240);
        C7 = (uint32_t *)((uint8_t *)pAddress + 256);
        C6 = (uint32_t *)((uint8_t *)pAddress + 272);
        C5 = (uint32_t *)((uint8_t *)pAddress + 288);
        C4 = (uint32_t *)((uint8_t *)pAddress + 304);
        C3 = (uint32_t *)((uint8_t *)pAddress + 320);
        C2 = (uint32_t *)((uint8_t *)pAddress + 336);
        C1 = (uint32_t *)((uint8_t *)pAddress + 352);
        C0 = (FieldElement *)((uint8_t *)pAddress + 368);
        D7 = (uint32_t *)((uint8_t *)pAddress + 384);
        D6 = (uint32_t *)((uint8_t *)pAddress + 400);
        D5 = (uint32_t *)((uint8_t *)pAddress + 416);
        D4 = (uint32_t *)((uint8_t *)pAddress + 432);
        D3 = (uint32_t *)((uint8_t *)pAddress + 448);
        D2 = (uint32_t *)((uint8_t *)pAddress + 464);
        D1 = (uint32_t *)((uint8_t *)pAddress + 480);
        D0 = (FieldElement *)((uint8_t *)pAddress + 496);
        E7 = (uint32_t *)((uint8_t *)pAddress + 512);
        E6 = (uint32_t *)((uint8_t *)pAddress + 528);
        E5 = (uint32_t *)((uint8_t *)pAddress + 544);
        E4 = (uint32_t *)((uint8_t *)pAddress + 560);
        E3 = (uint32_t *)((uint8_t *)pAddress + 576);
        E2 = (uint32_t *)((uint8_t *)pAddress + 592);
        E1 = (uint32_t *)((uint8_t *)pAddress + 608);
        E0 = (FieldElement *)((uint8_t *)pAddress + 624);
        SR7 = (uint32_t *)((uint8_t *)pAddress + 640);
        SR6 = (uint32_t *)((uint8_t *)pAddress + 656);
        SR5 = (uint32_t *)((uint8_t *)pAddress + 672);
        SR4 = (uint32_t *)((uint8_t *)pAddress + 688);
        SR3 = (uint32_t *)((uint8_t *)pAddress + 704);
        SR2 = (uint32_t *)((uint8_t *)pAddress + 720);
        SR1 = (uint32_t *)((uint8_t *)pAddress + 736);
        SR0 = (uint32_t *)((uint8_t *)pAddress + 752);
        CTX = (uint32_t *)((uint8_t *)pAddress + 768);
        SP = (uint16_t *)((uint8_t *)pAddress + 784);
        PC = (uint32_t *)((uint8_t *)pAddress + 788);
        GAS = (uint64_t *)((uint8_t *)pAddress + 804);
        MAXMEM = (uint32_t *)((uint8_t *)pAddress + 820);
        zkPC = (uint32_t *)((uint8_t *)pAddress + 836);
        RR = (uint32_t *)((uint8_t *)pAddress + 852);
        HASHPOS = (uint32_t *)((uint8_t *)pAddress + 868);
        CONST7 = (FieldElement *)((uint8_t *)pAddress + 884);
        CONST6 = (FieldElement *)((uint8_t *)pAddress + 900);
        CONST5 = (FieldElement *)((uint8_t *)pAddress + 916);
        CONST4 = (FieldElement *)((uint8_t *)pAddress + 932);
        CONST3 = (FieldElement *)((uint8_t *)pAddress + 948);
        CONST2 = (FieldElement *)((uint8_t *)pAddress + 964);
        CONST1 = (FieldElement *)((uint8_t *)pAddress + 980);
        CONST0 = (FieldElement *)((uint8_t *)pAddress + 996);
        FREE7 = (FieldElement *)((uint8_t *)pAddress + 1012);
        FREE6 = (FieldElement *)((uint8_t *)pAddress + 1028);
        FREE5 = (FieldElement *)((uint8_t *)pAddress + 1044);
        FREE4 = (FieldElement *)((uint8_t *)pAddress + 1060);
        FREE3 = (FieldElement *)((uint8_t *)pAddress + 1076);
        FREE2 = (FieldElement *)((uint8_t *)pAddress + 1092);
        FREE1 = (FieldElement *)((uint8_t *)pAddress + 1108);
        FREE0 = (FieldElement *)((uint8_t *)pAddress + 1124);
        inA = (FieldElement *)((uint8_t *)pAddress + 1140);
        inB = (FieldElement *)((uint8_t *)pAddress + 1156);
        inC = (FieldElement *)((uint8_t *)pAddress + 1172);
        inD = (FieldElement *)((uint8_t *)pAddress + 1188);
        inE = (FieldElement *)((uint8_t *)pAddress + 1204);
        inSR = (FieldElement *)((uint8_t *)pAddress + 1220);
        inFREE = (FieldElement *)((uint8_t *)pAddress + 1236);
        inCTX = (FieldElement *)((uint8_t *)pAddress + 1252);
        inSP = (FieldElement *)((uint8_t *)pAddress + 1268);
        inPC = (FieldElement *)((uint8_t *)pAddress + 1284);
        inGAS = (FieldElement *)((uint8_t *)pAddress + 1300);
        inMAXMEM = (FieldElement *)((uint8_t *)pAddress + 1316);
        inSTEP = (FieldElement *)((uint8_t *)pAddress + 1332);
        inRR = (FieldElement *)((uint8_t *)pAddress + 1348);
        inHASHPOS = (FieldElement *)((uint8_t *)pAddress + 1364);
        setA = (uint8_t *)((uint8_t *)pAddress + 1380);
        setB = (uint8_t *)((uint8_t *)pAddress + 1382);
        setC = (uint8_t *)((uint8_t *)pAddress + 1384);
        setD = (uint8_t *)((uint8_t *)pAddress + 1386);
        setE = (uint8_t *)((uint8_t *)pAddress + 1388);
        setSR = (uint8_t *)((uint8_t *)pAddress + 1390);
        setCTX = (uint8_t *)((uint8_t *)pAddress + 1392);
        setSP = (uint8_t *)((uint8_t *)pAddress + 1394);
        setPC = (uint8_t *)((uint8_t *)pAddress + 1396);
        setGAS = (uint8_t *)((uint8_t *)pAddress + 1398);
        setMAXMEM = (uint8_t *)((uint8_t *)pAddress + 1400);
        JMP = (uint8_t *)((uint8_t *)pAddress + 1402);
        JMPC = (uint8_t *)((uint8_t *)pAddress + 1404);
        setRR = (uint8_t *)((uint8_t *)pAddress + 1406);
        setHASHPOS = (uint8_t *)((uint8_t *)pAddress + 1408);
        offset = (uint32_t *)((uint8_t *)pAddress + 1410);
        incStack = (int32_t *)((uint8_t *)pAddress + 1426);
        incCode = (int32_t *)((uint8_t *)pAddress + 1434);
        isStack = (uint8_t *)((uint8_t *)pAddress + 1442);
        isCode = (uint8_t *)((uint8_t *)pAddress + 1444);
        isMem = (uint8_t *)((uint8_t *)pAddress + 1446);
        ind = (uint8_t *)((uint8_t *)pAddress + 1448);
        indRR = (uint8_t *)((uint8_t *)pAddress + 1450);
        useCTX = (uint8_t *)((uint8_t *)pAddress + 1452);
        mOp = (uint8_t *)((uint8_t *)pAddress + 1454);
        mWR = (uint8_t *)((uint8_t *)pAddress + 1456);
        sWR = (uint8_t *)((uint8_t *)pAddress + 1458);
        sRD = (uint8_t *)((uint8_t *)pAddress + 1460);
        arith = (uint8_t *)((uint8_t *)pAddress + 1462);
        arithEq0 = (uint8_t *)((uint8_t *)pAddress + 1464);
        arithEq1 = (uint8_t *)((uint8_t *)pAddress + 1466);
        arithEq2 = (uint8_t *)((uint8_t *)pAddress + 1468);
        arithEq3 = (uint8_t *)((uint8_t *)pAddress + 1470);
        memAlign = (uint8_t *)((uint8_t *)pAddress + 1472);
        memAlignWR = (uint8_t *)((uint8_t *)pAddress + 1474);
        hashK = (uint8_t *)((uint8_t *)pAddress + 1476);
        hashKLen = (uint8_t *)((uint8_t *)pAddress + 1478);
        hashKDigest = (uint8_t *)((uint8_t *)pAddress + 1480);
        hashP = (uint8_t *)((uint8_t *)pAddress + 1482);
        hashPLen = (uint8_t *)((uint8_t *)pAddress + 1484);
        hashPDigest = (uint8_t *)((uint8_t *)pAddress + 1486);
        bin = (uint8_t *)((uint8_t *)pAddress + 1488);
        binOpcode = (uint8_t *)((uint8_t *)pAddress + 1490);
        assert = (uint8_t *)((uint8_t *)pAddress + 1492);
        opcodeRomMap = (uint8_t *)((uint8_t *)pAddress + 1494);
        isNeg = (uint8_t *)((uint8_t *)pAddress + 1496);
        isMaxMem = (uint8_t *)((uint8_t *)pAddress + 1498);
        sKeyI[0] = (FieldElement *)((uint8_t *)pAddress + 1500);
        sKeyI[1] = (FieldElement *)((uint8_t *)pAddress + 1516);
        sKeyI[2] = (FieldElement *)((uint8_t *)pAddress + 1532);
        sKeyI[3] = (FieldElement *)((uint8_t *)pAddress + 1548);
        sKey[0] = (FieldElement *)((uint8_t *)pAddress + 1564);
        sKey[1] = (FieldElement *)((uint8_t *)pAddress + 1580);
        sKey[2] = (FieldElement *)((uint8_t *)pAddress + 1596);
        sKey[3] = (FieldElement *)((uint8_t *)pAddress + 1612);
    }

    static uint64_t degree (void) { return 4194304; }
    static uint64_t size (void) { return 1628; }
};

class CommitPols
{
public:
    Byte4CommitPols Byte4;
    MemAlignCommitPols MemAlign;
    ArithCommitPols Arith;
    BinaryCommitPols Binary;
    PoseidonGCommitPols PoseidonG;
    PaddingPGCommitPols PaddingPG;
    StorageCommitPols Storage;
    NormGate9CommitPols NormGate9;
    KeccakFCommitPols KeccakF;
    Nine2OneCommitPols Nine2One;
    PaddingKKBitCommitPols PaddingKKBit;
    PaddingKKCommitPols PaddingKK;
    MemCommitPols Mem;
    MainCommitPols Main;

    CommitPols (void * pAddress) : Byte4(pAddress), MemAlign(pAddress), Arith(pAddress), Binary(pAddress), PoseidonG(pAddress), PaddingPG(pAddress), Storage(pAddress), NormGate9(pAddress), KeccakF(pAddress), Nine2One(pAddress), PaddingKKBit(pAddress), PaddingKK(pAddress), Mem(pAddress), Main(pAddress) {}

    static uint64_t size (void) { return 17964204032; }
};

#endif // COMMIT_POLS_HPP
