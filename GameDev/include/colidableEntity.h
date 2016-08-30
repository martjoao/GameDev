#ifndef _COLIDABLE_ENTITY_H
#define _COLIDABLE_ENTITY_H

#include <iostream>
#include "gameEntity.h"
#include "AABB.h"

#include "physicsManager.h"

/*
    An entity that may collide with other collidableEntities
*/
class ColidableEntity : public GameEntity
{
public:
    ColidableEntity(AABB* bbox);
    virtual ~ColidableEntity();
    
    //overrides gameEntity to allow boundingbox position updates
    virtual void move(glm::vec3 displacement);

    //scaling (allow for boundingbox size changes)
    virtual void scale(glm::vec3 factor);
    

    //checks if current instance collided with colidableEntity e
    bool collides(ColidableEntity& e);

    //boundingbox getter and setter
    AABB getBoundingBox();
    void setBoundingBox(AABB bbox);

protected:
    AABB* boundingBox;

};

#endif