//
//  Player.cpp
//  Beast Curve
//
//  Created by admin on 3/31/15.
//
//

#include "Player.h"
#include "GameLogic.h"

using namespace cocos2d;

Player::Player(int id, MyPoint pos, float dir, ccColor4B color) : _id(id), _pos(pos), _dir(dir), _speed(GameLogic::Speed), _size(GameLogic::SizePoint), _color(color), _isMoving(false), _isDead(false), _score(0), _timeHole(3)
{
}

Player::~Player()
{
}

int Player::getId()
{
    return (_id);
}

MyPoint Player::getPos()
{
    return (_pos);
}

float Player::getDir()
{
    return (_dir);
}

int Player::getSpeed()
{
    return (_speed);
}

int Player::getSize()
{
    return (_size);
}

ccColor4B Player::getColor()
{
    return (_color);
}

bool Player::isMoving()
{
    return (_isMoving);
}

bool Player::isDead()
{
    return (_isDead);
}

int Player::getScore()
{
    return (_score);
}

void Player::setPos(MyPoint pos)
{
    _pos = pos;
}

void Player::setDir(float dir)
{
    _dir = dir;
}

void Player::setSpeed(int speed)
{
    _speed = speed;
}

void Player::setSize(int size)
{
    _size = size;
	_pos.size = size;
}

void Player::setColor(ccColor4B color)
{
    _color = color;
}

void Player::isMoving(bool isMoving)
{
    _isMoving = isMoving;
}

void Player::isDead(bool isDead)
{
    _isDead = isDead;
}

void Player::setScore(int score)
{
    _score = score;
}

void Player::increaseScore()
{
    ++_score;
}

void Player::addPos(MyPoint pos)
{
    _oldPos.push_back(pos);
}

std::deque<MyPoint> Player::getAllPos()
{
    return (_oldPos);
}

float Player::getTimeHole()
{
    return (_timeHole);
}

void Player::setTimeHole(float t)
{
    _timeHole = t;
}

void Player::reset(MyPoint pos, float dir)
{
    _pos = pos;
    _dir = dir;
    _speed = GameLogic::Speed;
    _size = GameLogic::SizePoint;
    _isMoving = false;
    _isDead = false;
    _timeHole = 3;
    _oldPos.clear();
}
