#include "OverworldRandomizer.h"

OverworldRandomizer::OverworldRandomizer()
{
    gen.seed(std::chrono::high_resolution_clock::now().time_since_epoch().count());
}

OverworldRandomizer::~OverworldRandomizer() {}

SDL_Color OverworldRandomizer::randomColor()
{
    std::uniform_int_distribution<int> dist7(128, 255);
    std::uniform_real_distribution<float> distF(-4.f, 4.f);

    SDL_Color clr;
    clr.r = dist7(gen);
    clr.g = dist7(gen);
    clr.b = dist7(gen);
    //clr.a = 0xC0;
    clr.a = 0xFF;
    return clr;
}
int OverworldRandomizer::randomNumber(int min, int max)
{
    std::uniform_int_distribution<int> distI(min, max);
    return distI(gen);
}

void OverworldRandomizer::randomCoordsTreasure(int& x, int& y, int tileW, int tileH)
{
    bool isTaboo;
    do
    {
        isTaboo = false;
        x = 584 + 32 * randomNumber(0, 21 - tileW), y = 24 + 32 * randomNumber(0, 21 - tileH);

        //Near internal walls - prevent spawn tidbits in wall
        if ((x >= 776 - 32 * tileW && x <= 840) || (x >= 1032 - 32 * tileW && x <= 1096))
        {
            if ((y >= 216 - 32 * tileH && y <= 280) || (y >= 472 - 32 * tileH && y <= 536))
            { isTaboo = true; }
        }
    } while (isTaboo);
}
