#ifndef _WINDOW_MANAGER_H
#define _WINDOW_MANAGER_H

#include <SDL.h>
#include <iostream>

/*
    Handles creation of a window and SDL initialisation
*/
class WindowManager
{
public:
    WindowManager(int width, int height);
    ~WindowManager();

    //returns a reference to the current window
    static SDL_Window* getWindow();
    
    //initialises SDL and an openGL context
    bool init();
    void update();
    //deletes the window
    void shutdown();
    
protected:
    int screenWidth;
    int screenHeight;

    static SDL_Window* window;
    static SDL_GLContext glContext;
};

#endif
