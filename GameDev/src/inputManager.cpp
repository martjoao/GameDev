#include "inputManager.h"

InputManager::InputManager()
{
    keyInput = NULL;
    mouseInput = NULL;
}

InputManager::~InputManager()
{

}

void InputManager::setKeyCallback(SDL_Keycode c, void(*k) ())
{
    //keyInput = k;
    action.insert(std::pair<SDL_Keycode, void(*)()>(c, k));
    isPressed.insert(std::pair<SDL_Keycode, bool>(c, false));
}

void InputManager::setMouseCallback(void(*m) (const SDL_Event& e))
{
    mouseInput = m;
}


bool InputManager::init()
{
    return true;
}

bool InputManager::update()
{
    if (SDL_PollEvent(&inputEvent))
    {
        if (inputEvent.type == SDL_QUIT)
        {
            std::cout << "QUIT SIGNAL RECEIVED";
            return false;
        }

        if (inputEvent.type == SDL_KEYDOWN)
        {
            if (isPressed.count(inputEvent.key.keysym.sym) != 0)
            {
                isPressed[inputEvent.key.keysym.sym] = true;
            }
        }
        if (inputEvent.type == SDL_KEYUP)
        {
            if (isPressed.count(inputEvent.key.keysym.sym) != 0)
            {
                isPressed[inputEvent.key.keysym.sym] = false;
            }
        }

        if (inputEvent.type == SDL_MOUSEBUTTONDOWN)
        {
            if (mouseInput)
            {
                mouseInput(inputEvent);
            }
        }
    }


    for (std::map<SDL_Keycode, bool>::iterator i = isPressed.begin(); i != isPressed.end(); ++i) {
        if (i->second)
        {
            action[i->first]();
        }
    }
    return true;
}

void InputManager::shutdown()
{

}