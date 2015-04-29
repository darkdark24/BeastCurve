#ifndef _REVERSE_H_
#define _REVERSE_H_

#include "Bonus.h"

class Reverse : public Bonus
{
public:
	Reverse() { _good = false; _color = cocos2d::ccColor4B::WHITE; }
	virtual ~Reverse() {}
	virtual void doEffect(Player * player) { player->setReverse(!player->getReverse()); }
	virtual void doReverseEffect(Player * player) { player->setReverse(!player->getReverse()); }
};

#endif