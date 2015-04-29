#include "GameLogic.h"
#include "GameScene.h"
#include "GoodSpeed.h"
#include "GoodSize.h"
#include "BadSpeed.h"
#include "BadSize.h"
#include "GoodSlow.h"
#include "BadSlow.h"
#include "Reverse.h"
#include "Invincibility.h"

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
	this->_randomBonus.push_back(&GameLogic::createBadSpeed);
	this->_randomBonus.push_back(&GameLogic::createGoodSpeed);
	this->_randomBonus.push_back(&GameLogic::createBadSize);
	this->_randomBonus.push_back(&GameLogic::createGoodSize);
	this->_randomBonus.push_back(&GameLogic::createGoodSlow);
	this->_randomBonus.push_back(&GameLogic::createBadSlow);
	this->_randomBonus.push_back(&GameLogic::createReverse);
	this->_randomBonus.push_back(&GameLogic::createInvincibility);
	_timeBonus = 0;
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
		{
			if (p->getReverse())
	            p->setDir(p->getDir() - AngleTurn * dt);
			else
		        p->setDir(p->getDir() + AngleTurn * dt);
		}
    }
}

void GameLogic::movePlayerRight(float dt, int id)
{
    for (Player* p : _players)
    {
        if (p->isDead() == false && (p->getId() == id || id == -1))
		{
			if (p->getReverse())
	            p->setDir(p->getDir() + AngleTurn * dt);
			else
	            p->setDir(p->getDir() - AngleTurn * dt);
		}
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

			for (Bonus * b : _bonus)
			{
				if (!b->isActive() && collision(b->getPosition(), p->getPos()))
				{
					b->selectTargetEffect(this->_players, p->getId());
				}
			}
        }
    }
	
	std::list<Bonus *>::const_iterator it = _bonus.begin();
	while (it != _bonus.end())
	{
		(*it)->update(dt, _players);
		if (!(*it)->isAlive())
		{
			delete (*it);
			it = _bonus.erase(it);
		}
		else
			++it;
	}

	if (_timeBonus >= TimeBonus)
	{
		this->createNewBonus();
		_timeBonus = 0;
	}
	else
		_timeBonus += dt;
}

std::deque<Player*>& GameLogic::getPlayers()
{
    return (_players);
}

bool GameLogic::hasGameEnd()
{
    return (_nbPlayerAlive <= 0);
}

void GameLogic::nextGame()
{
    _nbPlayerAlive = _players.size();
    _grid.clear();
    _points.clear();

	for (std::list<Bonus *>::const_iterator it = _bonus.begin();
		it != _bonus.end(); ++it)
		delete(*it);
	_bonus.clear();
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

Bonus * GameLogic::createBadSpeed()
{
	return new BadSpeed();
}

Bonus * GameLogic::createGoodSpeed()
{
	return new GoodSpeed();
}

Bonus * GameLogic::createBadSize()
{
	return new BadSize();
}

Bonus * GameLogic::createGoodSize()
{
	return new GoodSize();
}

Bonus * GameLogic::createGoodSlow()
{
	return new GoodSlow();
}

Bonus * GameLogic::createBadSlow()
{
	return new BadSlow();
}

Bonus * GameLogic::createReverse()
{
	return new Reverse();
}

Bonus * GameLogic::createInvincibility()
{
	return new Invincibility();
}

void GameLogic::createNewBonus()
{
	int r = random(0, _randomBonus.size());

	Bonus * bonus = (this->*(_randomBonus[r]))();
	bonus->setPosition(_gameSize.width, _gameSize.height);
//	_gs->addChild(bonus->getSprite(), 1);
	_bonus.push_back(bonus);
}

bool GameLogic::collision(const MyPoint & C1, const MyPoint & C2)
{
   int d2 = (C1.x-C2.x)*(C1.x-C2.x) + (C1.y-C2.y)*(C1.y-C2.y);
   if (d2 > (C1.size + C2.size)*(C1.size + C2.size))
      return false;
   else
      return true;
}
