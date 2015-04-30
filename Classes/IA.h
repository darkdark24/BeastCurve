#ifndef IA_H
#define	IA_H

#include "MyPoint.hpp"
#include	"Player.h"
#include <deque>

enum Direction
{
	LEFT,
	RIGHT,
	NONE
};

class IA
{
public:
	IA(Player*);
	~IA();

	void	update(std::deque<MyPoint>);

	bool	checkWall();
	bool	checkInFrontOf(MyPoint);
	MyPoint	checkAround(std::deque<MyPoint>);

	Direction	_dir;

	Player*	_player;
private:
	
	int		_rand;

	int		_minAngle;
	int		_maxAngle;
	double	_tan;
	int		_angle;
	
};



#endif // !IA_H
