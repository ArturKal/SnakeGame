#pragma once
#include "IBoard.h"
#include "ISnake.h"
#include "IApple.h"

class Board :
	public IBoard
{
public:
	//Constructors
	Board();
	Board(int m_size);
	Board(ISnake *  snakeIntrface, int m_size); //for Mock
	Board(ISnake *  snakeIntrface, IApple * appleInterface,  int m_size); //for Mock
	//Destructors
	~Board();

	//Methods:
	ISnake * snakeIntrface;
	IApple * appleInterface;
	
	//const int size = 0;

	std::vector<std::vector<char>> setSize(int _size);

	void drawSnakeOnBoard(int x, int y);
	void drawSnakeOnBoardbyIcoord();
	void drawApplOnBoardbyIcoord();
	void SnakeEatsApple();
	bool checkSegmentsV(int cx, int cy);
	int setScore();
	int getScore();
	char getvectorCoord(int coordX, int coordY);
	char setvectorCoord(int coordX, int coordY, char x);
	int getvectorSize();
	std::vector<std::vector<char>> getVector();
	bool checkVectorForFreeSpace();

	std::vector<std::vector<char>> clear();
	void printVector();
};