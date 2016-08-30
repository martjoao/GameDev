#ifndef _RENDERABLE_ENTITY_H
#define _RENDERABLE_ENTITY_H

#include "colidableEntity.h"
#include "renderObject.h"
#include "renderManager.h"

/*
    An entity class that may be rendered

    For the purposes of this implementation, 
    every entity that is renderable is considered
    to be collidable
*/
class RenderableEntity : public ColidableEntity
{
protected:
    //specifies the graphical properties of the entity
    RenderObject * obj;

public:
    RenderableEntity(RenderObject& o);
    virtual ~RenderableEntity();

    //overrides move method to enable graphical representation of entity to change positions
    virtual void move(glm::vec3 displacement);
    //overrides scale method to enable graphical representation of entity to change size
    virtual void scale(glm::vec3 factor);
    //renderobject getter and setter
    RenderObject* getRenderObject();
    void setRenderObject(RenderObject& o);

    //draws an object
    virtual void draw();
};

#endif