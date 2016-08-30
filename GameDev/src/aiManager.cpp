#include "aiManager.h"

std::list<AIEntity *> AIManager::entities;

AIManager::AIManager()
{

}

AIManager::~AIManager()
{

}


bool AIManager::init()
{
    return true;
}

void AIManager::update()
{
    for (std::list<AIEntity*>::const_iterator i = entities.begin(); i != entities.end(); i++)
    {
        (*i)->act();
    }
}

void AIManager::shutdown()
{

}

void AIManager::addEntity(AIEntity & o)
{
    entities.push_back(&o);
}

void AIManager::removeEntity(AIEntity * o)
{
    entities.remove(o);
}