#include "engine.h"

#include "gameCharacter.h"


Engine::Engine(int w, int h)
{
    sWidth = w;
    sHeight = h;
}

Engine::~Engine()
{
}

void Engine::keyCallback(SDL_Keycode c, void(*k) ()) 
{
    inputMan->setKeyCallback(c, k);
}

void Engine::collisionCallback(void(*c) (ColidableEntity* a, ColidableEntity* b, glm::vec3 dir))
{
    physicsMan->setCollisionCallback(c);
}
void Engine::mouseCallback(void(*m) (const SDL_Event& e))
{
    inputMan->setMouseCallback(m);
}
void Engine::setView(glm::mat4 v)
{
    RenderManager::setViewMatrix(v);
}
void Engine::setProj(glm::mat4 p)
{
    RenderManager::setProjMatrix(p);
}


void Engine::createObjects() 
{
}

void Engine::customPeriodic()
{
}


bool Engine::startup()
{
    windowMan   = new WindowManager(sWidth, sHeight);
    resourceMan = new ResourceManager();
    inputMan    = new InputManager();
    renderMan   = new RenderManager();
    physicsMan  = new PhysicsManager();
    aiMan       = new AIManager();
    hudMan      = new HUDManager();

    windowMan->init();
    resourceMan->init();
    inputMan->init();
    renderMan->init();
    physicsMan->init();
    aiMan->init();
    hudMan->init();

    createObjects();

    return true;
}

void Engine::run()
{
    //Physics loop with fixed timestep and rendering loop with variable timestep

    float timestep = 1000/60;
    float timestepSeconds = timestep / 1000;
    

    int frameCounter = 0;
    Uint32 fpsUpdateTime = SDL_GetTicks();

    Uint32 previousTime = SDL_GetTicks();
    double t = 0;
    while (true)
    {
        Uint32 currentTime = SDL_GetTicks();
        Uint32 elapsed = currentTime - previousTime;
        previousTime = currentTime;

        t = t + elapsed;

        customPeriodic();
        if (!inputMan->update())
        {
            break;
        }

        while (t >= timestep)
        {
            //physics updates should go here once force based movement is implemented                 
            t -= timestep;
            //find better location for next line
            aiMan->update();
            physicsMan->update(timestepSeconds);
            GameEntity::updateEntities();
            frameCounter++;

        }
        
        renderMan->update();
        hudMan->update();
        SDL_GL_SwapWindow(WindowManager::getWindow());
        
        //std::cout <<"\n" <<  (currentTime - previousTime) << "--\n";
        
        Uint32 t = SDL_GetTicks() - fpsUpdateTime;
        if (t > 1000)
        {
            fps = (frameCounter);
            frameCounter = 0;
            fpsUpdateTime = SDL_GetTicks();
            std::cout << "FPS: " << fps << "\n";           
        }
    }

}

bool Engine::shutdown()
{

    
    hudMan->shutdown();
    aiMan->shutdown();
    physicsMan->shutdown();
    GameEntity::shutdownEntities();
    renderMan->shutdown();
    inputMan->shutdown();
    resourceMan->shutdown();
    windowMan->shutdown();


    delete windowMan;
    delete resourceMan;
    delete inputMan;
    delete renderMan;
    delete physicsMan;
    delete aiMan;

    windowMan   = NULL;
    resourceMan = NULL;
    inputMan    = NULL;
    renderMan   = NULL;
    physicsMan  = NULL;
    aiMan       = NULL;

    return true;
}

