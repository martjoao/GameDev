#include "physicsManager.h"

std::list<ColidableEntity *> PhysicsManager::objects;
std::list<ColidableEntity *> PhysicsManager::moved;
std::list<ColidableEntity *> PhysicsManager::tmp_moved;

PhysicsManager::PhysicsManager()
{

}

PhysicsManager::~PhysicsManager()
{

}

void PhysicsManager::addEntity(ColidableEntity& o)
{
    objects.push_back(&o);
}

void PhysicsManager::removeEntity(ColidableEntity* o)
{
    objects.remove(o);
}
void PhysicsManager::addMovedEntity(ColidableEntity& o)
{
    if (std::find(std::begin(tmp_moved), std::end(tmp_moved), &o) == std::end(tmp_moved))
    {
        tmp_moved.push_back(&o);
    }
}
void PhysicsManager::removeMovedEntity(ColidableEntity* o)
{
    moved.remove(o);    
    tmp_moved.remove(o);
}


bool PhysicsManager::init()
{
    return true;
}

void PhysicsManager::update(float step)
{    
    // TODO: Update velocity/position values (EULER OR VERLET INTEGRATION)
    //drag constant
    float drag = 0.90f;
    //move every entity
    for (std::list<GameEntity*>::const_iterator i = GameEntity::entities.begin(); i != GameEntity::entities.end(); i++) 
    {
        GameEntity * e = (*i);       

        glm::vec3 s = e->getPosition();
        glm::vec3 v = e->getVelocity();
        glm::vec3 a = e->getAcceleration();

        //INTEGRATION:
        v += a*step;
        e->move(v*step);
        e->setVelocity(v*drag);
    }
    
    //check collisions (fixing overlaps)
    for (std::list<ColidableEntity*>::const_iterator i = moved.begin(); i != moved.end(); i++)
    {

        std::vector<ColidableEntity*> c;
        c = checkCollisions(*i);
        if (c.size() > 0)
        {
            //std::cout << "collision detected\n";
        }

    }
    moved.clear();
    moved = tmp_moved;
    tmp_moved.clear();
}

std::vector<ColidableEntity *> PhysicsManager::checkCollisions(ColidableEntity * e)
{
    std::vector<ColidableEntity*> collided;


    for (std::list<ColidableEntity*>::const_iterator i = objects.begin(); i != objects.end(); ++i)
    {
        if (e == (*i) || !e)
        {
            continue;
        }
        if (e->collides(*((*i))))
        {
            fixOverlapping(e, (*i));
            collided.push_back((*i));
        }
    }

    return collided;
}

void PhysicsManager::shutdown()
{

}

void PhysicsManager::fixOverlapping(ColidableEntity* a, ColidableEntity* b)
{

    //fix overlapping
    AABB aBB = a->getBoundingBox();
    AABB bBB = b->getBoundingBox();

    glm::vec3 d = aBB.getPosition() - bBB.getPosition();
    d.x = d.x >= 0 ? 1.f : -1.f;
    d.y = d.y >= 0 ? 1.f : -1.f;
    d.z = d.z >= 0 ? 1.f : -1.f;

    glm::vec3 overlap = glm::vec3();
    overlap.x = aBB.getOffset().x + bBB.getOffset().x - abs(aBB.getPosition().x - bBB.getPosition().x);
    overlap.y = aBB.getOffset().y + bBB.getOffset().y - abs(aBB.getPosition().y - bBB.getPosition().y);
    overlap.z = aBB.getOffset().z + bBB.getOffset().z - abs(aBB.getPosition().z - bBB.getPosition().z);

    overlap.x *= d.x;
    overlap.y *= d.y;
    overlap.z *= d.z;

    glm::vec3 movedir = overlap;

    glm::vec3 dir;

    dir = abs(overlap.x) <= abs(overlap.y) ? glm::vec3(1.0, 0, 0) : glm::vec3(0, 1.0, 0);

    glm::vec3 m = glm::dot(movedir, dir) * dir;

    a->move(m);
    PhysicsManager::collisionResponse(a, b, dir);
}

void PhysicsManager::setCollisionCallback(void(*c) (ColidableEntity* a, ColidableEntity* b, glm::vec3 dir))
{
    collisionResponse = c;
}