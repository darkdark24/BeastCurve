#ifndef _INVINCIBILITY_H_
#define _INVINCIBILITY_H_

#include "Bonus.h"

class Invincibility : public Bonus
{
public:
	Invincibility() { _good = true; _color = cocos2d::ccColor4B::GRAY; }
	virtual ~Invincibility() {}
	virtual void doEffect(Player * player) { player->setTimeHole(7.f); }
	virtual void doReverseEffect(Player * player) { }
};

#endif