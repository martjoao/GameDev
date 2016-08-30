#include "renderManager.h"

list<RenderableEntity*> RenderManager::objects;
glm::mat4 RenderManager::viewMatrix;
glm::mat4 RenderManager::projMatrix;

RenderManager::RenderManager()
{

}

RenderManager::~RenderManager()
{

}

void RenderManager::addEntity(RenderableEntity& o)
{
    objects.push_back(&o);
}

void RenderManager::removeEntity(RenderableEntity* o)
{
    objects.remove(o);
}


void RenderManager::renderScene()
{
    for (list<RenderableEntity*>::const_iterator i = objects.begin(); i != objects.end(); ++i) {
     
        GLuint program = (*i)->getRenderObject()->GetShader()->GetShaderProgram();
        //GLuint program = (*i)->GetShader()->GetShaderProgram();
        glUseProgram(program);

        glm::mat3 normalMatrix = glm::inverse(glm::transpose(glm::mat3((viewMatrix * (*i)->getRenderObject()->GetModelMatrix()))));
        //glm::mat3 normalMatrix = glm::mat3();
        glUniformMatrix4fv(glGetUniformLocation(program, "modelMatrix"), 1, false, (float*)&((*i)->getRenderObject()->GetModelMatrix()));
        //glUniformMatrix4fv(glGetUniformLocation(program, "modelMatrix"), 1, false, (float*)&((*i)->GetModelMatrix()));
        glUniformMatrix4fv(glGetUniformLocation(program, "viewMatrix"), 1, false, (float*)&(viewMatrix));
        glUniformMatrix4fv(glGetUniformLocation(program, "projMatrix"), 1, false, (float*)&(projMatrix));
        glUniformMatrix3fv(glGetUniformLocation(program, "normalMatrix"), 1, false, (float*)&(normalMatrix));

        //texs
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, (*i)->getRenderObject()->GetTexture());
        glUniform1i(glGetUniformLocation(program, "textureSampler"), 0);

        (*i)->draw();
    }
}

void RenderManager::setViewMatrix(glm::mat4 vm)
{
    viewMatrix = vm;
}

glm::mat4 RenderManager::getViewMatrix()
{
    return viewMatrix;
}

void RenderManager::setProjMatrix(glm::mat4 pm)
{
    projMatrix = pm;
}

glm::mat4 RenderManager::getProjMatrix()
{
    return projMatrix;
}



bool RenderManager::init()
{
    viewMatrix = glm::mat4();
    projMatrix = glm::mat4();

    glewExperimental = GL_TRUE;
    glewInit();

    glEnable(GL_DEPTH_TEST);
    glClearColor(0, 0, 0, 1);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    return true;
}

void RenderManager::update()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //updateCamera()
    //updateSceneElements()
    renderScene();

}

void RenderManager::shutdown()
{

}