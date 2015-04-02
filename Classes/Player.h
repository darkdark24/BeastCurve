//
//  Player.h
//  Beast Curve
//
//  Created by admin on 3/31/15.
//
//

#ifndef Beast_Curve_Player_h
#define Beast_Curve_Player_h

#include "cocos2d.h"

class Player
{
public:
    Player(int id, cocos2d::CCPoint pos, float dir, cocos2d::ccColor4B color);
    ~Player();

    int getId();
    cocos2d::CCPoint getPos();
    float getDir();
    int getSpeed();
    cocos2d::ccColor4B getColor();
    bool isMoving();
    bool isDead();
    int getScore();

    void setPos(cocos2d::CCPoint pos);
    void setDir(float dir);
    void setSpeed(int speed);
    void setColor(cocos2d::ccColor4B color);
    void isMoving(bool isMoving);
    void isDead(bool isDead);

    void increaseScore();
    void addPos(cocos2d::CCPoint pos);
    std::deque<cocos2d::CCPoint> getAllPos();

    float getTimeHole();
    void setTimeHole(float t);

private:
    int _id;
    cocos2d::CCPoint _pos;
    float _dir;
    int _speed;
    cocos2d::ccColor4B _color;
    bool _isMoving;
    bool _isDead;
    int _score;
    float _timeHole;

    std::deque<cocos2d::CCPoint> _oldPos;
};

#endif
