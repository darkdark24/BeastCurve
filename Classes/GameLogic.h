#pragma once

#include <deque>
#include "Player.h"
#include "cocos2d.h"

class GameLogic
{
public:
    GameLogic(cocos2d::CCSize const & gameSize);
    ~GameLogic();

    int addPlayer();
    void movePlayerLeft(float dt, int id = -1);
    void movePlayerRight(float dt, int id = -1);
    void update(float dt);
    std::deque<Player*> getPlayers();

private:
    cocos2d::CCSize _gameSize;
    int _idPlayer;
    std::deque<Player*> _players;
};

