#include "block.h"

Block::Block(RenderObject& o) : RenderableEntity(o)
{
    type = WALL;
}

void Block::move(glm::vec3 displacement)
{
    RenderableEntity::move(displacement);
    PhysicsManager::removeMovedEntity(this);
}