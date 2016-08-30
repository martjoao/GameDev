#include <iostream>
#include "SDL.h"
#include "game.h"
#include "gameCharacter.h"
#include "block.h"
#include "enemy.h"
#include "hudEntity.h"

#include <SDL_mixer.h>
#include <time.h>




void moveUp()
{
    if (GameCharacter::mainChar)
    {
        GameCharacter::mainChar->setVelocityY(8.0f);
    }
}
void moveDown()
{
    if (GameCharacter::mainChar)
    {
        GameCharacter::mainChar->setVelocityY(-8.0f);
    }
}
void moveLeft()
{       
    if (GameCharacter::mainChar)
    {
        GameCharacter::mainChar->setVelocityX(-8.0f);
    }
}
void moveRight()
{
    if (GameCharacter::mainChar)
    {
        //GameCharacter::mainChar->move(glm::vec3(0.5f, 0.0f, 0.0f));
        GameCharacter::mainChar->setVelocityX(8.0f);
    }
}

//set keyCallback
void keys(Engine &e)
{
    e.keyCallback(SDLK_w, moveUp);
    e.keyCallback(SDLK_s, moveDown);
    e.keyCallback(SDLK_d, moveRight);
    e.keyCallback(SDLK_a, moveLeft);
}

//what happens when A collides with B
//dir is direction of collision
void collision(ColidableEntity* a, ColidableEntity* b, glm::vec3 dir)
{
    if (a->getType() == PLAYER && b->getType() == WALL)
    {
        a->setVelocity(glm::vec3());
    }
    else if ((a->getType() == PLAYER && b->getType() == ENEMY) || (a->getType() == ENEMY && b->getType() == PLAYER))
    {
        a->die();
        b->die();
    }
    else if (a->getType() == ENEMY && b->getType() == WALL )
    {
        glm::vec3 vel = ((Enemy*)a)->getMovement();
        if (dir.x) vel.x *= -dir.x;
        if (dir.y) vel.y *= -dir.y;
        if (dir.z) vel.z *= -dir.z;
        a->setVelocity(vel);

        ((Enemy*)a)->setMovement(vel);
    }
    else if (a->getType() == ENEMY && b->getType() == ENEMY)
    {
        glm::vec3 velA = ((Enemy*)a)->getMovement();
        glm::vec3 velB = ((Enemy*)b)->getMovement();

        if (dir.x) 
        {
            velA.x = -velA.x;
            velB.x = -velB.x;
        }
        if (dir.y)
        {
            velA.y = -velA.y;
            velB.y = -velB.y;
        }
        if (dir.z)
        {
            velA.z = -velA.z;
            velB.z = -velB.z;
        }
        a->setVelocity(velA);
        b->setVelocity(velB);

        ((Enemy*)a)->setMovement(velA);
        ((Enemy*)b)->setMovement(velB);
    }
}

//mouse events
void mouse(const SDL_Event& e)
{
    if (Game::mainGame->getState() == GAME)
    {
        float x = (2.0f * e.button.x) / 1200 - 1.0f;
        float y = 1.0f - (2.0f * e.button.y) / 670;

        glm::mat4 v = RenderManager::getViewMatrix();
        glm::mat4 p = RenderManager::getProjMatrix();

        //get homogeneous coordinate in oder to reverse pipeline
        glm::vec4 i2 = glm::vec4(0, 0, 0, 1);
        i2 = v * i2;
        i2 = p * i2;
        float w = i2.a;

        glm::vec4 i = glm::vec4(x*w, y*w, 0, 1);
        i = glm::inverse(p) * i;
        i = glm::inverse(v) * i;
        //std::cout << i.x << " " << i.y << " " << i.z << " " << i.a << "\n";


        if (GameCharacter::mainChar)
        {
            GameCharacter::mainChar->shoot(glm::vec3(i.x, i.y, 0));
        }
    }
    else if (Game::mainGame->getState() == MENU)
    {
        //std::cout << e.button.x << " " << e.button.y << "\n";
        if (e.button.x > 324 && e.button.x < 866)
        {
            if (e.button.y > 268 && e.button.y < 340)
            {
                Game::mainGame->initGame();
            }     
            else if (e.button.y > 360 && e.button.y < 431)
            {
                Game::mainGame->initCredits();
            }
            else if (e.button.y > 452 && e.button.y < 525)
            {
                Game::mainGame->quit();
            }
        }
    }
    else if (Game::mainGame->getState() == GAMEOVER)
    {
        if (e.button.y > 344 && e.button.y < 533)
        {
            if (e.button.x > 321 && e.button.x < 484)
            {
                Game::mainGame->initGame();
            }
            else if (e.button.x > 517 && e.button.x < 679)
            {
                Game::mainGame->initMenu();
            }
            else if (e.button.x > 709 && e.button.x < 871)
            {
                Game::mainGame->quit();
            }
        }
    }
    else if (Game::mainGame->getState() == CREDITS)
    {
        //std::cout << e.button.x << " " << e.button.y << "\n";
        if (e.button.x > 324 && e.button.x < 866 && e.button.y > 428 && e.button.y < 501)
        {
            Game::mainGame->initMenu();
        }
    }
    
}

int main(int argc, char* args[])
{
    Game e(1200, 670);
    Game::mainGame = &e;

    srand(time(NULL));

    //set callbacks
    e.setProj(glm::perspective(60.f, 12.f/6.7f, 1.f, 100.f));
    e.setView(glm::translate(glm::mat4(),glm::vec3(0.f, 0.f, -40.f )));
    keys(e);
    e.mouseCallback(mouse);
    e.collisionCallback(collision);

    e.run();
    
    return 0;
}

