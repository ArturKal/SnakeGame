#include "pch.h"
#include "Snake.h"
#include <iostream>

Snake::Snake()
{
	ICoord * _coord = new Coord();
	Icoord = _coord;
	snakeHead = Icoord;
}

Snake::Snake(int x, int y) //DEPRECATED
{
	ICoord * _coord = new Coord(x ,y);
	Icoord = _coord;
	snakeHead = Icoord;

	//std::cout << "CONSTRUKTOR\n";
	this->Xcolumn = x;
	this->Yrow = y;
}

Snake::Snake(ICoord * _coord) : Icoord(_coord)
{
	snakeHead = Icoord;
	//putSnakeHeadCoorinatesToDeque();
	snakeTail = snakeHead;
	fieldToClear = snakeTail; //Has to be set at begining
}

Snake::~Snake()
{
}

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
	Coord coords(snakeHead->getCoordX(), snakeHead->getCoordY());
	putSnakeHeadCoorinatesToDeque(coords);

	if (direction == 'u')
	{
		snakeHead->setCoordX( snakeHead->getCoordX()-1 );
	}
	if (direction == 'd')
	{
		snakeHead->setCoordX(snakeHead->getCoordX() + 1);
	}
	if (direction == 'l')
	{
		snakeHead->setCoordY( (snakeHead->getCoordY() -1) );
	}
	if (direction == 'r')
	{
		snakeHead->setCoordY(snakeHead->getCoordY() + 1);
		//snakeHead.Yrow++;
	}

	//checkIfSnakeReachEndOfTheBoard(); 
	//method not needed anymore set in COORD class
	
	return snakeHead;
}

void Snake::setSnakeTail()
{
	if (Coord_Container.size() >= snakeLength) //>=  ???
	{
		snakeTail = 
			new Coord( Coord_Container[1].getCoordX(), Coord_Container[1].getCoordY() );

		fieldToClear =
			new Coord(Coord_Container[0].getCoordX(), Coord_Container[0].getCoordY());

	Coord_Container.pop_front(); //Removes the first element of the container
	}
}

void Snake::checkIfSnakeReachEndOfTheBoard()
{
	if (snakeHead->getCoordY() == BOARDSIZE) 
	{ 
		snakeHead->setCoordY(0); 
	} //Yrow = 0;
	
	if (snakeHead->getCoordY() == -1) 
	{ 
		snakeHead->setCoordY(BOARDSIZE - 1); 
	} //.Yrow = (BOARDSIZE - 1); }
	if (snakeHead->getCoordX() == BOARDSIZE)
	{
		snakeHead->setCoordX(0); //.Xcolumn = 0;
	}
	if (snakeHead->getCoordX() == -1)
	{
		snakeHead->setCoordX(BOARDSIZE - 1); // .Xcolumn = BOARDSIZE - 1;
	}
}

bool Snake::snakeHitItself()
{
	for (auto x : Coord_Container)
	{
		if ((snakeHead->getCoordX() == x.getCoordX()) && (snakeHead->getCoordY() == x.getCoordY()))
		{
			std::cout << "\n\n\t!!! KOLIZJA !!!\n";
			endGame = true;
			break;
		}
	}
	return endGame;
}

void Snake::putSnakeHeadCoorinatesToDeque(Coord& _snakeHead)
{/*
	if (snakeTail != nullptr && 
		(snakeTail->getCoordX() == snakeHead->getCoordX() 
			&& (snakeTail->getCoordY() == snakeHead->getCoordY()) )
		) 
	{
		std::cout << "snakeTail == snakeHead";
		snakeTail->setCoordX(Coord_Container.at(1).getCoordX());
		snakeTail->setCoordX(Coord_Container.at(1).getCoordY());
	}*/
	//Coord coords(snakeHead->getCoordX(), snakeHead->getCoordY());
	//_snakeHead = coords;
	Coord_Container.push_back(_snakeHead); //put coordinates of snake head
}

void Snake::setXcolumn(int _counter)
{
	 Xcolumn = _counter;
}
int Snake::getXcolumn()
{
	return Xcolumn;
}
void Snake::setYrow(int _counter)
{
	Yrow = _counter;
}
int Snake::getYrow()
{
	return Yrow;
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
