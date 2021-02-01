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

void OverworldRandomizer::randomCoordsTreasure(int& x, int& y)
{
    bool isTaboo;
    do
    {
        isTaboo = false;
        x = 584 + 32 * randomNumber(0, 19), y = 24 + 32 * randomNumber(0, 19);

        //Near internal walls
        if ((x >= 712 && x <= 840) || (x >= 968 && x <= 1096))
        {
            if ((y >= 152 && y <= 280) || (y >= 408 && y <= 536))
            { isTaboo = true; }
        }
    } while (isTaboo);
}
