#include "ray.h"

Ray::Ray(glm::vec3 o, glm::vec3 d)
{
    origin = o;
    direction = glm::normalize(d);
}

Ray::~Ray()
{

}

void swap(float& x, float&y)
{
    float z = y;
    y = x;
    x = z;
}

//based on http://www.scratchapixel.com/lessons/3d-basic-lessons/lesson-7-intersecting-simple-shapes/ray-box-intersection/
bool Ray::intersect(AABB bb, float minimum, float maximum)
{
    glm::vec3 bPos = bb.getPosition();
    glm::vec3 bOff = bb.getOffset();

    //corners of bounding box
    glm::vec3 min = bPos - bOff;
    glm::vec3 max = bPos + bOff;

    // ray intersection with axis aligned planes
    float t0x = std::numeric_limits<float>::max();
    float t0y = std::numeric_limits<float>::max();
    float t0z = std::numeric_limits<float>::max();

    float t1x = std::numeric_limits<float>::min();
    float t1y = std::numeric_limits<float>::min();
    float t1z = std::numeric_limits<float>::min();

    if (direction.x)
    {
        t0x = (min.x - origin.x) / direction.x;
        t1x = (max.x - origin.x) / direction.x;
        if (t0x > t1x) swap(t0x, t1x);

    }
    if (direction.y)
    {
        t0y = (min.y - origin.y) / direction.y;
        t1y = (max.y - origin.y) / direction.y;
        if (t0y > t1y) swap(t0y, t1y);

    }


    //make t0 the lowest one

    //if there is an intersection, the highest value in each axis will be an intersection
    
    if ((t0x > t1y) || (t0y > t1x))
        return false;

    float tmin = (t0x < t0y) ? t0y : t0x;
    float tmax = (t1x > t1y) ? t1y : t1x;


    if (direction.z)
    {
        t0z = (min.z - origin.z) / direction.z;
        t1z = (max.z - origin.z) / direction.z;
        if (t0z > t1z) swap(t0z, t1z);
        if ((tmin > t1z) || (t0z > tmax))
            return false;

    }
    
    if (tmin > t0z) tmin = t0z;
    if (tmax < t1z) tmax = t1z;


    
    if (tmin < minimum || tmax > maximum)
        return false;


    return true;

}
