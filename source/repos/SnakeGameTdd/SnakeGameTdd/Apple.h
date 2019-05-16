#pragma once
#include "IApple.h"
class Apple :
	public IApple
{
public:
	//Constructors
	Apple();
	Apple(ICoord * _coord);
	Apple(int x, int y);

	~Apple();

	void putRandomAppleOnboard();
	// getters and setters methods:
	int getAppleCoordX();
	int getAppleCoordY();
	ICoord * getAppleCoords();

protected:
	ICoord * IcoordApple;
};

