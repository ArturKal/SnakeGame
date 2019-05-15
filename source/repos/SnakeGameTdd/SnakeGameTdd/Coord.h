#pragma once
#include "ICoord.h"
class Coord :
	public ICoord
{
public:
	Coord() ;
	Coord(int x, int y);
	Coord(ICoord * _coord);

	~Coord() {};

	int getCoordX();
	int getCoordY();

	int setCoordX(int _x);
	int setCoordY(int _y);
	int checkBorders(int fieldcoord);


	//helping methods:
	int compare(int a, int b);

	std::string printCoordinates();
	ICoord * Icoord;

};

