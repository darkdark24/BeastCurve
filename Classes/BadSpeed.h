#ifndef _BADSPEED_H_
#define _BADSPEED_H_

#include "Bonus.h"

class BadSpeed : public Bonus
{
public:
	BadSpeed() { _good = false; _color = cocos2d::ccColor4B::RED; }
	virtual ~BadSpeed() {}
	virtual void doEffect(Player * player) { player->setSpeed(player->getSpeed() * 2); }
	virtual void doReverseEffect(Player * player) { player->setSpeed(player->getSpeed() / 2); }
};

#endif