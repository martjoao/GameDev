#include "hudManager.h"

list<HUDEntity*> HUDManager::hudObjects;

HUDManager::HUDManager()
{

}

HUDManager::~HUDManager()
{

}

void HUDManager::addEntity(HUDEntity &o)
{
    hudObjects.push_back(&o);
}
void HUDManager::removeEntity(HUDEntity *o)
{
    hudObjects.remove(o);
}

void HUDManager::renderHUD()
{
    for (list<HUDEntity*>::const_iterator i = hudObjects.begin(); i != hudObjects.end(); ++i) {
        GLuint program = (*i)->getRenderObject()->GetShader()->GetShaderProgram();
        //GLuint program = (*i)->GetShader()->GetShaderProgram();
        glUseProgram(program);

        //glm::mat3 normalMatrix = glm::mat3();
        glUniformMatrix4fv(glGetUniformLocation(program, "modelMatrix"), 1, false, (float*)&((*i)->getRenderObject()->GetModelMatrix()));
        //glUniformMatrix4fv(glGetUniformLocation(program, "modelMatrix"), 1, false, (float*)&((*i)->GetModelMatrix()));
        glUniformMatrix4fv(glGetUniformLocation(program, "viewMatrix"), 1, false, (float*)&(RenderManager::getViewMatrix()));
        glUniformMatrix4fv(glGetUniformLocation(program, "projMatrix"), 1, false, (float*)&(RenderManager::getProjMatrix()));

        //texs
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, (*i)->getRenderObject()->GetTexture());
        glUniform1i(glGetUniformLocation(program, "textureSampler"), 0);

        (*i)->draw();
    }
}




bool HUDManager::init()
{
    return true;
}

void HUDManager::update()
{

    renderHUD();

}

void HUDManager::shutdown()
{
    shutdownEntities();
}

void HUDManager::shutdownEntities()
{
    for (std::list<HUDEntity*>::const_iterator i = hudObjects.begin(); i != hudObjects.end(); ) {
        HUDEntity* a = (*i);
        i = hudObjects.erase(i);
        delete a;
    }
}

