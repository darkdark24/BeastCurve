#include "GameLogic.h"

using namespace cocos2d;

GameLogic::GameLogic(CCSize const & gameSize) : _idPlayer(0), _gameSize(gameSize)
{
}

GameLogic::~GameLogic()
{
}

int GameLogic::addPlayer()
{
    ++_idPlayer;
    CCPoint pos(random(_gameSize.width / 5, _gameSize.width - _gameSize.width / 5), random(_gameSize.height / 5, _gameSize.height - _gameSize.height / 5));
    int dir = random(0, 360);
    ccColor4B color(random(0, 255), random(0, 255), random(0, 255), 255);
    _players.push_back(new Player(_idPlayer, pos, dir, color));
    return (_idPlayer);
}

void GameLogic::movePlayerLeft(float dt, int id)
{
    for (Player* p : _players)
    {
        if (p->getId() == id || id == -1)
            p->setDir(p->getDir() + 100 * dt);
    }
}

void GameLogic::movePlayerRight(float dt, int id)
{
    for (Player* p : _players)
    {
        if (p->getId() == id || id == -1)
            p->setDir(p->getDir() - 100 * dt);
    }
}

void GameLogic::update(float dt)
{
    for (Player* p : _players)
    {
        if (random(0, 70) == 0)
            p->setTimeHole(random(20, 40) / 100.0);

        CCPoint nextPos = p->getPos();
        if (p->getTimeHole() > 0)
            p->setTimeHole(p->getTimeHole() - dt);
        else
            p->addPos(nextPos);
        nextPos.x += (cos(CC_DEGREES_TO_RADIANS(p->getDir())) * p->getSpeed() * dt);
        nextPos.y += (sin(CC_DEGREES_TO_RADIANS(p->getDir())) * p->getSpeed() * dt);
        p->setPos(nextPos);
    }
}

std::deque<Player*> GameLogic::getPlayers()
{
    return (_players);
}