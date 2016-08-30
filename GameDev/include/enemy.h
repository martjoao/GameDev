#ifndef _ENEMY_H
#define _ENEMY_H

#include "renderableEntity.h"
#include "aiEntity.h"
#include "gameCharacter.h"
#include <list>

/*
    Enemy Class
*/

class Enemy : public RenderableEntity, AIEntity
{
protected:
    //movement direction
    glm::vec3 movement;
    static list<Enemy*> enemies;
    //speed
    float speed;
    bool died;

public:
    Enemy(RenderObject& o, glm::vec3 initVel);
    ~Enemy();

    //called by AIManager
    virtual void act();
    
    virtual void die();    
    bool isDead();


    void setMovement(glm::vec3);
    glm::vec3 getMovement();

    //creates a enemy with random position and movement direction
    static void spawnEnemy(string model, string tex);

    static list<Enemy*> getEnemyList();

};

#endif