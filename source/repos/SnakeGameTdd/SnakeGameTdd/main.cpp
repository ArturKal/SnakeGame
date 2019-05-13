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
	ICoord * Icoord = new Coord(1,1);
	ISnake * Isnake = new Snake(new Coord(1,0));
	IApple * Iapple = new Apple(new Coord(0,0));
	IBoard * Iboard = new Board(Isnake, Iapple,  BOARDSIZE);

	//IBoard * Iboard = new Board (Isnake , BOARDSIZE);
	//std::cout << "ART" << Iboard->getvectorCoord(7, 7);
	for (; ; )
	{
		Sleep(600);
		while (_kbhit())
		{
			char drct = _getch();
			Isnake->setDirection(drct);
		}
		system("cls");
			   
		Isnake->changeSnakeHeadCoordinates(Isnake->getDirection()); 
		//add head to cont and chceck borders
		Iboard->drawSnakeOnBoardbyIcoord();
		
		Isnake->snakeHitItself(true);
						if (Isnake->endGame)
						{
							std::cout << "\n\n\t!! KONIEC GRY !!\n\n\n"; _getch();	break;

						}
 	
		Iboard->SnakeEatsApple(); //put random apple on '.' field	
		
		if (!Iboard->eatApple) //don't delete last element in vector
		{
			Isnake->setSnakeTail(); //delete last element from container
			if (Isnake->fieldToClear) {
				Iboard->setvectorCoord(
					Isnake->fieldToClear->getCoordX(), Isnake->fieldToClear->getCoordY(), '.');
			}
		}
		
		if (Iboard->SnakeEatAllApple)
		{
			for (int x = 0; x < BOARDSIZE; x++)
			{
				for (int y = 0; y < BOARDSIZE; y++)
					Iboard->setvectorCoord(x, y, 'X');
			}

			Iboard->printVector();
			std::cout << "\t\tWYGRALES TWOJ WYNIK : " << Iboard->getScore() << " \n"; break;
		}

		Iboard->drawApplOnBoardbyIcoord();

		//if (Iboard->snaketailnotEq())
		//	Iboard->drawSnakeOnBoardbyIcoord();

		Iboard->printVector();

		std::cout << "\t\tWYNIK " << Iboard->getScore() << " \n";
		std::cout << "getSnakeHead: " << Isnake->getSnakeHead()->printCoordinates() << " \n";
		if(Isnake->snakeTail != nullptr)
		std::cout << "getSnakeTail: " << Isnake->snakeTail->printCoordinates() << " \n";
		std::cout << "snake->Coord_Container.size() " << Isnake->getCoord_Container().size() << " \n";

		if (Isnake->fieldToClear != nullptr)
			std::cout << "Field To Clear: " << Isnake->fieldToClear->printCoordinates() << " \n";

	}
	
	//delete instances after
	delete Icoord;
	delete Isnake;
	delete Iboard;
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
