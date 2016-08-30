#ifndef _AI_MANAGER_H
#define _AI_MANAGER_H

#include <list>
#include "aiEntity.h"


/*
    Handles AI entities
*/
class AIEntity;

class AIManager
{
public:
    AIManager();
    ~AIManager();

    bool init();
    //calls ACT method of every AIEntity
    void update();
    void shutdown();

    static void addEntity(AIEntity & o);
    static void removeEntity(AIEntity * o);


protected:
    static std::list< AIEntity*> entities;

};

#endif