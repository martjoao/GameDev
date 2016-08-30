#include "aiEntity.h"

AIEntity::AIEntity()
{
    AIManager::addEntity(*this);
}

AIEntity::~AIEntity()
{
    AIManager::removeEntity(this);
}