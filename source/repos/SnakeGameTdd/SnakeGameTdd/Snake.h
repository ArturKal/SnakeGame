#pragma once
#include "ISnake.h"
#include "ICoord.h"
class Snake :
	public ISnake
{
public:
	//Constructors
	Snake();
	Snake(int x, int y);
	Snake(ICoord * _coord);

	~Snake();

	char setDirection(char moveKey) ;
	ICoord * changeSnakeHeadCoordinates(char _direction);
	void setSnakeTail();
	bool snakeHitItself();
	void putSnakeHeadCoorinatesToDeque(Coord _snakeHead);
	// getters and setters methods:
	char getDirection();
	ICoord * getSnakeHead();
	ICoord * getSnakeTail();
	ICoord * getFieldToClear();
	std::deque<Coord> getCoord_Container();
	int setSnakeLength();
	int getSnakeLength();
	bool getEndGame();
protected:
	ICoord * Icoord;
};

