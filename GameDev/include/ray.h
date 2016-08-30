#ifndef _RAY_H_
#define _RAY_H_

#include "AABB.h"
#include <iostream>
#include <limits>
#include <glm\glm.hpp>

/*
    Ray class
    Provides some raycasting features
    Collision with bounding box provided
*/

class Ray
{

public:
    Ray(glm::vec3 o, glm::vec3 d);
    ~Ray();

    bool intersect(AABB bb, float min, float max);

protected:
    glm::vec3 origin;
    glm::vec3 direction;

};

#endif