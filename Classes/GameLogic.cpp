#include "GameLogic.h"
#include "GameScene.h"

using namespace cocos2d;

uint16_t GameLogic::AngleTurn = 100;
uint16_t GameLogic::SizePoint = 4;
uint16_t GameLogic::Speed = 50;

int random(int a, int b)
{
    return (rand() % (b - a) + a);
}

GameLogic::GameLogic(CCSize const & gameSize) : _idPlayer(0), _gameSize(gameSize), _nbPlayerAlive(0)
{
}

GameLogic::~GameLogic()
{
}

void GameLogic::setOnDeadCallback(GameScene* gs)
{
    _gs = gs;
}

Player* GameLogic::addPlayer()
{
    ++_nbPlayerAlive;
    ++_idPlayer;
    
    MyPoint pos;
    pos.x = random((int)(_gameSize.width / 5), (int)(_gameSize.width - _gameSize.width / 5));
    pos.y = random((int)(_gameSize.height / 5), (int)(_gameSize.height - _gameSize.height / 5));
    pos.size = SizePoint;

    int dir = random(0, 360);
    
    ccColor4B color;
    
    color.r = random(0, 255);
    color.g = random(0, 255);
    color.b = random(0, 255);
    color.a = 255;
    
    _players.push_back(new Player(_idPlayer, pos, dir, color));
	return _players.back();
}

void GameLogic::movePlayerLeft(float dt, int id)
{
    for (Player* p : _players)
    {
        if (p->isDead() == false && (p->getId() == id || id == -1))
            p->setDir(p->getDir() + AngleTurn * dt);
    }
}

void GameLogic::movePlayerRight(float dt, int id)
{
    for (Player* p : _players)
    {
        if (p->isDead() == false && (p->getId() == id || id == -1))
            p->setDir(p->getDir() - AngleTurn * dt);
    }
}

void GameLogic::update(float dt)
{
    for (Player* p : _players)
    {
        if (p->isDead() == false)
        {
            if (p->getTimeHole() <= 0 && random(0, 70) == 0)
                p->setTimeHole(random(40, 70) / 100.0);

            MyPoint nextPos = p->getPos();
            if (p->getTimeHole() > 0)
                p->setTimeHole(p->getTimeHole() - dt);
            else
            {
                p->addPos(nextPos);
                _points.push_back(nextPos);
            }
            nextPos.x += (cos(CC_DEGREES_TO_RADIANS(p->getDir())) * p->getSpeed() * dt);
            nextPos.y += (sin(CC_DEGREES_TO_RADIANS(p->getDir())) * p->getSpeed() * dt);
            p->setPos(nextPos);

            if (p->getPos().x - p->getSize() < 0 || p->getPos().x + p->getSize() > _gameSize.width || p->getPos().y - p->getSize() < 0 || p->getPos().y + p->getSize() > _gameSize.height)
            {
                p->isDead(true);
                incScore();
                --_nbPlayerAlive;
                continue;
            }

            if (p->getTimeHole() <= 0)
            {
                int gridPos = (int)(p->getPos().x / _gameSize.width * GridX + (GridX * p->getPos().y / _gameSize.height * GridY));

                if (_grid[gridPos] == true)
                {
                    MyPoint pp;

                    pp.x = p->getPos().x + (cos(CC_DEGREES_TO_RADIANS(p->getDir()))) * p->getSize();
                    pp.y = p->getPos().y + (sin(CC_DEGREES_TO_RADIANS(p->getDir()))) * p->getSize();
                    for (MyPoint point : _points)
                    {
                        int tmp = sqrtf((point.x - pp.x) * (point.x - pp.x) + (point.y - pp.y) * (point.y - pp.y));
                        //if (tmp < point.size + p->getSize())
                        if (tmp < point.size)
                        {
                            p->isDead(true);
                            incScore();
                           --_nbPlayerAlive;
                            return;
                        }
                    }
                }
                else
                    _grid[gridPos] = true;
            }
        }
    }
}

std::deque<Player*> GameLogic::getPlayers()
{
    return (_players);
}

bool GameLogic::hasGameEnd()
{
    return (_nbPlayerAlive <= 1);
}

void GameLogic::nextGame()
{
    _nbPlayerAlive = _players.size();
    _grid.clear();
    _points.clear();
    for (auto p : _players)
    {
        MyPoint pos;
        
        pos.x = random((int)(_gameSize.width / 5), (int)(_gameSize.width - _gameSize.width / 5));
        pos.y = random((int)(_gameSize.height / 5), (int)(_gameSize.height - _gameSize.height / 5));
        pos.size = SizePoint;

        int dir = random(0, 360);

        p->reset(pos, dir);
    }
}

void GameLogic::reset()
{
    for (auto p : _players)
        p->setScore(0);
    nextGame();
}

Player* GameLogic::getWinner()
{
    return (_winner);
}

Player* GameLogic::finalWinner()
{
    Player* winner = nullptr;

    for (auto p : _players)
    {
        if (p->getScore() >= GameScene::ScoreMax)
        {
            if (winner)
            {
                if (winner->getScore() < p->getScore())
                {
                    if (p->getScore() - winner->getScore() > 1)
                        winner = p;
                    else
                        winner = nullptr;
                }
                else if (winner->getScore() - p->getScore() <= 1)
                    winner = nullptr;
            }
            else
                winner = p;
        }
    }
    return (winner);
}

void GameLogic::incScore()
{
    for (auto p : _players)
    {
        if (!p->isDead())
        {
            p->increaseScore();
            _winner = p;
        }
    }
    _gs->onDead();
}
