#pragma once
#include "Coord.h"
class ISnake
{
public:
	ISnake() {};
	ISnake(int x, int y) {};

	virtual ~ISnake() {};

	virtual char setDirection(char moveKey) = 0;
	virtual ICoord * changeSnakeHeadCoordinates(char _direction) = 0;
	virtual void checkIfSnakeReachEndOfTheBoard() = 0;
	virtual void setSnakeTail() = 0;
	virtual bool snakeHitItself(bool eg) = 0;
	virtual void putSnakeHeadCoorinatesToDeque() = 0;


	virtual void setXcolumn(int _counter) = 0;
	virtual void setYrow(int _counter) = 0;
	virtual int getXcolumn() = 0;
	virtual int getYrow() = 0;
	virtual char getDirection() = 0;
	virtual ICoord * getSnakeHead() = 0;
	virtual std::deque<Coord> getCoord_Container() = 0;

	//std::deque<Segments> Coord_Container; /*Segments class instance*/
	int snakeLength = 2;
	bool endGame = false;

	ICoord * snakeTail;

protected:
	int Xcolumn;
	int Yrow;
	std::deque<Coord> Coord_Container; /*Segments class instance*/

	char direction = 'r'; //d=down// Variable control of the snake's direction
	ICoord * snakeHead;

};