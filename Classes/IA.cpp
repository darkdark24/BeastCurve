#include <algorithm>
#include	"IA.h"
#include	"GameLogic.h"
#include <math.h>

#define PI 3.14159265

IA::IA(Player* p)
	:_player(p),
	_rand(0)
{
}

IA::~IA()
{
}

bool	IA::checkWall()
{
	MyPoint pos = _player->getPos();

	if (pos.x > 900 || pos.x < 50)
	{
		if (pos.x > 900 && (_player->getDir() >= 270 || _player->getDir() <= 90))
		{
			_dir = Direction::RIGHT;
			return true;
		}
		if (pos.x < 50 && (_player->getDir() <= 270 && _player->getDir() >= 90))
		{ 
			_dir = Direction::RIGHT;
			return true;
		}
		
	}
	if (pos.y > 430 || pos.y < 50)
	{
		if (pos.y > 430 && (_player->getDir() <= 180 && _player->getDir() >= 0))
		{
			_dir = Direction::RIGHT;
			return true;
		}
		if (pos.y < 50 && (_player->getDir() >= 180 && _player->getDir() <= 360))
		{ 
			_dir = Direction::RIGHT;
			return true;
		}
	}
	return false;
}

bool	IA::checkInFrontOf(MyPoint	_p)
{
	return true;
}

int	IA::getAngle(MyPoint p)
{
	int	result = 0;// = tan(p.y, p.x) * 180 / PI;
	return result;
}

MyPoint	IA::checkAround(std::deque<MyPoint> _points)
{
	MyPoint pos = _player->getPos();
	MyPoint	nearPoint;
	nearPoint.x = 0;
	nearPoint.y = 0;
	int distX = 900;
	int distY = 450;

	MyPoint	Distance;
	Distance.x = -1000;
	Distance.y = -1000;

	for (int i = 0; i < _points.size(); i++)
	{
		double dir = _player->getDir();
		if (dir > 180)
			dir  = 360-dir;
		double m = (dir * PI / 180.0);
		double t = m;
		getAngle(_points[i]);
		if (((pos.x - 50) < _points[i].x) && ((pos.x + 50) > _points[i].x) && ((pos.y - 50) < _points[i].y) && ((pos.y + 50) > _points[i].y))
		{
			if (checkInFrontOf(_points[i]))
			{
				//_dir = Direction::NONE;
				int tmpDistanceX = pos.x - _points[i].x;
				int tmpDistanceY = pos.y - _points[i].y;

				if (tmpDistanceX < 0)
					tmpDistanceX *= -1;
				if (tmpDistanceY < 0)
					tmpDistanceY *= -1;
				if ((tmpDistanceX < distX && tmpDistanceY < distY) && (tmpDistanceX > 5 && tmpDistanceY > 5))
				{
					distX = tmpDistanceX;
					distY = tmpDistanceY;
					Distance.x = pos.x - _points[i].x;
					Distance.y = pos.y - _points[i].y;
				}
			}
		}
	}
	return Distance;
}

void	IA::update(std::deque<MyPoint> _points)
{
	_dir = Direction::NONE;
	if (checkWall())
		return;
	MyPoint Distance = checkAround(_points);
	if ((Distance.x == -1000 && Distance.y == -1000))
		_dir = Direction::NONE;
	else
	{
		if ((Distance.x > 0 && Distance.y > 0) && (Distance.x < 50 && Distance.y < 50))
			_dir = Direction::LEFT;
		else if ((Distance.x > 0 && Distance.y < 0) && (Distance.x < 25 && Distance.y > -50))
			_dir = Direction::RIGHT;
		else if ((Distance.x < 0 && Distance.y < 0) && (Distance.x > -50 && Distance.y > -50))
			_dir = Direction::RIGHT;
		else if ((Distance.x < 0 && Distance.y > 0) && (Distance.x > -50 && Distance.y < 50))
			_dir = Direction::RIGHT;
	}
}