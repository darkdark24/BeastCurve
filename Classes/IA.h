#ifndef IA_H
#define	IA_H

#include "MyPoint.hpp"
#include <deque>

enum Direction
{
	LEFT,
	RIGHT
};

class IA
{
public:
	IA(int);
	~IA();

	void	update();
	Direction	_dir;
	int _id;
private:
	

	
};



#endif // !IA_H
