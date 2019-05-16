#include "pch.h"
#include "Apple.h"

//Constructors:
Apple::Apple()
{
	ICoord * _coord = new Coord(BOARDSIZE/2-1 , BOARDSIZE/2-1);
	IcoordApple = _coord;
	AppleCoord = IcoordApple;
}

Apple::Apple(ICoord * _coord) : IcoordApple(_coord)
{
	srand(time(0));
	AppleCoord = IcoordApple;
	putRandomAppleOnboard();
}

Apple::Apple(int x , int y)
{
	ICoord * _coord = new Coord(x , y);
	IcoordApple = _coord;
	AppleCoord = IcoordApple;
}

//Methods:
void Apple::putRandomAppleOnboard()
{
	int rnd = rand() % (BOARDSIZE*BOARDSIZE);
	int x = rnd % BOARDSIZE;
	int y = rnd / BOARDSIZE;
	AppleCoord->setCoordX (x);
	AppleCoord->setCoordY (y);
}

int Apple::getAppleCoordX()
{
	return AppleCoord->getCoordX();
}
int Apple::getAppleCoordY()
{
	return AppleCoord->getCoordY();
}

ICoord * Apple::getAppleCoords()
{
	return AppleCoord;
}

//Destructor:
Apple::~Apple()
{
}
