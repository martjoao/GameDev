#ifndef _HUD_ENTITY_H
#define _HUD_ENTITY_H

#include "renderObject.h"
#include "gameEntity.h"
#include "hudManager.h"
#include "resourceManager.h"

enum HUDtype
{
    TEXTURE = 0,
    TEXT    
};

/*
    Class for HUD elements. These may be defined as text or textures
    HUDEntities are always a square from -1 to 1 in both X and Y axis 
        (they might be scaled or moved)
*/
class HUDEntity
{
protected:

    //specifies the graphical properties of the entity
    RenderObject * obj;
    HUDtype hudtype;

public:
    HUDEntity(string tex, HUDtype t = TEXTURE);
    virtual ~HUDEntity();

    void move(glm::vec3 displacement);
    void scale(glm::vec3 factor);
    void rotate(float degrees, glm::vec3 around);

    //renderobject getter and setter
    RenderObject* getRenderObject();
    void setRenderObject(RenderObject& o);

    //draws an object
    void draw();
};

#endif