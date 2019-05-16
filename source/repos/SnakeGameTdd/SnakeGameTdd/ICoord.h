#pragma once
class ICoord
{

public:
	//Constructors
	ICoord() {};

	virtual ~ICoord() {};

	virtual int checkBorders(int fieldcoord) = 0;
	virtual std::string printCoordinates() = 0;
	// getters and setters methods:
	virtual int getCoordX() = 0;
	virtual int getCoordY() = 0;
	virtual int setCoordX(int _x) = 0;
	virtual int setCoordY(int _y) = 0;

protected:
	int Xcolumn;
	int Yrow;
	ICoord * coords;
};

