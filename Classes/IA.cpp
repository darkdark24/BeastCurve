#include	"IA.h"
#include	"GameLogic.h"
IA::IA(Player* p)
	:_player(p),
	_rand(0)
{
}

IA::~IA()
{
}

void	IA::update()
{
	_rand++;
	if (_rand < 20)
	{
		_dir = Direction::LEFT;
	}
	else if (_rand > 30)
	{
		_dir = Direction::RIGHT;
		if (_rand > 50)
			_rand = 0;
	}
}