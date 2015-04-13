#ifndef _BONUS_H_
#define _BONUS_H_

#include <deque>
#include <list>
#include <2d\CCSprite.h>
#include "Player.h"

class Bonus
{
public:
	Bonus();
	virtual ~Bonus();
	virtual void selectTargetEffect(std::deque<Player*> &, int);
	void update(double, std::deque<Player*> &);
	virtual void doEffect(Player *) = 0;
	virtual void doReverseEffect(Player *) = 0;
	void draw();
	void setPosition(int, int);
	bool isAlive() const;
	inline MyPoint getPosition() const { return _pos; }
	inline bool isActive() const { return _active; }
	inline cocos2d::CCSprite * getSprite() { return _sprite; }
	inline cocos2d::ccColor4B getColor() const { return _color; }
protected:
	bool _good;
	bool _active;
	bool _alive;
	double _time;
	std::list<int> _players;
	cocos2d::CCSprite* _sprite;
	MyPoint _pos;
	cocos2d::ccColor4B _color;
private:
	int random(int, int);
};

#endif