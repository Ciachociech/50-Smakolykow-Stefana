#include "..\..\include\basics\OverworldRandomizer.h"

OverworldRandomizer::OverworldRandomizer()
{
    gen.seed(std::chrono::high_resolution_clock::now().time_since_epoch().count());             //seed generating (depending of time)
}

OverworldRandomizer::~OverworldRandomizer() {}

SDL_Color OverworldRandomizer::randomColor()
{
    std::uniform_int_distribution<int> dist7(128, 255);                                         //setting R,G,B range values

    //setting random color
    SDL_Color clr;
    clr.r = dist7(gen);
    clr.g = dist7(gen);
    clr.b = dist7(gen);
    //clr.a = 0xC0;
    clr.a = 0xFF;
    return clr;
}

//randomize and return a number in specific range (between min and max)
int OverworldRandomizer::randomNumber(int min, int max)
{
    std::uniform_int_distribution<int> distI(min, max);
    return distI(gen);
}

//setting coords of treasure on scene
void OverworldRandomizer::randomCoordsTreasure(int& x, int& y, int tileW, int tileH)
{
    bool isTaboo;                                                                                   //flag setting true, until all conditions are valid
    //do until coords are alright
    do
    {
        isTaboo = false;                                                                            //changed to false by bad condition
        //random coords between external walls (including size of object)
        x = 584 + 32 * randomNumber(0, 21 - tileW), y = 24 + 32 * randomNumber(0, 21 - tileH);

        //If treasure is near internal walls - prevent spawn in wall
        if ((x >= 776 - 32 * tileW && x <= 840) || (x >= 1032 - 32 * tileW && x <= 1096))
        {
            if ((y >= 216 - 32 * tileH && y <= 280) || (y >= 472 - 32 * tileH && y <= 536)) { isTaboo = true; }
        }
    } while (isTaboo);
}
