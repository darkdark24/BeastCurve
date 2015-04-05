#include "GameLogic.h"

using namespace cocos2d;

uint16_t GameLogic::AngleTurn = 100;
uint16_t GameLogic::SizePoint = 4;
uint16_t GameLogic::Speed = 50;

GameLogic::GameLogic(CCSize const & gameSize) : _idPlayer(0), _gameSize(gameSize), _nbPlayerAlive(0)
{
}

GameLogic::~GameLogic()
{
}

int GameLogic::addPlayer()
{
    ++_nbPlayerAlive;
    ++_idPlayer;
    
    MyPoint pos;
    pos.x = random<int>(_gameSize.width / 5, _gameSize.width - _gameSize.width / 5);
    pos.y = random<int>(_gameSize.height / 5, _gameSize.height - _gameSize.height / 5);
    pos.size = SizePoint;

    int dir = random(0, 360);
    
    ccColor4B color(random(0, 255), random(0, 255), random(0, 255), 255);
    
    _players.push_back(new Player(_idPlayer, pos, dir, color));
    
    return (_idPlayer);
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
            if (random(0, 70) == 0)
                p->setTimeHole(random(20, 40) / 100.0);

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
                --_nbPlayerAlive;
                continue;
            }

            if (p->getTimeHole() <= 0)
            {
                //CCLOG("TEST: %f %f", p->getPos().x / _gameSize.width * GridX, p->getPos().y / _gameSize.height * GridY);
                int gridPos = (int)(p->getPos().x / _gameSize.width * GridX + (GridX * p->getPos().y / _gameSize.height * GridY));
                //CCLOG("Pos: %d", gridPos);

                if (_grid[gridPos] == true)
                {
                    CCLOG("CHECK %d", gridPos);
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
    /*for (auto t : _grid)
    {
        if (t.second)
        {
            CCLOG("%d %d", t.first % GridX, t.first / GridX);
            DrawPrimitives::setDrawColor4B(50, 50, 50, 255);
            //DrawPrimitives::drawSolidRect(Vec2((t.first % GridX) * GridX / _gameSize.width, (t.first / GridX) * GridY / _gameSize.height), Vec2();
            DrawPrimitives::drawPoint(Vec2((t.first % GridX) * GridX / _gameSize.width, (t.first / GridX) * GridY / _gameSize.height));
        }
    }*/
}

std::deque<Player*> GameLogic::getPlayers()
{
    return (_players);
}

bool GameLogic::hasGameEnd()
{
    return (_nbPlayerAlive == 0);
}

void GameLogic::nextGame()
{
    _nbPlayerAlive = _players.size();
    for (auto p : _players)
    {
        MyPoint pos;
        pos.x = random<int>(_gameSize.width / 5, _gameSize.width - _gameSize.width / 5);
        pos.y = random<int>(_gameSize.height / 5, _gameSize.height - _gameSize.height / 5);
        pos.size = SizePoint;

        int dir = random(0, 360);

        p->reset(pos, dir);
    }
}
