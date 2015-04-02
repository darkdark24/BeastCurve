//
//  Player.cpp
//  Beast Curve
//
//  Created by admin on 3/31/15.
//
//

#include "Player.h"

using namespace cocos2d;

Player::Player(int id, CCPoint pos, float dir, ccColor4B color) : _id(id), _pos(pos), _dir(dir), _speed(100), _color(color), _isMoving(false), _isDead(false), _score(0), _timeHole(0)
{
}

Player::~Player()
{
}

int Player::getId()
{
    return (_id);
}

CCPoint Player::getPos()
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

void Player::setPos(CCPoint pos)
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

void Player::increaseScore()
{
    ++_score;
}

void Player::addPos(CCPoint pos)
{
    _oldPos.push_back(pos);
}

std::deque<CCPoint> Player::getAllPos()
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