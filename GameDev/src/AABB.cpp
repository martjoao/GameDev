#include "AABB.h"

AABB::AABB(){}

AABB::AABB(glm::vec3 pos, glm::vec3 off)
{
    position = pos;
    offset = off;
}



glm::vec3 AABB::getPosition()
{
    return position;
}
glm::vec3 AABB::getOffset()
{
    return offset;
}
void AABB::setPosition(glm::vec3 pos)
{
    position = pos;
}
void AABB::setOffset(glm::vec3 off)
{
    offset = off;
}

//void AABB::draw()
//{
//    RenderObject * o = ResourceManager::createRenderObject("cube.obj", "texWhite.bmp", "texV.glsl", "texF.glsl");
//    o->SetModelMatrix(glm::translate(glm::scale(glm::mat4(), offset), position ));
//    o->Draw();
//    delete o;
//}