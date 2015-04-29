#ifndef _GOODSLOW_H_
#define _GOODSLOW_H_

#include "Bonus.h"

class GoodSlow : public Bonus
{
public:
	GoodSlow() { _good = true; _color = cocos2d::ccColor4B::YELLOW; }
	virtual ~GoodSlow() {}
	virtual void doEffect(Player * player) { player->setSpeed(player->getSpeed() / 2); }
	virtual void doReverseEffect(Player * player) { player->setSpeed(player->getSpeed() * 2); }
};

#endif