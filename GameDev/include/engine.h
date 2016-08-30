#ifndef _ENGINE_H
#define _ENGINE_H

#include <iostream>

#include "windowManager.h"
#include "renderManager.h"
#include "inputManager.h"
#include "resourceManager.h"
#include "physicsManager.h"
#include "aiManager.h"
#include "hudManager.h"

/*
    Main engine class, with instances of managers
    and init/run/shutdown routines for the game   
 */
class Engine
{
protected:
    int sWidth;
    int sHeight;
    double fps;

    //initial objects on scene
    virtual void createObjects();
    //whatever is in this function will be called periodically (start of every loop)
    virtual void customPeriodic();

    //instances of managers

    WindowManager   * windowMan;
    ResourceManager * resourceMan;
    InputManager    * inputMan;
    RenderManager   * renderMan;
    PhysicsManager  * physicsMan;
    AIManager       * aiMan;
    HUDManager      * hudMan;

public:
    //set key callbacks
    void keyCallback(SDL_Keycode c, void(*k) ());
    //set collision response
    void collisionCallback(void(*c) (ColidableEntity* a, ColidableEntity* b, glm::vec3 dir));
    //set mouse input response
    void mouseCallback(void(*m) (const SDL_Event& e));
    
    //matrices
    void setView(glm::mat4);
    void setProj(glm::mat4);

public:
    Engine(int, int);
    ~Engine();

    //startup components
    bool startup();
    //game loop
    void run();
    //cleanup environment
    bool shutdown();
};

#endif