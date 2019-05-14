#pragma once
class IBoard
{
public:
	//Constructors
	IBoard() {};
	IBoard(int m_size) {}

	//Destructors
	virtual ~IBoard() {};

	//Methods
	virtual std::vector<std::vector<char>> setSize(int) = 0;
	virtual void drawSnakeOnBoard(int x, int y) = 0;
	virtual void drawSnakeOnBoardbyIcoord() = 0;
	virtual void drawApplOnBoardbyIcoord() = 0;
	virtual void SnakeEatsApple() = 0;
	virtual int setScore() = 0;
	virtual int getScore() = 0;
	virtual std::vector<std::vector<char>> clear() =  0;
	virtual void printVector() = 0;
	virtual char getvectorCoord(int coordX, int coordY) = 0;
	virtual char setvectorCoord(int coordX, int coordY, char x) = 0;
	virtual int getvectorSize() = 0;
	virtual std::vector<std::vector<char>> getVector() = 0;
	virtual bool checkVectorForFreeSpace() = 0;
	virtual bool snaketailnotEq() = 0;

	bool SnakeEatAllApple = false;
	bool eatApple = false;
protected:
	int score = 0;
	std::vector <std::vector<char> > vec2D;
};