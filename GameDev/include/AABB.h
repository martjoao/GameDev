#ifndef _AABB_H
#define _AABB_H

#include <glm\vec3.hpp>
#include <glm\vec4.hpp>
#include <glm\mat4x4.hpp>

/*
    Axis Aligned Bounding Box class
*/
class AABB
{
protected:
    //center of boundingBox
    glm::vec3 position;
    glm::vec3 offset;

public:

    AABB(glm::vec3 pos, glm::vec3 off);
    AABB();

    glm::vec3 getPosition();
    glm::vec3 getOffset();

    void setPosition(glm::vec3);
    void setOffset(glm::vec3);

};

#endif