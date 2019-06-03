// SnakeGameTdd.cpp : This file contains the 'main' function. Program execution begins and ends there.
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
		{
			std::cout << "\n\n\t!! KONIEC GRY !!\n\n\n";
			_getch();	
			break;
		}
	
		Iboard->SnakeEatsApple(); //put random apple on '.' field	
		if (Iboard->SnakeEatAllApple) { break; }

		Iboard->drawApplOnBoardbyIcoord();
		Iboard->printVector();

		std::cout << "\tTWOJ WYNIK: " << Iboard->getScore() << " \n";
	}
	//delete instances after
	delete Isnake;	delete Iboard;	delete Iapple;
}