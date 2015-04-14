#pragma once

#include <deque>
#include <map>
#include "Player.h"
#include "MyPoint.hpp"
#include "cocos2d.h"

class GameScene;

class GameLogic
{
public:
    GameLogic(cocos2d::CCSize const & gameSize);
    ~GameLogic();
    
    void setOnDeadCallback(GameScene* gs);
    
    Player* addPlayer();
    void movePlayerLeft(float dt, int id = -1);
    void movePlayerRight(float dt, int id = -1);
    void update(float dt);
    std::deque<Player*> getPlayers();
    bool hasGameEnd();
    void nextGame();
    void reset();
    Player* getWinner();
    Player* finalWinner();

    static uint16_t AngleTurn;
    static uint16_t SizePoint;
    static uint16_t Speed;


private:
    
    cocos2d::CCSize _gameSize;
    int _idPlayer;
    std::deque<Player*> _players;
    int _nbPlayerAlive;
    Player* _winner;

    GameScene* _gs;
    
    void incScore();
    
    static const uint16_t GridX = 20;
    static const uint16_t GridY = 10;

    std::map<int, bool> _grid;
    std::deque<MyPoint> _points;
};
