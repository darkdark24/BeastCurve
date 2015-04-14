#include	"IA.h"
#include	"GameLogic.h"
IA::IA(int id)
	:_id(id)
{
}

IA::~IA()
{
}

void	IA::update()
{
	_dir = Direction::LEFT;
}