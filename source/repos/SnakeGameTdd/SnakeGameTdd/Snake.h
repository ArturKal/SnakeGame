#pragma once
#include "ISnake.h"
#include "ICoord.h"
class Snake :
	public ISnake
{
public:
	Snake();
	Snake(int x, int y);
	Snake(ICoord * _coord);

	~Snake();

	char setDirection(char moveKey) ;
	ICoord * changeSnakeHeadCoordinates(char _direction);
	void checkIfSnakeReachEndOfTheBoard();
	void setSnakeTail();
	bool snakeHitItself(bool eg);
	void putSnakeHeadCoorinatesToDeque();

	void setXcolumn(int _counter);
	void setYrow(int _counter);
	int getXcolumn();
	int getYrow();
	char getDirection();
	ICoord * getSnakeHead();
	std::deque<Coord> getCoord_Container();


	ICoord * Icoord;
};

