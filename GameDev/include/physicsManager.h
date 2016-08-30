#ifndef _PHYSICS_MANAGER_H
#define _PHYSICS_MANAGER_H

#include <list>
#include <iostream>
#include <SDL.h>
#include "colidableEntity.h"
#include <algorithm>

class ColidableEntity;
/*
    Handles colision and movement
*/
class PhysicsManager
{
public:
    PhysicsManager();
    ~PhysicsManager();

    //adds an entity to a list of ColidableEntities
    static void addEntity(ColidableEntity & o);
    static void removeEntity(ColidableEntity * o);

    static void addMovedEntity(ColidableEntity & o);
    static void removeMovedEntity(ColidableEntity * o);



    std::vector<ColidableEntity *> checkCollisions(ColidableEntity * e);

    bool init();
    //checks for object collision
    void update(float step);
    void shutdown();

    void setCollisionCallback(void(*collisionResponse) (ColidableEntity* a, ColidableEntity* b, glm::vec3 dir));

protected:
    //list that should contain every collidableObject
    static std::list<ColidableEntity *> objects;
    //list of every object that moved from last update until now
    static std::list<ColidableEntity *> moved;
    static std::list<ColidableEntity *> tmp_moved;


    //fixes a overlapping that might have occurred between entities a and b
    //call it once a collision is detected 
    void fixOverlapping(ColidableEntity* a, ColidableEntity* b);
    void(*collisionResponse) (ColidableEntity* a, ColidableEntity* b, glm::vec3 dir);
};

#endif