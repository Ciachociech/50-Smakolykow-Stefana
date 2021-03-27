#include "SteeringManager.h"

SteeringManager::SteeringManager() : combo1(0), combo2(0) {}

SteeringManager::~SteeringManager() {}

//Returns performed action depending of pressed key
keyAction SteeringManager::keyboardMovement(int& x, int& y, SDL_Keycode keycode)
{
    //check these evil combos
    checkMischievousCombo(keycode);
    checkAnotherEvilCombo(keycode);

    //character moving (up, down, left, right)
    if (keycode == SDLK_w || keycode == SDLK_UP) { y = -2; return keyAction::moving; }
    else if (keycode == SDLK_s || keycode == SDLK_DOWN) { y = 2; return keyAction::moving; }
    if (keycode == SDLK_a || keycode == SDLK_LEFT) 
    { 
        if (combo1 == 10) { return keyAction::mischievous; }                                //end of mischievous combo
        else { x = -2; return keyAction::moving; }
    }
    else if (keycode == SDLK_d || keycode == SDLK_RIGHT) { x = 2; return keyAction::moving; }

    if (keycode == SDLK_l) { return keyAction::digging; }                                   //digging action
    if (keycode == SDLK_k) { return keyAction::powerupUsing; }                              //power-up action
    if (keycode == SDLK_p) { return keyAction::steeringHelp; }                              //invoking help window
    if (combo2 == 6 && keycode == SDLK_n) { return keyAction::anotherEvil; }                //end of another evil combo

    return keyAction::none;                                                                 //if none of them, return none
}

//checks the continuing of mischievous combo
void SteeringManager::checkMischievousCombo(SDL_Keycode keycode)
{
    //if one of following conditions is true, increase the proper combo counter
    if (combo1 < 2 && (keycode == SDLK_w || keycode == SDLK_UP)) { combo1++; return; }
    else if (combo1 < 4 && (keycode == SDLK_s || keycode == SDLK_DOWN)) { combo1++; return; }
    else if ((combo1 == 4 || combo1 == 6) && (keycode == SDLK_a || keycode == SDLK_LEFT)) { combo1++; return; }
    else if ((combo1 == 5 || combo1 == 7) && (keycode == SDLK_d || keycode == SDLK_RIGHT)) { combo1++; return; }
    else if (combo1 == 8 && keycode == SDLK_b) { combo1++; return; }
    else if (combo1 == 9 && keycode == SDLK_a) { combo1++; return; }

    combo1 = 0;                                                                             //if none of previous conditions is true, reset a combo counter
}

//checks the continuing of another evil combo
void SteeringManager::checkAnotherEvilCombo(SDL_Keycode keycode)
{
    //if one of following conditions is true, increase the proper combo counter
    if (combo2 == 0 && keycode == SDLK_s) { combo2++; return; }
    else if (combo2 == 1 && keycode == SDLK_t) { combo2++; return; }
    else if (combo2 == 2 && keycode == SDLK_e) { combo2++; return; }
    else if (combo2 == 3 && keycode == SDLK_f) { combo2++; return; }
    else if (combo2 == 4 && keycode == SDLK_a) { combo2++; return; }
    else if (combo2 == 5 && keycode == SDLK_n) { combo2++; return; }

    combo2 = 0;                                                                             //if none of previous conditions is true, reset a combo counter
}
