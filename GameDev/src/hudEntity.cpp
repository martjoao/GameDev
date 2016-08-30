#include "hudEntity.h"

HUDEntity::HUDEntity(string tex, HUDtype t) //: GameEntity()
{
    hudtype = t;
    if (t == TEXTURE)
    {
        obj = ResourceManager::createRenderObject("plane.obj", tex, "hudV.glsl", "hudF.glsl");
        obj->SetModelMatrix(glm::rotate(obj->GetModelMatrix(), 90.f, glm::vec3(1.0f, 0.0f, 0.f)));
    }
    else if (t == TEXT)
    {
        obj = ResourceManager::createRenderObject("plane.obj", "texBlue.bmp", "hudV.glsl", "hudF.glsl");
        obj->SetTexture(ResourceManager::loadTTFTex(tex));
        obj->SetModelMatrix(glm::rotate(obj->GetModelMatrix(), 90.f, glm::vec3(1.0f, 0.0f, 0.f)));
    }
    HUDManager::addEntity(*this);

}

HUDEntity::~HUDEntity()
{
    HUDManager::removeEntity(this);
    delete obj;
    obj = NULL;
}



void HUDEntity::move(glm::vec3 displacement)
{
    //GameEntity::move(displacement);
    glm::mat4 model = obj->GetModelMatrix();
    obj->SetModelMatrix(glm::translate(glm::mat4(), displacement) * model);
}

void HUDEntity::scale(glm::vec3 factor)
{
    obj->SetModelMatrix(glm::scale(glm::mat4(), factor) * obj->GetModelMatrix());
}

void HUDEntity::rotate(float degrees, glm::vec3 around)
{
    obj->SetModelMatrix(glm::rotate(glm::mat4(),degrees, around) * obj->GetModelMatrix());
}


RenderObject* HUDEntity::getRenderObject()
{
    return obj;
}

void HUDEntity::setRenderObject(RenderObject &o)
{
    obj = &o;
}

void HUDEntity::draw()
{
    obj->Draw();
}