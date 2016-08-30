#ifndef _HUD_MANAGER_H
#define _HUD_MANAGER_H

#include <SDL.h>

#include "mesh.h"
#include "shader.h"

#include <glm\mat4x4.hpp>
#include <glm\vec3.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\matrix_transform.hpp>


#include "windowManager.h"


#include <iostream>
#include <vector>
#include <list>
#include "hudEntity.h"

class HUDEntity;

/*
    Handles Rendering of HUDEntities
*/
class HUDManager
{
public:
    HUDManager();
    ~HUDManager();

    static void addEntity(HUDEntity & o);
    static void removeEntity(HUDEntity * o);
    static void shutdownEntities();

    void renderHUD();

    //sets up any opengl configuration required
    bool init();
    //renders the hud
    void update();
    //cleanup - clear list of hudEntities
    void shutdown();


public:
    //list of HUDEntities
    static list<HUDEntity *> hudObjects;
};

#endif