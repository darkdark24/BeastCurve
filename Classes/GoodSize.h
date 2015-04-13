#ifndef _GOODSIZE_H_
#define _GOODSIZE_H_

#include "Bonus.h"

class GoodSize : public Bonus
{
public:
	GoodSize() { _good = true; _color = cocos2d::ccColor4B::GREEN; }
	virtual ~GoodSize() {}
	virtual void doEffect(Player * player) { player->setSize(player->getSize() * 2); }
	virtual void doReverseEffect(Player * player) { player->setSize(player->getSize() / 2); }
};

#endif