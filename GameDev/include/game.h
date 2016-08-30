#ifndef _GAME_H_
#define _GAME_H_


#include "engine.h"
#include "gameCharacter.h"
#include "enemy.h"
#include "block.h"
#include <sstream>

enum GameState
{
    MENU = 0,
    GAME,
    CREDITS,
    GAMEOVER
};

/*
    Game itself, inherits from Engine and adds game specific stuff
*/

class Game : public Engine
{
protected:
    //game specific variables

    //last enemy spawned
    Uint32 lastSpawn;
    
    int score;
    int level;
    GameState state;
    HUDEntity * hudScore;


public:
    Game(int, int);
    ~Game();

    int getScore();
    int getLevel();

    void setScore(int s);
    void setLevel(int l);
    GameState getState();
    void quit();

    //initial objects on scene
    virtual void createObjects();
    virtual void customPeriodic();

    //setup and start each game state
    void initMenu();
    void initGame();
    void initGameOver();
    void initCredits();


    static Game* mainGame;
};

#endif