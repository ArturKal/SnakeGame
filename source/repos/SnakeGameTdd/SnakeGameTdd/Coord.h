#pragma once
#include "ICoord.h"
class Coord :
	public ICoord
{
public:
	//Constructors
	Coord() ;
	Coord(int x, int y);
	Coord(ICoord * _coord);

	~Coord() {};

	std::string printCoordinates();
	int checkBorders(int fieldcoord);
	// getters and setters methods:
	int getCoordX();
	int getCoordY();
	int setCoordX(int _x);
	int setCoordY(int _y);

	//helping methods:
	int compare(int a, int b);
protected:
	ICoord * Icoord;
};

