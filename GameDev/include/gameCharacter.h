#ifndef _GAME_CHARACTER_H
#define _GAME_CHARACTER_H

#include "renderableEntity.h"
#include "hudEntity.h"
#include "ray.h"
#include "enemy.h"
#include "game.h"
#include "resourceManager.h"
#include <stack>


/*
    Main game character, the player
*/
class GameCharacter : public RenderableEntity
{
protected:
    //shot drawing
    HUDEntity * shot;

    //last time shot
    Uint32 lastShot;
    
    bool died;
    int lives;

    stack<HUDEntity*> hudLives;

public:
    virtual void move(glm::vec3 displacement);
    void shoot(glm::vec3 dir);
    void die();
    bool isDead();
    void oneUp();
    void oneDown();

    virtual void draw();

    static GameCharacter * mainChar;
    GameCharacter(RenderObject& o);
    ~GameCharacter();

};

#endif