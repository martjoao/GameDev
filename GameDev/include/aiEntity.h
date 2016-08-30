#ifndef _AI_ENTITY_H
#define _AI_ENTITY_H

#include "aiManager.h"

/*
    An entity that  has a processing step (act) to define any kind of behaviour
*/
class AIEntity
{
protected:

public:
    AIEntity();
    virtual ~AIEntity();

    //ai step, called every game loop
    virtual void act() = 0;
};

#endif