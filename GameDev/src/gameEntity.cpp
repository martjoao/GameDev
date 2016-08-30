#include "gameEntity.h"

std::list<GameEntity*> GameEntity::entities;

GameEntity::GameEntity()
{   
    position = glm::vec3(0.f, 0.f, 0.f);
    velocity = glm::vec3(0.f, 0.f, 0.f);
    acceleration = glm::vec3(0.f, 0.0f, 0.0f);

    last_position = position;

    entities.push_back(this);
}

GameEntity::~GameEntity()
{
    entities.remove(this);
}

void GameEntity::move(glm::vec3 displacement)
{
    position = position + displacement;
}


glm::vec3& GameEntity::getPosition()
{
    return position;

}
void GameEntity::setPosition(const glm::vec3& vec)
{
    position = vec;
}

glm::vec3& GameEntity::getLastPosition()
{
    return last_position;

}
void GameEntity::setLastPosition(const glm::vec3& vec)
{
    last_position = vec;
}

glm::vec3& GameEntity::getVelocity()
{
    return velocity;

}
void GameEntity::setVelocity(const glm::vec3& vec)
{
    velocity = vec;
}

void GameEntity::setVelocityX(float v)
{
    velocity.x = v;
}

void GameEntity::setVelocityY(float v)
{
    velocity.y = v;
}

void GameEntity::setVelocityZ(float v)
{
    velocity.z = v;
}

glm::vec3& GameEntity::getAcceleration()
{
    return acceleration;

}
void GameEntity::setAcceleration(const glm::vec3& vec)
{
    acceleration = vec;
}


void GameEntity::updateEntities()
{
    for (std::list<GameEntity*>::const_iterator i = GameEntity::entities.begin(); i != GameEntity::entities.end(); i++)
    {
        (*i)->last_position = (*i)->position;
    }
}

unsigned GameEntity::getNumEntities()
{
    return entities.size();
}



void GameEntity::shutdownEntities()
{
    for (std::list<GameEntity*>::const_iterator i = entities.begin(); i != entities.end(); ) {
        GameEntity* a = (*i);
        i = entities.erase(i);
        delete a;
    }
}

EntityType GameEntity::getType()
{
    return type;
}

void GameEntity::die()
{

}