#pragma once
#include "IApple.h"
class Apple :
	public IApple
{
public:
	Apple();
	Apple(ICoord * _coord);
	Apple(int x, int y);

	void putRandomAppleOnboard();
	int getAppleCoordX();
	int getAppleCoordY();
	ICoord * getAppleCoords();


	ICoord * IcoordApple;

	~Apple();
};

