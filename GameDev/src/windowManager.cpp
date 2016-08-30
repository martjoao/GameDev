#include "windowManager.h"

SDL_Window* WindowManager::window = NULL;
SDL_GLContext WindowManager::glContext;

WindowManager::WindowManager(int width, int height)
{
        screenWidth = width;
        screenHeight = height;

        window = NULL;
}

WindowManager::~WindowManager()
{
}

SDL_Window* WindowManager::getWindow()
{
    return window;
}

bool WindowManager::init()
{
    //initialise SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        std::cout << "Call to SDL_Init failed: " << SDL_GetError() << "\n";
        return false;
    }

    //create window
    window = SDL_CreateWindow("Computer Games Development", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    if (!window)
    {
        std::cout << "Call to SDL_CreateWindow: " << SDL_GetError() << "\n";
        return false;
    }

    //opengl version 2.1
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

    //setup opengl context
    glContext = SDL_GL_CreateContext(window);

    if (glContext == NULL)
    {
        std::cout << "Call to SDL_GL_CreateContext failed: " << SDL_GetError() << "\n";
        return false;
    }


    return true;
}

void WindowManager::shutdown()
{
    //destroy SDL window
    SDL_DestroyWindow(window);
    window = NULL;
}