#ifndef _INPUT_MANAGER_H
#define _INPUT_MANAGER_H

#include <SDL.h>
#include <iostream>
#include <map>

/*
    Handles user input (keyboard/mouse)
*/
class InputManager
{
public:
    InputManager();
    ~InputManager();

//    void setKeyCallback(void(*keyInput) (const SDL_Keycode));
    void setKeyCallback(SDL_Keycode k, void(*keyInput) ());
    void setMouseCallback(void(*mouseInput) (const SDL_Event& e));

    bool init();
    bool update();
    void shutdown();

protected:
    SDL_Event inputEvent;

    //pointer to a callback function that handles keyboard input
    void(*keyInput) (const SDL_Keycode);
    //pointer to a callback function that handles mouse input
    void(*mouseInput) (const SDL_Event& e);




    //maps a key to a function pointer
    std::map<SDL_Keycode, void(*)()> action;
    
    //maps a key to a state
    std::map<SDL_Keycode, bool> isPressed;
};

#endif