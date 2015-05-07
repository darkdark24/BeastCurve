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
	IA(Player*, int, int);
	~IA();

	void	update(std::deque<MyPoint>);

	bool	checkWall();
	bool	checkInFrontOf(MyPoint);
	bool  checkAround2(std::deque<MyPoint>);
	Direction	_dir;

	int		getAngle(MyPoint);

	Player*	_player;
private:
	
	int		_rand;

	int		_minAngle;
	int		_maxAngle;
	double	_tan;
	int		_angle;

	int width;
	int height;
	
};



#endif // !IA_H
