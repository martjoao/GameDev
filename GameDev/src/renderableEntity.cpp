#include "renderableEntity.h"

RenderableEntity::RenderableEntity(RenderObject & o) : ColidableEntity((o.GetMesh()->getAABB(o.GetModelMatrix())))
{
    obj = &o;
    RenderManager::addEntity(*this);
}

RenderableEntity::~RenderableEntity()
{
    delete obj;
    RenderManager::removeEntity(this);
}

void RenderableEntity::move(glm::vec3 displacement)
{
    ColidableEntity::move(displacement);
    glm::mat4 model = obj->GetModelMatrix();
    obj->SetModelMatrix(glm::translate(glm::mat4(), displacement) * model);
}

void RenderableEntity::scale(glm::vec3 factor)
{
    ColidableEntity::scale(factor);
    obj->SetModelMatrix(glm::scale(glm::mat4(), factor) * obj->GetModelMatrix() );
}


RenderObject* RenderableEntity::getRenderObject()
{
    return obj;
}

void RenderableEntity::setRenderObject(RenderObject &o)
{
    obj = &o;
}

void RenderableEntity::draw()
{
    obj->Draw();
    //boundingBox->draw();
}