#include "pch.h"
#include "Board.h"
#include <iostream>


//Constructors:
Board::Board() 
{}

Board::Board(int m_size) 
{ 
	vec2D = setSize(m_size); 
}

Board::Board(ISnake * snakeIntrface, int m_size) : snakeIntrface(snakeIntrface) 
{ 
	vec2D = setSize(m_size);
	clear();
	drawSnakeOnBoardbyIcoord();
}; // FORM MOCKS

Board::Board(ISnake *  snakeIntrface, IApple * appleInterface, int m_size) : snakeIntrface(snakeIntrface) , appleInterface(appleInterface)
{
	vec2D = setSize(m_size);
	clear();
	drawSnakeOnBoardbyIcoord();
	drawApplOnBoardbyIcoord();
}

//Destructor
Board::~Board()
{
}

//Methods:
std::vector<std::vector<char>> Board::setSize(int _size) {

	try
	{
		if (_size <= 0 ) {
			throw std::logic_error("Board Size parameter cannot be minus value, changed wrong value to default BOARDSIZE\n");
		}
	}
	catch (std::logic_error & e)
	{
		std::cout << "Logic error: " << e.what();
		_size = BOARDSIZE;
	}
	vec2D.resize(_size, std::vector<char>(_size));
	return vec2D;
}

void Board::drawSnakeOnBoard(int x, int y)
{
	setvectorCoord(x, y, 'o');
}

void Board::drawSnakeOnBoardbyIcoord()
{
	setvectorCoord ((snakeIntrface->getSnakeHead())->getCoordX(),  
					((snakeIntrface->getSnakeHead())->getCoordY()), 'o');
}

void Board::drawApplOnBoardbyIcoord()
{
	if (getvectorCoord(appleInterface->getAppleCoordX(), appleInterface->getAppleCoordY()) == 'o')
	{
		appleInterface->putRandomAppleOnboard();
		drawApplOnBoardbyIcoord();
	}
	setvectorCoord(appleInterface->getAppleCoordX(), appleInterface->getAppleCoordY(), 'x');
}

std::vector<std::vector<char>> Board::clear() {
	for (int y = 0; y < vec2D.size(); y++)
	{
		for (int x = 0; x < vec2D.at(y).size(); x++)
		{
			setvectorCoord(x, y, '.');
		}
	}
	return vec2D;
	//std::vector<std::vector<char>>();
}

void Board::printVector()
{
	//Upper Line 
	for (int i = 0; i < (BOARDSIZE * 2 + 2); ++i) std::cout << "8"; std::cout << std::endl;
	for (auto vec : vec2D)
	{
		std::cout << "8";
		for (auto x : vec)
		{
			std::cout << x << " ";
		}

		if (vec.size() == BOARDSIZE) std::cout << "8";
		std::cout << std::endl;
	}
	//Lower Line 
	for (int i = 0; i < (BOARDSIZE * 2 + 2); ++i) std::cout << "8"; std::cout << std::endl;
}

void Board::SnakeEatsApple()
{
	if (snakeIntrface->getSnakeHead()->getCoordX() == appleInterface->getAppleCoordX()
		&& snakeIntrface->getSnakeHead()->getCoordY() == appleInterface->getAppleCoordY())
	{

		snakeIntrface->setSnakeLength();
		setScore();
		do {
			if (checkVectorForFreeSpace())
			{
				SnakeEatAllApple = true;
				break;
			}
			appleInterface->putRandomAppleOnboard();

		} while (getVector().at(appleInterface->getAppleCoordX())
							.at(appleInterface->getAppleCoordY()) 
								!= '.');
		eatApple = true;
	}
	else
		eatApple = false;
	
	if (!eatApple) //don't delete last element in vector
	{
		snakeIntrface->setSnakeTail(); //delete last element from container
		if (snakeIntrface->getFieldToClear() != snakeIntrface->getSnakeTail()) //valid only at the firs game row
		{
			setvectorCoord(
				snakeIntrface->getFieldToClear()->getCoordX(),
				snakeIntrface->getFieldToClear()->getCoordY(),
				'.');
		}
	}

	if (SnakeEatAllApple)
	{
		for (int x = 0; x < BOARDSIZE; x++)
		{
			for (int y = 0; y < BOARDSIZE; y++)
				setvectorCoord(x, y, 'X');
		}
		printVector();
		std::cout << "\t\tWYGRALES TWOJ WYNIK : " << getScore() << " \n";
	}
}

bool Board::checkSegmentsV(int cx, int cy)
{
	bool rntyp = false; //with false always coming out from the loop
	int count = 0;
	for (auto Xhead : snakeIntrface->getCoord_Container())
	{
		if ( (cx == Xhead.getCoordX() && cy == Xhead.getCoordY())  )
		{
			rntyp = true;
		}
	}
	return rntyp;
}

int Board::setScore()
{
	return score++;
}
int Board::getScore()
{
	return score;
}


char Board::getvectorCoord(int coordX, int coordY)
{
	return vec2D.at(coordX).at(coordY);
}

char Board::setvectorCoord(int coordX, int coordY, char x)
{
	 vec2D.at(coordX).at(coordY) = x;
	 return x;
}

int Board::getvectorSize()
{
	return vec2D.size();
}

std::vector<std::vector<char>> Board::getVector()
{
	return vec2D;
}

bool  Board::checkVectorForFreeSpace()
{
	bool won = true;
	for (auto Column : getVector())
	{
		for (auto Row : Column)
		{
			if (Row == '.')
			{
				won = false;
				break;
			}
		}
		if (!won)
			break;
	}
	return won;
}