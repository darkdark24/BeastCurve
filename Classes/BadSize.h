#ifndef _BADSIZE_H_
#define _BADSIZE_H_

#include "Bonus.h"

class BadSize : public Bonus
{
public:
	BadSize() { _good = false; _color = cocos2d::ccColor4B::MAGENTA; }
	virtual ~BadSize() {}
	virtual void doEffect(Player * player) { player->setSize(player->getSize() * 2); }
	virtual void doReverseEffect(Player * player) { player->setSize(player->getSize() / 2); }
};

#endif