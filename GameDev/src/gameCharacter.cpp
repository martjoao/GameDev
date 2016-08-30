#include "gameCharacter.h"


GameCharacter* GameCharacter::mainChar = NULL;

GameCharacter::GameCharacter(RenderObject& o) : RenderableEntity(o)
{
    type = PLAYER;
    lastShot = 0;
    lives = 0;
    died = false;
    shot = NULL;

    for (int i = 0; i < 5; i++)
    {
        oneUp();
    }

}

GameCharacter::~GameCharacter()
{
    if (shot)
    {
        delete shot;
        shot = NULL;
    }
}

void GameCharacter::move(glm::vec3 displacement)
{
    RenderableEntity::move(displacement);
    //RenderManager::setViewMatrix(glm::translate(RenderManager::getViewMatrix(), glm::vec3(-displacement.x, -displacement.y, -0.0f)));
}

void GameCharacter::shoot(glm::vec3 dir)
{
    //Draw shooting line
    if (shot)
    {
        delete shot;
        shot = NULL;
        lastShot = 0;
    }
    glm::vec3 d = glm::normalize(dir - position);
    float cos = glm::dot(d, glm::vec3(1,0,0));
    float angle = glm::degrees(std::acos(cos));

    shot = new HUDEntity("texWhite.bmp");
    if (position.y > dir.y)
    {
        angle = -angle;
    }
    Mix_PlayChannel(-1, ResourceManager::loadAudioChunk("lightsaber.wav"), 0);


    shot->scale(glm::vec3(7, 0.1, 0));
    shot->move(glm::vec3(7.f, 0.f, 0.f));
    shot->rotate(angle, glm::vec3(0, 0, 1));
    shot->move(position);
    lastShot = SDL_GetTicks();

    //enemies hit
    Ray r(position, d);

    list<Enemy*>enemies = Enemy::getEnemyList();
    for (list<Enemy*>::const_iterator i = enemies.begin(); i != enemies.end(); i++)
    {
        if (r.intersect((*i)->getBoundingBox(), 0, 14))
        {
            (*i)->die();
            Mix_PlayChannel(-1, ResourceManager::loadAudioChunk("cough.wav"), 0);
        }
    }

}

void GameCharacter::die()
{
    
    oneDown();
    if (lives == 0)
    {
        died = true;
    }
    
}

bool GameCharacter::isDead()
{
    return died;
}

void GameCharacter::draw()
{

    RenderableEntity::draw();
    if ((SDL_GetTicks() - lastShot) > 100)
    {
        delete shot;
        shot = NULL;
        lastShot = 0;
    }
}

void GameCharacter::oneUp()
{
    int i = hudLives.size();
    lives++;

    HUDEntity* h = new HUDEntity("texIcos.bmp");
    h->scale(glm::vec3(1.5, 1.5, 1));
    h->move(glm::vec3(-36 + ((i%3) * 3), 15 + ((i/3) * -3), 2));
    hudLives.push(h);

}

void GameCharacter::oneDown()
{
    lives--;

    HUDEntity* h = hudLives.top();
    hudLives.pop();
    delete h;

}
