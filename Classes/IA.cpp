#include <algorithm>
#include	"IA.h"
#include	"GameLogic.h"
#include <math.h>

#define PI 3.14159265

IA::IA(Player* p, int w, int h)
	:_player(p),
	_rand(0)
{
	width = w;
	height = h;
}

IA::~IA()
{
}

bool	IA::checkWall()
{
	MyPoint pos = _player->getPos();

	if (pos.x > (width - 50))
	{
		if (_player->getDir() >= 0)
			_dir = Direction::LEFT;
		else
			_dir = Direction::RIGHT;
		return true;
	}
	if (pos.x < 50)
	{
		if (_player->getDir() >= 180)
			_dir = Direction::LEFT;
		else
			_dir = Direction::RIGHT;
		return true;
	}
	if (pos.y > (height - 50))
	{
		if (_player->getDir() >= 90)
			_dir = Direction::LEFT;
		else
			_dir = Direction::RIGHT;
		return true;
	}
	if (pos.y < 50)
	{
		if (_player->getDir() >= 270)
			_dir = Direction::LEFT;
		else
			_dir = Direction::RIGHT;
		return true;
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


bool	IA::checkAround2(std::deque<MyPoint> _points)
{
	MyPoint pos = _player->getPos();
	int param = 50;
	int size = 10;

	for (int i = 0; i < param; i++)
		{
			for (int j=0; j< _points.size(); j++)
			{			
				if (_player->getDir() >= 0 && _player->getDir() <= 90)
				{
					MyPoint tmp = pos;
					tmp.x += param;
					tmp.y += param;
					if ((((int)_points[j].x - size) < (int)(tmp.x-i) && ((int)_points[j].x + size) > (int)(tmp.x-i)) && (((int)_points[j].y - size) < (int)(tmp.y) && ((int)_points[j].y + size) > (int)(tmp.y)))
					{
						_dir = Direction::RIGHT;
						return true;
					}
					if ((((int)_points[j].x - size) < (int)(tmp.x) && ((int)_points[j].x + size) > (int)(tmp.x)) && (((int)_points[j].y - size) < (int)(tmp.y-i) && ((int)_points[j].y + size) > (int)(tmp.y-i)))
					{
						_dir = Direction::LEFT;
						return true;
					}
				}

				if (_player->getDir() > 90 && _player->getDir() <= 180)
				{
					MyPoint tmp1 = pos;
					tmp1.x -= param;
					tmp1.y += param;
					if ((((int)_points[j].x - size) < (int)(tmp1.x+i) && ((int)_points[j].x + size) > (int)(tmp1.x+i)) && (((int)_points[j].y - size) < (int)(tmp1.y) && ((int)_points[j].y + size) > (int)(tmp1.y)))
					{
						_dir = Direction::LEFT;
						return true;
					}
					if ((((int)_points[j].x - size) < (int)(tmp1.x) && ((int)_points[j].x + size) > (int)(tmp1.x)) && (((int)_points[j].y - size) < (int)(tmp1.y-i) && ((int)_points[j].y + size) > (int)(tmp1.y-i)))
					{
						_dir = Direction::RIGHT;
						return true;
					}
				}
				if (_player->getDir() > 180 && _player->getDir() <= 270)
				{
					MyPoint tmp2 = pos;
					tmp2.x -= param;
					tmp2.y -= param;
					if ((((int)_points[j].x - size) < (int)(tmp2.x+i) && ((int)_points[j].x + size) > (int)(tmp2.x+i)) && (((int)_points[j].y - size) < (int)(tmp2.y) && ((int)_points[j].y + size) > (int)(tmp2.y)))
					{
						_dir = Direction::RIGHT;
						return true;
					}
					if ((((int)_points[j].x - size) < (int)(tmp2.x) && ((int)_points[j].x + size) > (int)(tmp2.x)) && (((int)_points[j].y - size) < (int)(tmp2.y+i) && ((int)_points[j].y + size) > (int)(tmp2.y+i)))
					{
						_dir = Direction::LEFT;
						return true;
					}
				}
				
				if (_player->getDir() > 270 && _player->getDir() <= 360)
				{
					MyPoint tmp3 = pos;
					tmp3.x += param;
					tmp3.y -= param;
					if ((((int)_points[j].x - size) < (int)(tmp3.x-i) && ((int)_points[j].x + size) > (int)(tmp3.x-i)) && (((int)_points[j].y - size) < (int)(tmp3.y) && ((int)_points[j].y + size) > (int)(tmp3.y)))
					{
						_dir = Direction::LEFT;
						return true;
					}
					if ((((int)_points[j].x - size) < (int)(tmp3.x) && ((int)_points[j].x + size) > (int)(tmp3.x)) && (((int)_points[j].y - size) < (int)(tmp3.y+i) && ((int)_points[j].y + size) > (int)(tmp3.y+i)))
					{
						_dir = Direction::RIGHT;
						return true;
					}
				}
		}
	}
	return false;
}

void	IA::update(std::deque<MyPoint> _points)
{
	_dir = Direction::NONE;
	if (checkWall())
		return;
	if (checkAround2(_points))
		return;
	int iSecret, iGuess;
  /* initialize random seed: */
  srand (time(NULL));

  /* generate secret number between 1 and 10: */
  iSecret = rand() % 6 + 1;
  if (iSecret == 1)
	  _dir = Direction::LEFT;
   if (iSecret == 2)
	   _dir = Direction::RIGHT;
    if (iSecret >= 3)
		_dir = Direction::NONE;
	return;
}