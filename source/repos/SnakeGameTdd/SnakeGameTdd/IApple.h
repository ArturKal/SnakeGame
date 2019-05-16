#pragma once
#include "Coord.h"
class IApple
{
public:
	//Constructors
	IApple() {};
	IApple(int x, int y) {};

	virtual ~IApple() {};

	virtual void putRandomAppleOnboard() = 0;
	// getters and setters methods:
	virtual int getAppleCoordX() = 0;
	virtual int getAppleCoordY() = 0;
	virtual ICoord * getAppleCoords() = 0;

protected:
	ICoord *  AppleCoord;
};

