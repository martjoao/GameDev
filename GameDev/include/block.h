#ifndef _BLOCK_H
#define _BLOCK_H

#include "renderableEntity.h"

/*
    Blocks are scaled cubes
    Not movable
*/

class Block : public RenderableEntity
{
public:
    Block(RenderObject& o);

    virtual void move(glm::vec3 displacement);
};

#endif