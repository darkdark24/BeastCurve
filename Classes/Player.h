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
#include "MyPoint.hpp"
#include <deque>

class Player
{
public:
    Player(int id, MyPoint pos, float dir, cocos2d::ccColor4B color);
    ~Player();

    int getId();
    MyPoint getPos();
    float getDir();
    int getSpeed();
    int getSize();
    cocos2d::ccColor4B getColor();
    bool isMoving();
    bool isDead();
    int getScore();

    void setPos(MyPoint pos);
    void setDir(float dir);
    void setSpeed(int speed);
    void setSize(int size);
    void setColor(cocos2d::ccColor4B color);
    void isMoving(bool isMoving);
    void isDead(bool isDead);
    void setScore(int score);

    void increaseScore();
    void addPos(MyPoint pos);
    std::deque<MyPoint> getAllPos();

    float getTimeHole();
    void setTimeHole(float t);

    void reset(MyPoint pos, float dir);
	
	bool getReverse() const;
	void setReverse(bool);
private:
    int _id;
    MyPoint _pos;
    float _dir;
    int _speed;
    int _size;
    cocos2d::ccColor4B _color;
    bool _isMoving;
    bool _isDead;
    int _score;
    float _timeHole;
	bool _reverse;

    std::deque<MyPoint> _oldPos;
};

#endif
