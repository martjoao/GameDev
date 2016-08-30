#include "game.h"

Game* Game::mainGame;


Game::Game(int w, int h) : Engine(w,h)
{
    startup();
    lastSpawn = SDL_GetTicks();
}

Game::~Game()
{
    shutdown();
}


//called every update
void Game::customPeriodic()
{
    Uint32 time = SDL_GetTicks();
    
    if (state == GAME)
    {    
        if (GameCharacter::mainChar && GameCharacter::mainChar->isDead())
        {
            delete GameCharacter::mainChar;
            GameCharacter::mainChar = NULL;
            initGameOver();
        }

        if ((time - lastSpawn) > 500)
        {
            Enemy::spawnEnemy("odd.obj", "texBlue.bmp");
            lastSpawn = time;
        }

        list<Enemy*> enemies = Enemy::getEnemyList();
        for (list<Enemy*>::const_iterator i = enemies.begin(); i != enemies.end();)
        {
            if ((*i)->isDead())
            {
                Enemy* a = (*i);
                i = Enemy::getEnemyList().erase(i);
                delete a;
                setScore(score + 1);
                //i++;
            }
            else
            {
                i++;
            }
        }
    }
    else if (state == MENU)
    {

    }
    else if (state == GAMEOVER)
    {

    }
}

void Game::initMenu()
{
    GameEntity::shutdownEntities();
    HUDManager::shutdownEntities();
    Mix_HaltMusic();

    state = MENU;

    HUDEntity* e = new HUDEntity("texMenu.bmp");
    e->scale(glm::vec3(30, 20, 1));
}

void Game::initCredits()
{
    GameEntity::shutdownEntities();
    HUDManager::shutdownEntities();
    Mix_HaltMusic();

    state = CREDITS;

    HUDEntity* e = new HUDEntity("texCredits.bmp");
    e->scale(glm::vec3(30, 20, 1));
}

void Game::initGameOver()
{
    GameEntity::shutdownEntities();
    HUDManager::shutdownEntities();
    Mix_HaltMusic();

    std::stringstream ss;
    ss << score;


    hudScore = new HUDEntity(ss.str(), TEXT);
    hudScore->scale(glm::vec3(3, 3, 1));
    hudScore->move(glm::vec3(0, 6, 1.1));

    state = GAMEOVER;
    HUDEntity* e = new HUDEntity("texGameOver.bmp");
    e->scale(glm::vec3(30, 20, 1));

}

void Game::createObjects()
{
    initMenu();
}

void Game::initGame()
{
    Mix_HaltMusic();
    Mix_PlayMusic(ResourceManager::loadAudioMusic("GlobalElite.wav"), 1);


    lastSpawn = SDL_GetTicks();
    score = 0;
    level = 0;
    
    GameEntity::shutdownEntities();
    HUDManager::shutdownEntities();
    state = GAME;

    //Game HUD
    HUDEntity* h = new HUDEntity("texLives.bmp");
    h->scale(glm::vec3(4,4,1));
    h->move(glm::vec3(-34, 17, 1));

    HUDEntity* h1 = new HUDEntity("Score:", TEXT);
    h1->scale(glm::vec3(3.5, 2.5, 1));
    h1->move(glm::vec3(-34, -5, 1));
    
    hudScore = new HUDEntity("0", TEXT);
    hudScore->scale(glm::vec3(1.5, 1.5, 1));
    hudScore->move(glm::vec3(-33, -9, 2));

    
    //main character
    RenderObject * o1 = ResourceManager::createRenderObject("icos.obj", "texBlue.bmp", "texV.glsl", "texF.glsl");
    GameCharacter* g1 = new GameCharacter(*o1);
    g1->move(glm::vec3(-24.f, 0.f, 0.f));
    GameCharacter::mainChar = g1;
        
    //Down Wall
    RenderObject * o2 = ResourceManager::createRenderObject("cube.obj", "texRed.bmp", "texV.glsl", "texF.glsl");
    Block * g2 = new Block(*o2);
    g2->scale(glm::vec3(30.f, 1.f, 2.f));
    g2->move(glm::vec3(5.f, -20.f, 0.f));

    //Up Wall
    RenderObject * o3 = ResourceManager::createRenderObject("cube.obj", "texRed.bmp", "texV.glsl", "texF.glsl");
    Block * g3 = new Block(*o3);
    g3->scale(glm::vec3(30.f, 1.f, 2.f));
    g3->move(glm::vec3(5.f, 20.f, 0.f));

    //Right Wall
    RenderObject * o4 = ResourceManager::createRenderObject("cube.obj", "texRed.bmp", "texV.glsl", "texF.glsl");
    Block * g4 = new Block(*o4);
    g4->scale(glm::vec3(1.f, 21.f, 2.f));
    g4->move(glm::vec3(36.f, 0.f, 0.f));

    //Left Wall
    RenderObject * o5 = ResourceManager::createRenderObject("cube.obj", "texRed.bmp", "texV.glsl", "texF.glsl");
    Block * g5 = new Block(*o5);
    g5->scale(glm::vec3(1.f, 21.f, 2.f));
    g5->move(glm::vec3(-26.f, 0.f, 0.f));

}

int Game::getScore()
{
    return score;
}
int Game::getLevel()
{
    return level;
}

void Game::setScore(int s)
{
    score = s;
    if (hudScore)
    {
        std::stringstream ss;
        ss << score;
        hudScore->getRenderObject()->SetTexture(ResourceManager::loadTTFTex(ss.str()));
    }
    setLevel(score / 3);
}
void Game::setLevel(int l)
{
    level = l;
    //std::cout << "\n level: " << level << "\n";
}

GameState Game::getState()
{
    return state;
}

void Game::quit()
{
    SDL_Event* e = new SDL_Event();
    e->type = SDL_QUIT;
    SDL_PushEvent(e);
}