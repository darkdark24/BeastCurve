#include "Bonus.h"

Bonus::Bonus()
{
	_good = false;
	_active = false;
	_alive = true;
	_time = 5.f;
	_pos.size = 10;
}

Bonus::~Bonus()
{
}

void Bonus::update(double dt, std::deque<Player *> & players)
{
	if (_active)
	{
		if (_alive && _time < 0)
		{
			_alive = false;
			for (std::deque<Player *>::const_iterator it = players.begin();
				it != players.end(); ++it)
			{
				for (int id : _players)
				{
					if ((*it)->getId() == id)
						doReverseEffect(*it);
				}
			}
			_players.clear();
		}
		_time -= dt;
	}
}

void Bonus::selectTargetEffect(std::deque<Player*> & listPlayer, int id)
{
	_active = true;
	for (std::deque<Player *>::const_iterator it = listPlayer.begin();
		it != listPlayer.end(); ++it)
	{
		if (_good && (*it)->getId() == id)
		{
			doEffect(*it);
			_players.push_back((*it)->getId());
		}
		else if (!_good && (*it)->getId() != id)
		{
			doEffect(*it);
			_players.push_back((*it)->getId());
		}
	}
}

void	Bonus::draw()
{

}

bool	Bonus::isAlive() const
{
	return _alive;
}

int		Bonus::random(int a, int b)
{
    return (rand() % (b - a) + a);
}

void	Bonus::setPosition(int width, int height)
{
	_pos.x = this->random(0, width);
	_pos.y = this->random(0, height);
//	_sprite->setPosition(cocos2d::ccp(_pos.x, _pos.y));

}