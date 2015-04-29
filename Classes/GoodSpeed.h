#ifndef _GOODSPEED_H_
#define _GOODSPEED_H_

#include "Bonus.h"

class GoodSpeed : public Bonus
{
public:
	GoodSpeed() { _good = true; _color = cocos2d::ccColor4B::BLUE; _sprite = cocos2d::CCSprite::create("speed_good.png");}
	virtual ~GoodSpeed() {}
	virtual void doEffect(Player * player) { player->setSpeed(player->getSpeed() * 2); }
	virtual void doReverseEffect(Player * player) { player->setSpeed(player->getSpeed() / 2); }
};

#endif