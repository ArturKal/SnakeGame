#include "pch.h"
#include "Coord.h"


//Constructors:
Coord::Coord()
{
	Xcolumn = BOARDSIZE / 2;
	Yrow = BOARDSIZE / 2;
}

Coord::Coord(ICoord * _coord) : Icoord(_coord)
{
	coords = Icoord;
}

Coord::Coord(int x, int y) 
{
	try
	{
		compare(x, y);
	}
	catch (std::runtime_error & e)
	{
		std::cout << "Runtime error: " << e.what();
			if (x < 0 || x > BOARDSIZE) x = 0;
			if (y < 0 || y > BOARDSIZE) y = 0;	
	}
		setCoordX(x);
		setCoordY(y);
}


//Methods:
int Coord::getCoordX()
{
	return this->Xcolumn;
}

int Coord::getCoordY()
{
	return this->Yrow;
}

int Coord::setCoordX(int _x)
{
	return this->Xcolumn = checkBorders(_x);
}

int Coord::setCoordY(int _y)
{
	return this->Yrow = checkBorders(_y);
}

std::string Coord::printCoordinates()
{
	std::string coordX = std::to_string(getCoordX());
	std::string coordY = std::to_string(getCoordY());

	std::string concatate = "Coord Xcolumn : " + coordX + " Coord Ycolumn : " + coordY + "\n";
	return concatate;
}

int Coord::checkBorders(int fieldcoord)
{
	if (fieldcoord >= BOARDSIZE)
		 fieldcoord = 0;
	if (fieldcoord <= -1)
		 fieldcoord = BOARDSIZE - 1;
	return fieldcoord;
}

int Coord::compare(int a, int b) 
{
	if (a < 0 || b < 0) {
		throw std::runtime_error("Coord parameter cannot be minus value, changed wrong value to 0\n");
	}
	if (a > BOARDSIZE || b > BOARDSIZE) {
		throw std::runtime_error("Coord parameter cannot be bigger then Boardsize value, changed wrong value to 0\n");
	}
}