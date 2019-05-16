// SnakeGameTdd.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "pch.h"
#include <iostream>
#include <conio.h>
#include <ctime>
#include <windows.h>

#include "Board.h"
#include "Snake.h"
#include "Coord.h"
#include "Apple.h"


int main()
{
	ISnake * Isnake = new Snake(new Coord());
	IApple * Iapple = new Apple(new Coord());
	IBoard * Iboard = new Board(Isnake, Iapple,  BOARDSIZE);

	for (; ; )
	{
		Sleep(400);
		while (_kbhit())
		{
			char drct = _getch();
			Isnake->setDirection(drct);
		}
		system("cls");
		   
		Isnake->changeSnakeHeadCoordinates(Isnake->getDirection()); //add head to cont and chceck borders
		Iboard->drawSnakeOnBoardbyIcoord();
		
		if (Isnake->snakeHitItself())
			{std::cout << "\n\n\t!! KONIEC GRY !!\n\n\n"; _getch();	break; }
	
		Iboard->SnakeEatsApple(); //put random apple on '.' field	
		if (Iboard->SnakeEatAllApple) { break; }

		Iboard->drawApplOnBoardbyIcoord();
		//if (Iboard->snaketailnotEq())		//	Iboard->drawSnakeOnBoardbyIcoord(); ???
		Iboard->printVector();

		std::cout << "\t\tWYNIK " << Iboard->getScore() << " \n";
		std::cout << "getSnakeHead: " << Isnake->getSnakeHead()->printCoordinates() << " \n";
		if(Isnake->getSnakeTail() != nullptr)
		std::cout << "getSnakeTail: " << Isnake->getSnakeTail()->printCoordinates() << " \n";
		std::cout << "snake->Coord_Container.size() " << Isnake->getCoord_Container().size() << " \n";

		if (Isnake->getFieldToClear() != nullptr)
			std::cout << "Field To Clear: " << Isnake->getFieldToClear()->printCoordinates() << " \n";
	}

	//delete instances after
	delete Isnake;	delete Iboard;	delete Iapple;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
