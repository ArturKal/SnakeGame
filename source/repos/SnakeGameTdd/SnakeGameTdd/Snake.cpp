#include "pch.h"
#include "Snake.h"
#include <iostream>

//Constructors:
Snake::Snake()
{
	ICoord * _coord = new Coord();
	Icoord = _coord;
	snakeHead = Icoord;
}

Snake::Snake(int x, int y)
{
	ICoord * _coord = new Coord(x ,y);
	Icoord = _coord;
	snakeHead = Icoord;
}

Snake::Snake(ICoord * _coord) : Icoord(_coord)
{
	snakeHead = Icoord;
	snakeTail = snakeHead;
	fieldToClear = snakeTail; //Has to be set at begining
}

//Destructor:
Snake::~Snake()
{
}

//Methods:
char Snake::setDirection(char moveKey)
{
	if (moveKey == 'w' && (direction == 'l' || direction == 'r')) return direction = 'u';
	if (moveKey == 's' && (direction == 'l' || direction == 'r')) return direction = 'd';
	if (moveKey == 'd' && (direction == 'u' || direction == 'd')) return direction = 'r';
	if (moveKey == 'a' && (direction == 'u' || direction == 'd')) return direction = 'l';
	if (moveKey == 'p') _getch();
	return direction;
}

ICoord * Snake::changeSnakeHeadCoordinates(char _direction)
{
	int Xx = snakeHead->getCoordX();
	int Yy = snakeHead->getCoordY();
	Coord coords(Xx, Yy);
	putSnakeHeadCoorinatesToDeque(coords);


	if (direction == 'u')
	{
		getSnakeHead()->setCoordX(Xx - 1);
	}
	if (direction == 'd')
	{
		getSnakeHead()->setCoordX(Xx + 1);
	}
	if (direction == 'l')
	{
		getSnakeHead()->setCoordY(Yy - 1);
	}
	if (direction == 'r')
	{
		getSnakeHead()->setCoordY(Yy + 1);
	}

	return snakeHead;
}

void Snake::setSnakeTail()
{
	if (Coord_Container.size() >= snakeLength)
	{
		snakeTail = 
			new Coord(Coord_Container.at(1).getCoordX(), 
						Coord_Container.at(1).getCoordY());

		fieldToClear =
			new Coord(Coord_Container.at(0).getCoordX(), 
						Coord_Container.at(0).getCoordY());

	Coord_Container.pop_front(); //Removes the first element of the container
	}
}

bool Snake::snakeHitItself()
{
	for (auto x : Coord_Container)
	{
		if ((snakeHead->getCoordX() == x.getCoordX()) && 
			(snakeHead->getCoordY() == x.getCoordY()))
		{
			std::cout << "\n\n\t!!! KOLIZJA !!!\n";
			endGame = true;
			break;
		}
	}
	return endGame;
}

void Snake::putSnakeHeadCoorinatesToDeque(Coord _snakeHead)
{
	Coord_Container.push_back(_snakeHead); //put coordinates of snake head at the end
}

char Snake::getDirection()
{
	return direction;
}

ICoord * Snake::getSnakeHead()
{
	return snakeHead;
}

ICoord * Snake::getSnakeTail()
{
	return snakeTail;
}

ICoord * Snake::getFieldToClear()
{
	return fieldToClear;
}

std::deque<Coord> Snake::getCoord_Container()
{
	return Coord_Container;
}

int Snake::setSnakeLength()
{
	return snakeLength++;
}
int Snake::getSnakeLength()
{
	return snakeLength;
}

bool Snake::getEndGame()
{
	return endGame;
}
