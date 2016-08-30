#include "enemy.h"

list<Enemy*> Enemy::enemies;


Enemy::Enemy(RenderObject& o, glm::vec3 initVel) : RenderableEntity(o), AIEntity()
{
    type = ENEMY;
    enemies.push_back(this);
    speed = 10;
    setMovement(initVel);
    died = false;
}

Enemy::~Enemy()
{
    enemies.remove(this);
}

void Enemy::act()
{
    //distance from main char
    if (GameCharacter::mainChar)
    {
        glm::vec3 d = GameCharacter::mainChar->getPosition() - position;
        if (glm::length(d) == 0) return;
        float dist = sqrt(glm::dot(d, d));

        if (dist < 14)
        {
            this->setMovement(8.f * glm::normalize(d));
            this->getRenderObject()->SetTexture(ResourceManager::loadBmpTex("texRed.bmp"));
        }
        else
        {
            this->getRenderObject()->SetTexture(ResourceManager::loadBmpTex("texBlue.bmp"));
        }
    }
    else
    {
        this->getRenderObject()->SetTexture(ResourceManager::loadBmpTex("texBlue.bmp"));
    }
    this->setVelocity(movement);
}

void Enemy::setMovement(glm::vec3 m)
{
    movement = glm::normalize(m) * speed;
}

glm::vec3 Enemy::getMovement()
{
    return movement;
}

list<Enemy*> Enemy::getEnemyList()
{
    return enemies;
}


float randFloat(double max)
{
    float i = (float)(rand() % 101);
    float f = i * 0.02f;
    return (float)(f - 1) * max;
}


void Enemy::spawnEnemy(std::string model, std::string tex)
{
    RenderObject * e1 = ResourceManager::createRenderObject(model, tex, "texV.glsl", "texF.glsl");
    e1->SetModelMatrix(glm::rotate(e1->GetModelMatrix(), 90.f, glm::vec3(0.0f, 1.f, 0.f)));
    Enemy* enemy = new Enemy(*e1, glm::vec3(randFloat(10), randFloat(10), 0));
    enemy->move(glm::vec3(randFloat(28) + 5, randFloat(18), 0.f));
}


void Enemy::die()
{
    died = true;
}

bool Enemy::isDead()
{
    return died;
}