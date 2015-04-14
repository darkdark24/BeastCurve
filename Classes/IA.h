#ifndef IA_H
#define	IA_H

#include "MyPoint.hpp"
#include	"Player.h"
#include <deque>

enum Direction
{
	LEFT,
	RIGHT
};

class IA
{
public:
	IA(Player*);
	~IA();

	void	update();
	Direction	_dir;

	Player*	_player;
private:
	
	int		_rand;
	
};



#endif // !IA_H
