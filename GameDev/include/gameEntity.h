#ifndef _GAME_ENTITY_H
#define _GAME_ENTITY_H

#include <glm\glm.hpp>
#include <list>
#include <vector>
#include <iostream>

#include "AABB.h"

/*
    Base entity class for game elements
*/

enum EntityType
{
    PLAYER = 0,
    ENEMY,
    WALL,
};

class GameEntity
{
protected:
    glm::vec3 last_position;
    glm::vec3 position;
    glm::vec3 velocity;
    glm::vec3 acceleration;
    EntityType type;

    //list with every entity in the game
    
public:
    //every gameEntity
    static std::list<GameEntity*> entities;

    GameEntity();
    virtual ~GameEntity();

    //moves the entity. Might be overridden for special movement requirements
    virtual void move(glm::vec3 displacement);

    //may be overridden in game code
    virtual void die();

    glm::vec3& getPosition();
    void setPosition(const glm::vec3& vec);

    glm::vec3& getLastPosition();
    void setLastPosition(const glm::vec3& vec);

    glm::vec3& getVelocity();
    void setVelocity(const glm::vec3& vec);
    void setVelocityX(float v);
    void setVelocityY(float v);
    void setVelocityZ(float v);

    EntityType getType();


    glm::vec3& getAcceleration();
    void setAcceleration(const glm::vec3& vec);


    //update last_position value of every entity
    static void updateEntities();
    static void shutdownEntities();

    static unsigned getNumEntities();
    //static std::vector<GameEntity*> getAllEntities();
};

#endif