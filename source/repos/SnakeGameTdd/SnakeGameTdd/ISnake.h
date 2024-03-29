#pragma once
#include "Coord.h"
class ISnake
{
public:
	//Constructors
	ISnake() {};
	ISnake(int x, int y) {};

	virtual ~ISnake() {};

	virtual char setDirection(char moveKey) = 0;
	virtual ICoord * changeSnakeHeadCoordinates(char _direction) = 0;
	virtual void setSnakeTail() = 0;
	virtual bool snakeHitItself() = 0;
	virtual void putSnakeHeadCoorinatesToDeque(Coord _snakeHead) = 0;
	// getters and setters methods:
	virtual char getDirection() = 0;
	virtual ICoord * getSnakeHead() = 0;
	virtual ICoord * getSnakeTail() = 0;
	virtual ICoord * getFieldToClear() = 0;
	virtual std::deque<Coord> getCoord_Container() = 0;
	virtual int setSnakeLength() = 0;
	virtual int getSnakeLength() = 0;
	virtual bool getEndGame() = 0;


	//std::deque<Segments> Coord_Container; /*Segments class instance*/

protected:
	std::deque<Coord> Coord_Container; /*Segments class instance*/

	char direction = 'r'; //d=down// Variable control of the snake's direction
	ICoord * snakeHead;
	ICoord * snakeTail;
	ICoord *fieldToClear;
	int snakeLength = 2;
	bool endGame = false;
};