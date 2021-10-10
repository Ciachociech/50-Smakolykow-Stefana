#include "..\..\include\managers\SteeringManager.h"

SteeringManager::SteeringManager() : combo1(0), combo2(0) {}

SteeringManager::~SteeringManager() {}

//Returns performed action depending of pressed key
keyAction SteeringManager::keyboardMovement(int& x, int& y, SDL_Keycode keycode)
{
    //check these evil combos
    checkMischievousCombo(keycode);
    checkAnotherEvilCombo(keycode);

    if (keycode == SDLK_ESCAPE) { return keyAction::pauseScene; }                                               //check clicking ESC (pause activating)

    //character moving (up, down, left, right)
    if (keycode == SDLK_w || keycode == SDLK_UP) { y = -2; return keyAction::movingScene; }
    else if (keycode == SDLK_s || keycode == SDLK_DOWN) { y = 2; return keyAction::movingScene; }
    if (keycode == SDLK_a || keycode == SDLK_LEFT) 
    { 
        if (combo1 == 10) { return keyAction::mischievousCombo; }                                               //end of mischievous combo
        else { x = -2; return keyAction::movingScene; }
    }
    else if (keycode == SDLK_d || keycode == SDLK_RIGHT) { x = 2; return keyAction::movingScene; }

    //other character actions
    if (keycode == SDLK_l) { return keyAction::diggingScene; }                                                  //digging action
    if (keycode == SDLK_k) { return keyAction::powerupUsingScene; }                                             //power-up action
    if (keycode == SDLK_p) { return keyAction::steeringHelpScene; }                                             //invoking help window
    if (combo2 == 6 && keycode == SDLK_n) { return keyAction::anotherEvilCombo; }                               //end of another evil combo

    return keyAction::none;                                                                                     //if none of them, return none
}

//Returns performed action depending of pressed key
keyAction SteeringManager::keyboardMenu(SDL_Keycode keycode)
{
    //moving up/down (choose menu option)
    if (keycode == SDLK_w || keycode == SDLK_UP) { return keyAction::prevMenu; }
    else if (keycode == SDLK_s || keycode == SDLK_DOWN) { return keyAction::nextMenu; }

    //change value of option
    if (keycode == SDLK_a || keycode == SDLK_LEFT) { return keyAction::lessMenu; }
    else if (keycode == SDLK_d || keycode == SDLK_RIGHT) { return keyAction::moreMenu; }

    //enter to menu or go back
    if (keycode == SDLK_SPACE || keycode == SDLK_RETURN) { return keyAction::enterMenu; }
    if (keycode == SDLK_ESCAPE) { return keyAction::goBackMenu; }

    return keyAction::none;
}

//Returns performed action depending of pressed key or changes value of string
keyAction SteeringManager::keyboardString(std::string& name, SDL_Event event)
{
    if (event.key.keysym.sym == SDLK_RETURN) { return keyAction::acceptName; }                                               //accept name and save score
    if (event.key.keysym.sym == SDLK_ESCAPE) { return keyAction::rejectName; }                                               //cancel saving last score
    if (event.key.keysym.sym == SDLK_BACKSPACE && name.length() > 0) { name.pop_back(); return keyAction::backspaceName; }   //deleting last character

    if (event.type == SDL_TEXTINPUT && name.length() < 16) 
    { 
        name += event.text.text; 
        if (name[name.size() - 1] == ' ') { name.pop_back(); }
    } 
    return keyAction::none;
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
