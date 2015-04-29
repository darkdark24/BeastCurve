#ifndef _BADSLOW_H_
#define _BADSLOW_H_

#include "Bonus.h"

class BadSlow : public Bonus
{
public:
	BadSlow() { _good = false; _color = cocos2d::ccColor4B::ORANGE; }
	virtual ~BadSlow() {}
	virtual void doEffect(Player * player) { player->setSpeed(player->getSpeed() / 2); }
	virtual void doReverseEffect(Player * player) { player->setSpeed(player->getSpeed() * 2); }
};

#endif