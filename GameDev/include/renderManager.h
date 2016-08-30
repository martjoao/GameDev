#ifndef _RENDER_MANAGER_H
#define _RENDER_MANAGER_H

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
#include "renderableEntity.h"
class RenderableEntity;

/*
    Handles Rendering
*/
class RenderManager
{
public:
    RenderManager();
    ~RenderManager();

    //add a RenderableEntity to a list of RenderableEntities
    static void addEntity(RenderableEntity & o);
    static void removeEntity(RenderableEntity * o);


    //renders the scene (as described on the static list of renderableEntities)
    void renderScene();

    //view matrix management
    static void setViewMatrix(glm::mat4 vm);
    static glm::mat4 getViewMatrix();
    
    //projection matrix management
    static void setProjMatrix(glm::mat4 pm);
    static glm::mat4 getProjMatrix();

    //sets up any opengl configuration required
    bool init();
    //renders the scene
    void update();
    //cleanup - clear list of renderableEntities
    void shutdown();

       
protected:
    //list of renderableEntities describing the scene
    static list<RenderableEntity *> objects;

    //light source (directional)
    static glm::vec3 light_source;

    //camera and projection matrices
    static glm::mat4 viewMatrix;
    static glm::mat4 projMatrix;

};

#endif