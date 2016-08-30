#include "colidableEntity.h"

ColidableEntity::ColidableEntity(AABB* bbox) : GameEntity()
{
    boundingBox = bbox;
    PhysicsManager::addEntity(*this);
}

ColidableEntity::~ColidableEntity()
{    
    PhysicsManager::removeEntity(this);
    PhysicsManager::removeMovedEntity(this);

    delete boundingBox;
    boundingBox = NULL;
}


void ColidableEntity::move(glm::vec3 displacement)
{
    GameEntity::move(displacement);
    boundingBox->setPosition(boundingBox->getPosition() + displacement);

    PhysicsManager::addMovedEntity(*this);
}

void ColidableEntity::scale(glm::vec3 factor)
{
    glm::vec3 off = boundingBox->getOffset();
    
    //std::cout << off.x << " " << off.y << " " << off.z << "\n";
    
    off.x *= factor.x;
    off.y *= factor.y;
    off.z *= factor.z;

    //std::cout << off.x << " " << off.y << " " << off.z << "\n";

    boundingBox->setOffset(off);
}


bool ColidableEntity::collides(ColidableEntity& e)
{
    //checks for AABB collision
    AABB bb = e.getBoundingBox();
    glm::vec3 off = bb.getOffset();
     
    if (abs(boundingBox->getPosition().x - bb.getPosition().x) >= (boundingBox->getOffset().x + bb.getOffset().x - 0.0001))
        return false;
    if (abs(boundingBox->getPosition().y - bb.getPosition().y) >= (boundingBox->getOffset().y + bb.getOffset().y - 0.0001))
        return false;
    if (abs(boundingBox->getPosition().z - bb.getPosition().z) >= (boundingBox->getOffset().z + bb.getOffset().z - 0.0001))
        return false;

    


    return true;
}

AABB ColidableEntity::getBoundingBox()
{
    return *boundingBox;
}

void ColidableEntity::setBoundingBox(AABB bbox)
{
    boundingBox = &bbox;
}
