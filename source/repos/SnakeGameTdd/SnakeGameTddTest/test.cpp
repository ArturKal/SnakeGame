#include "pch.h"
#include <iostream>
#include <vector>
#include <deque>
#include <string>
#include <cmath>
#include <conio.h>
#include <ctime>
#include <windows.h>
#include <gmock/gmock.h>
#include "../SnakeGameTddTest/MockClasses.cpp"

#include "../SnakeGameTdd/IBoard.h"
#include "../SnakeGameTdd/Board.h"
#include "../SnakeGameTdd/IBoard.cpp"
#include "../SnakeGameTdd/Board.cpp"
#include "../SnakeGameTdd/Snake.h"
#include "../SnakeGameTdd/Coord.h"
#include "../SnakeGameTdd/Apple.h"
#include "../SnakeGameTdd/Snake.cpp"
#include "../SnakeGameTdd/Coord.cpp"
#include "../SnakeGameTdd/Apple.cpp"

//===========================Helping Methods Declarations:=============================================
void compareSnakeHeadCoord(ISnake *  snake, int x, int y);
void compareCoordValues(ICoord *  coord, int x, int y);

//========================================================================================================
//===========================================SNAKE TEST===================================================

TEST(TestSnake , CreateSnakeInstanceAndSetSnakeHeadCoordinatedInTheCenterOfTheBoard)
{
	int expected =  BOARDSIZE / 2;
	ISnake * Isnake = new Snake();
	ASSERT_EQ(Isnake->getSnakeHead()->getCoordX(), expected);
	ASSERT_EQ(Isnake->getSnakeHead()->getCoordY(), expected);
}

TEST(TestSnake, CreateSnakeInstanceAndSetSnakeHeadCoordinatedByCoordObjectValues)
{
	ICoord * coord = new Coord((BOARDSIZE - 2), 8);
	ISnake * snake = new Snake(coord);

	EXPECT_EQ(snake->getSnakeHead(), coord);
	EXPECT_GE(snake->getSnakeHead()->getCoordX(), (BOARDSIZE - 2));
	EXPECT_LE(snake->getSnakeHead()->getCoordY(), 8);
	delete snake;
	delete coord;
}

TEST(TestSnake, TestDefaultSnakeConstructorWithTwoIntParameters)
{
	int expected = BOARDSIZE / 2;
	ISnake * Isnake = new Snake(5, 5);
	compareCoordValues(Isnake->getSnakeHead(), 5,5);
	delete Isnake;
}

TEST(TestSnake, setSnakeMovementDirectionBasedOnThePressedKey)
{
	ICoord * mCoord = new Coord();
	ISnake *  snake = new Snake(mCoord);
	char pressedKey_W = 'w';	//press w to set the direction up
	char pressedKey_S = 's';	//press s to set the direction down
	char pressedKey_D = 'd';	//press d to set the direction right
	char pressedKey_A = 'a';	//press a to set the direction left

	ASSERT_EQ(snake->getDirection(), 'r');  //snake by default always starts going right

	ASSERT_EQ(snake->setDirection(pressedKey_D), 'r');
	ASSERT_EQ(snake->getDirection(), 'r');

	ASSERT_EQ(snake->setDirection(pressedKey_S), 'd');
	ASSERT_EQ(snake->getDirection(), 'd');

	ASSERT_EQ(snake->setDirection(pressedKey_A), 'l');
	ASSERT_EQ(snake->getDirection(), 'l');

	ASSERT_EQ(snake->setDirection(pressedKey_W), 'u');
	ASSERT_EQ(snake->getDirection(), 'u');
	delete  mCoord ;
	delete snake ;
}

TEST(TestSnake, setMovementDirectionToRightWhenPreesedKeyIsLeftAndMovementDirectionIsRight)
{
	MockCoord * mCoord = new MockCoord();
	ISnake *  snake = new Snake(mCoord);
	ASSERT_EQ(snake->getDirection(), 'r');
	char leftKey = 'a';
	ASSERT_EQ(snake->setDirection(leftKey), 'r');
	ASSERT_EQ(snake->getDirection(), 'r');
	ASSERT_NE(snake->getDirection(), 'l');
	delete  mCoord;
	delete snake;
}
TEST(TestSnake, setMovementDirectionToLeftWhenPreesedKeyIsRightAndMovementDirectionIsLeft)
{
	MockCoord * mCoord = new MockCoord();
	ISnake *  snake = new Snake(mCoord);
	char leftKey = 'a';
	ASSERT_EQ(snake->setDirection('w'), 'u'); //first set direction to up
	ASSERT_EQ(snake->setDirection(leftKey), 'l'); //then set direction to left
	ASSERT_EQ(snake->setDirection('r'), 'l');
	ASSERT_NE(snake->getDirection(), 'r');
	ASSERT_EQ(snake->getDirection(), 'l');
	delete  mCoord;
	delete snake;
}
TEST(TestSnake, setMovementDirectionToDefaultWhenOtherKeyWaspressedthenASDW)
{
	MockCoord * mCoord = new MockCoord();
	ISnake *  snake = new Snake(mCoord);
	char leftKey = 'a';
	ASSERT_EQ(snake->setDirection('q'), 'r'); 
	ASSERT_EQ(snake->setDirection('t'), 'r');
	ASSERT_EQ(snake->setDirection('='), 'r');
	ASSERT_EQ(snake->getDirection(), 'r');
	delete  mCoord;
	delete snake;
}

TEST(TestSnake, setMovementDirectionToUpWhenPreesedKeyIsDownAndMovementDirectionIsUp)
{
	MockCoord * mCoord = new MockCoord();
	ISnake *  snake = new Snake(mCoord);
	char upKey = 'w';
	ASSERT_EQ(snake->setDirection(upKey), 'u');
	ASSERT_EQ(snake->setDirection('s'), 'u');
	ASSERT_EQ(snake->getDirection(), 'u');
	delete  mCoord;
	delete snake;
}
TEST(TestSnake, setMovementDirectionToDownWhenPreesedKeyIsUpAndMovementDirectionIsDown)
{
	MockCoord * mCoord = new MockCoord();
	ISnake *  snake = new Snake(mCoord);
	ASSERT_EQ(snake->setDirection('s'), 'd');

	char downKey = 's';
	ASSERT_EQ(snake->setDirection(downKey), 'd');
	ASSERT_EQ(snake->setDirection('u'), 'd');
	ASSERT_EQ(snake->getDirection(), 'd');
	delete  mCoord;
	delete snake;
}

TEST(TestSnake, ExpectToThrowOutOfrangeException)
{
	ICoord * coord = new Coord(2, 3);
	ISnake *  snake = new Snake(coord);
	EXPECT_THROW(snake->getCoord_Container().at(0), std::out_of_range);
	Coord coordX(snake->getSnakeHead());
	snake->putSnakeHeadCoorinatesToDeque(coordX);
	ASSERT_EQ(snake->getCoord_Container().size(), 1);
	EXPECT_THROW(snake->getCoord_Container().at(1), std::out_of_range);
	delete coord;
	delete snake;
}

TEST(TestSnake, putHeadSnakeCoordinatesToDequeContainer)
{
	ICoord * coord = new Coord(2,3);
	ISnake *  snake = new Snake(coord);
	Coord x(coord->getCoordX() , coord->getCoordY());
	snake->putSnakeHeadCoorinatesToDeque(x);
	ASSERT_EQ(snake->getCoord_Container().size(), 1);
	ASSERT_EQ(snake->getCoord_Container().at(0).getCoordX(), 2);
	ASSERT_EQ(snake->getCoord_Container().at(0).getCoordY(), 3);
	ASSERT_EQ(snake->getSnakeHead(), coord); //Compare addresses
	delete coord;
	delete snake;
}

TEST(TestSnake, putHeadSnakeCoordinatesToDequeContainerUsingGMOCK)
{
	using::testing::Return;
	using::testing::AnyNumber;

	int returnValue = (BOARDSIZE - 2);
	int returnValueTwo = (BOARDSIZE/2);
	MockCoord * mCoord = new MockCoord();
	ISnake *  snake = new Snake(mCoord);

	EXPECT_CALL(*mCoord, getCoordX()).WillRepeatedly(Return(returnValue));
	EXPECT_CALL(*mCoord, getCoordY()).WillRepeatedly(Return(returnValueTwo));

	snake->putSnakeHeadCoorinatesToDeque( 
		Coord(snake->getSnakeHead()->getCoordX() , snake->getSnakeHead()->getCoordY()));
	ASSERT_EQ(snake->getCoord_Container().size(), 1);
	ASSERT_EQ(snake->getCoord_Container().at(0).getCoordX(), (BOARDSIZE - 2));
	ASSERT_EQ(snake->getCoord_Container().at(0).getCoordY(), (BOARDSIZE / 2));
	delete mCoord;
	delete snake;
}

TEST(TestSnake, MoveSnakeToRightOnBoard)
{
	ICoord * coord = new Coord(5, 5);
	ISnake * snake = new Snake(coord);
	char direction = 'r';
	snake->changeSnakeHeadCoordinates(direction);
	compareSnakeHeadCoord(snake, 5, 6);
	delete coord;
	delete snake;
}

TEST(TestSnake, MoveSnakeToRightOnBoardAndPutSnakeHeadCoordinatesToDeque)
{
	ICoord * coord = new Coord(5, 5);
	ISnake * snake = new Snake(coord);
	char direction = 'r';
	snake->changeSnakeHeadCoordinates(direction);
	
	compareSnakeHeadCoord(snake, 5, 6);
	ASSERT_EQ(snake->getCoord_Container().size(), 1);
	ASSERT_EQ(snake->getCoord_Container().at(0).getCoordX(), 5);
	ASSERT_EQ(snake->getCoord_Container().at(0).getCoordY(), 5);
	EXPECT_THROW(snake->getCoord_Container().at(1) ,std::out_of_range ); //throw out_of_range exception
	delete coord;
	delete snake;
}

TEST(TestSnake, SnakeMovesRigtOneFildAndThenPlayerPresUpKeySnakeMovesUpOneField)
{
	ICoord * coord = new Coord(5, 5);
	ISnake * snake = new Snake(coord);
	char pressedKey = 'w';
	snake->changeSnakeHeadCoordinates(snake->getDirection()); //right
	snake->setDirection(pressedKey); //key w is up
	snake->changeSnakeHeadCoordinates(snake->getDirection()); //up
	compareSnakeHeadCoord(snake, 4, 6);
	delete coord;
	delete snake;
}

TEST(TestSnake, SnakeReachedTheBoardEndGMOCK)
{
	using::testing::Return;
	using::testing::_;
	MockCoord * mCoord = new MockCoord();
	ISnake * snake = new Snake(mCoord);

	EXPECT_CALL(*mCoord, getCoordX()).Times(1).WillRepeatedly(Return(0));
	EXPECT_CALL(*mCoord, getCoordY()).WillRepeatedly(Return(5));
	
	compareSnakeHeadCoord(snake, 0, 5);
	delete mCoord;	delete snake;
}

TEST(TestSnake, SnakeReachedTheBoardEndTwice)
{
	ICoord * coord = new Coord((BOARDSIZE - 1), (BOARDSIZE - 1));
	ISnake * snake = new Snake(coord);

	snake->changeSnakeHeadCoordinates(snake->getDirection()); //right
	snake->setDirection('s'); //key w is up
	compareSnakeHeadCoord(snake, (BOARDSIZE - 1), 0);
	snake->changeSnakeHeadCoordinates(snake->getDirection()); //up
	compareSnakeHeadCoord(snake, 0 ,0);
	EXPECT_EQ(snake->getCoord_Container().size() , 2);
	delete coord;
	delete snake;
}

TEST(TestSnake, SnakeMovesRigtOneFildSetSnakeTail)
{
	ICoord * coord = new Coord(5, 5); //snake tail [5,5]
	ISnake * snake = new Snake(coord);
	for (int i = 0; i < 2; ++i)
	{
		snake->changeSnakeHeadCoordinates(snake->getDirection()); //right , deque [5,6][5,7]
		snake->setSnakeTail();
	}
	compareSnakeHeadCoord(snake, 5, 7);
	EXPECT_EQ(snake->getCoord_Container().size(), 1);
	compareCoordValues(snake->getSnakeTail(), 5, 6);
	compareCoordValues(new Coord (snake->getCoord_Container().at(0)) , 5, 6);

	delete coord;	delete snake;
}


TEST(TestSnake, SnakeMovesRigtTwoFieldAndCrossBorder)
 {
	ICoord * coord = new Coord(5, BOARDSIZE - 1); //snake tail [5,14]
	ISnake * snake = new Snake(coord);
	
	snake->changeSnakeHeadCoordinates(snake->getDirection());//right  [5,14] ->sh[5,0] not in container
	snake->setSnakeTail();//didn't call container=1 snakeLength=2
	snake->changeSnakeHeadCoordinates(snake->getDirection());//  fireldToclear-><5,14>,st->[5,0] ->sh[5,1]
	snake->setSnakeTail(); //<5,14> [5, 0]
	snake->changeSnakeHeadCoordinates(snake->getDirection());//deque <5,0>[5,1] ->5,2
	snake->setSnakeTail();
	
	compareSnakeHeadCoord(snake, 5, 2);
	EXPECT_EQ(snake->getCoord_Container().size(), 1);
	compareCoordValues(snake->getFieldToClear(), 5, 0);
	compareCoordValues(snake->getSnakeTail(), 5, 1);
	compareCoordValues(new Coord(snake->getCoord_Container().at(0)), 5, 1);

	delete coord;	delete snake;
}

TEST(TestSnake, SnakeMovesToTheRightUntilHeFindsHimselfInTheSamePositionAndThenMovesUpCrossingTheBoundariesTwice)
{
	ICoord * coord = new Coord(0, BOARDSIZE - 1); //snake tail [0,14]
	ISnake * snake = new Snake(coord);

	for (int i = 0; i <= BOARDSIZE; ++i)
	{
		if (i == BOARDSIZE)
			snake->setDirection('w');
		snake->changeSnakeHeadCoordinates(snake->getDirection()); //right , deque [0,0][1,0]..
		snake->setSnakeTail();
	}
	compareSnakeHeadCoord(snake, (BOARDSIZE-1), (BOARDSIZE-1) );
	EXPECT_EQ(snake->getCoord_Container().size(), 1);
	compareCoordValues(snake->getFieldToClear(), 0, (BOARDSIZE - 2));
	compareCoordValues(snake->getSnakeTail(), 0, (BOARDSIZE - 1));
	compareCoordValues(new Coord(snake->getCoord_Container().at(0)), 0, (BOARDSIZE - 1));
	EXPECT_THROW(snake->getCoord_Container().at(1), std::out_of_range); //only 1 element at zero position
	delete coord;	delete snake;
}

TEST(TestSnake, SnakeMovesDownUntilHeFindsHimselfInTheSamePositionAndThenMovesLeftCrossingTheBoundariesTwice)
{
	ICoord * coord = new Coord(BOARDSIZE - 1, 0); //snake tail [14,0]
	ISnake * snake = new Snake(coord);
	snake->setDirection('s');//down key was pressed

	for (int i = 0; i <= BOARDSIZE; ++i)
	{
		if (i == BOARDSIZE)
			snake->setDirection('a');
		snake->changeSnakeHeadCoordinates(snake->getDirection()); //left , deque [0,0][0,1]...
		snake->setSnakeTail();
	}
	compareSnakeHeadCoord(snake, (BOARDSIZE - 1), (BOARDSIZE - 1)); //[14,0]
	EXPECT_EQ(snake->getCoord_Container().size(), 1);
	compareCoordValues(snake->getFieldToClear(), (BOARDSIZE - 2), 0);
	compareCoordValues(snake->getSnakeTail(), (BOARDSIZE - 1),0);
	compareCoordValues(new Coord(snake->getCoord_Container().at(0)), (BOARDSIZE - 1),0);
	EXPECT_THROW(snake->getCoord_Container().at(1), std::out_of_range); //only 1 element at zero position
	delete coord;	delete snake;
}
//========================================================================================================
//===========================================COORD TEST===================================================

	class TestCoord : public ::testing::Test {
	protected:
			ICoord * Icoord;
			int expected = BOARDSIZE / 2;
	
		void SetUp() override 
		{
			Icoord = new Coord();
		}

		void TearDown() override 
		{
			delete Icoord;
		}
	};

TEST_F(TestCoord, CreateCoordInstanceAndGetCoordinates)	
{
	EXPECT_EQ(Icoord->getCoordX() , expected);	
	ASSERT_EQ(Icoord->getCoordY() , expected);
}

TEST_F(TestCoord, CreateCoordInstanceAndSetCoordinates)
{
	int Xcoord = 4;				int Ycoord = 6;	
	Icoord->setCoordX(Xcoord); 	Icoord->setCoordY(Ycoord);
	compareCoordValues(Icoord, 4, 6);
}

TEST_F(TestCoord, CreateCoordInstanceSetCoordinatesAndPrintThemInConsole)
{
	Icoord = new Coord(5,5);

	compareCoordValues(Icoord, 5, 5);
	std::string concatate = "Coord Xcolumn : 5 Coord Ycolumn : 5\n";
	EXPECT_EQ(Icoord->printCoordinates() , concatate);
}

TEST_F(TestCoord, CreateCoordInstanceAndSetCoordinatesWithMinusValueCatchExceptionThrowMassege)
{
	int Xcoord = -10;	int Ycoord = -10;
	try
	{
		Icoord = new Coord(Xcoord, Ycoord);
	}
	catch (const std::runtime_error& err)
	{
		// check exception
		ASSERT_STREQ("Coord parameter cannot be minus value\n", err.what());
	}
}
TEST_F(TestCoord, CreateCoordInstanceAndSetCoordinatesWithMinusValueCatchExceptionSetMinusToZero)
{
	int Xcoord = -4;	int Ycoord = -6;
	Icoord = new Coord(Xcoord, Ycoord);
	compareCoordValues(Icoord, 0, 0);
}

TEST_F(TestCoord, CreateCoordInstanceAndSetCoordinatesWithValuBiggerThanBoardsizeAndChangItToZero)
{
	int Xcoord = BOARDSIZE+1;	int Ycoord = BOARDSIZE+2;
	Icoord = new Coord(Xcoord, Ycoord);
	compareCoordValues(Icoord, 0, 0);
}
//-------------------------------------------------------------------------------------------------------

TEST(TestMockCoords, SnakeTakeMockCoordInConstructor)
{
	using::testing::Return;
	int returnValue = 12;
	int returnValueTwo =7;
	MockCoord * mCoord = new MockCoord();
	ISnake *  snake = new Snake(mCoord);
	EXPECT_CALL(*mCoord, getCoordX()).Times(1).WillRepeatedly(Return(returnValue));
	EXPECT_CALL(*mCoord, getCoordY()).Times(1).WillRepeatedly(Return(returnValueTwo));
	
	ASSERT_THAT(snake->getSnakeHead()->getCoordX(), returnValue);
	ASSERT_THAT(snake->getSnakeHead()->getCoordY(), returnValueTwo);
	delete mCoord;
	delete snake;
}

//========================================================================================================
//===========================================BOARD TEST===================================================

TEST(TestBoard, TestBoardCreateAndSetvectorSizeAndFillItFields) {
	IBoard * Iboard = new Board(10);
	ASSERT_THAT(Iboard->getvectorSize(), 10);

	Iboard->clear();
	for (auto line : Iboard->getVector())
		for (auto segment : line)
		{
			ASSERT_THAT(segment, '.');
		}
	delete Iboard;
}

TEST(TestBoard, CreateAndSetvectorSizetoZeroAndMinusCatchLogicErrorAndChangValueToDefault)
{
	IBoard * Iboard = new Board(-1);
	ASSERT_THAT(Iboard->getvectorSize(), BOARDSIZE);
	delete Iboard;
	IBoard * Iboard2 = new Board(0);
	ASSERT_THAT(Iboard2->getvectorSize(), BOARDSIZE);
	delete Iboard2;
}
	TEST(TestBoard, TestBoardFillItFields)
	{
		IBoard * Iboard = new Board(3);
		Iboard->clear();
	
		std::vector <std::vector<char> > 
			expected = { {'.','.','.'} ,{'.','.','.'}, {'.','.','.'} }; // "{...}{...}{...}";
		std::vector <std::vector<char> > 
			expectedFail = { {'.','.','x'} ,{'.','.','.'}, {'.','.','.'} }; // "{..x}{...}{...}";

		ASSERT_EQ(Iboard->clear(), expected);
		ASSERT_NE(Iboard->clear(), expectedFail);
		delete Iboard;
	}

TEST(TestBoard, TestBoardScore)
{
	IBoard * Iboard = new Board(3);
	ASSERT_EQ(Iboard->getScore(), 0);
	Iboard->setScore(); Iboard->setScore();
	ASSERT_EQ(Iboard->setScore(), 2);
	delete Iboard;
}
TEST(TestBoard, TestDrawSnakeOnBoard)
{
	int expected = BOARDSIZE / 2;
	IBoard * Iboard = new Board(BOARDSIZE);
	ISnake * Isnake = new Snake();
	Iboard->clear();
	std::vector <std::vector<char> > expectedEmpty = Iboard->getVector();

	Iboard->drawSnakeOnBoard(Isnake->getSnakeHead()->getCoordX(), Isnake->getSnakeHead()->getCoordY());
	std::vector <std::vector<char> > expectedSnake = Iboard->getVector();

	ASSERT_NE(expectedEmpty, expectedSnake);
	ASSERT_EQ(Isnake->getSnakeHead()->getCoordX(), expected);
	ASSERT_EQ(Isnake->getSnakeHead()->getCoordY(), expected);
	ASSERT_EQ(Iboard->getvectorCoord(expected , expected), 'o');
	delete Iboard;
	delete Isnake;
}

TEST(TestMockSnake, createMockSnakeAndPutCoordinatesOfSnakeHeadOnTheBoard)
{
	using::testing::Return;
	ICoord * coord = new Coord(BOARDSIZE-2, BOARDSIZE - 2);
	MockSnake * mSnake = new MockSnake();
	
	EXPECT_CALL(*mSnake, getSnakeHead()).WillRepeatedly(Return(coord));
	IBoard * board = new Board(mSnake , BOARDSIZE);

	ASSERT_EQ(board->getvectorSize() , BOARDSIZE);
	compareSnakeHeadCoord(mSnake, (BOARDSIZE - 2), (BOARDSIZE - 2));
	ASSERT_EQ(board->getvectorCoord((mSnake->getSnakeHead())->getCoordX() , 
									(mSnake->getSnakeHead())->getCoordY()), 
									'o');
	delete board;	delete coord;	delete mSnake;
}

TEST(TestBoard, PrintSnakeOnBoardUsingCoordMock)
{
	using::testing::Return;
	MockCoord * mCoord = new MockCoord();
	ISnake * snake = new Snake(mCoord);

	EXPECT_CALL(*mCoord , getCoordX()).WillRepeatedly(Return (5)); 
	EXPECT_CALL(*mCoord, getCoordY()).WillRepeatedly(Return(5));

	IBoard * board = new Board(snake, BOARDSIZE);

	for (int i = 0; i < BOARDSIZE; i++) 
	{
		for (int j = 0; j < BOARDSIZE; j++)
		{
			if (i==5 && j==5)
				EXPECT_EQ(board->getvectorCoord(i, j), 'o')
				<<"Value of X: "<< i <<"Value of Y: "<< j << "is "<< board->getvectorCoord(i, j);
			else
				EXPECT_EQ(board->getvectorCoord(i, j), '.');
		}
	}
	delete board, mCoord, snake;
}

TEST(TestBoard, SnakeMoveOnBordTwoFieldRightAndWasPrintOnBoard)
{
	using::testing::Return;
	ICoord * expCoord = new Coord(0,7);
	MockCoord * mCoord = new MockCoord();
	ISnake * snake = new Snake(mCoord);

	EXPECT_CALL(*mCoord, getCoordX()).WillRepeatedly(Return(0));
	EXPECT_CALL(*mCoord, getCoordY()).Times(5).WillRepeatedly(Return(5));

	IBoard * board = new Board(snake, BOARDSIZE);
	
	EXPECT_EQ(board->getvectorCoord(0, 5), 'o');
	EXPECT_CALL(*mCoord, setCoordY(6)).Times(1);
	snake->changeSnakeHeadCoordinates(snake->getDirection()); 
	EXPECT_EQ(snake->getCoord_Container().size(), 1);

	EXPECT_CALL(*mCoord, getCoordY()).Times(6).WillRepeatedly(Return(6));
	board->drawSnakeOnBoardbyIcoord();
	EXPECT_EQ(board->getvectorCoord(0, 6), 'o');

	EXPECT_CALL(*mCoord, setCoordY(7)).Times(1);
	snake->changeSnakeHeadCoordinates(snake->getDirection()); 
	EXPECT_EQ(snake->getCoord_Container().size(), 2);

	EXPECT_CALL(*mCoord, getCoordY()).Times(7).WillRepeatedly(Return(7));
	board->drawSnakeOnBoardbyIcoord();
	EXPECT_EQ(board->getvectorCoord(0, 7), 'o');

	delete board, mCoord, snake;
}

TEST(TestBoard, SnakeMoveOnBordTwoFieldRightCrossBoardEndAndWasPrintOnBoard)
{
	using::testing::Return;
	ICoord * expCoord = new Coord(0, (BOARDSIZE - 2));
	MockCoord * mCoord = new MockCoord();
	ISnake * snake = new Snake(mCoord);

	EXPECT_CALL(*mCoord, getCoordX()).WillRepeatedly(Return(0));
	EXPECT_CALL(*mCoord, getCoordY()).Times(5).WillRepeatedly(Return((BOARDSIZE - 2)));

	IBoard * board = new Board(snake, BOARDSIZE);
	EXPECT_CALL(*mCoord, setCoordY((BOARDSIZE - 1))).Times(1);
	EXPECT_CALL(*mCoord, getCoordY()).Times(5).WillRepeatedly(Return((BOARDSIZE - 1)));
	EXPECT_CALL(*mCoord, setCoordY((BOARDSIZE ))).Times(1);

	snake->changeSnakeHeadCoordinates(snake->getDirection()); //5 time call
	board->drawSnakeOnBoardbyIcoord();
	
	EXPECT_CALL(*mCoord, getCoordY()).Times(10).WillRepeatedly(Return(0));
	EXPECT_CALL(*mCoord, setCoordY(1)).Times(2);
	
	snake->changeSnakeHeadCoordinates(snake->getDirection()); //5 time call
	board->drawSnakeOnBoardbyIcoord();

	EXPECT_EQ(snake->getCoord_Container().size(), 2);
	EXPECT_EQ(board->getvectorCoord(0, (BOARDSIZE - 2)), 'o');
	EXPECT_EQ(board->getvectorCoord(0, (BOARDSIZE - 1)), 'o');
	EXPECT_EQ(board->getvectorCoord(0, (BOARDSIZE - BOARDSIZE )), 'o');
	for (int i = 0; i < BOARDSIZE; i++)
	{
		for (int j = 0; j < BOARDSIZE; j++)
		{
			if ((i == 0 && j == (BOARDSIZE - 2)) || (i == 0 && j == (BOARDSIZE - 1)) || (i == 0 && j == 0))
				EXPECT_EQ(board->getvectorCoord(i, j), 'o')
				<< "Value of X: " << i << "Value of Y: " << j << "is " << board->getvectorCoord(i, j);
			else
				EXPECT_EQ(board->getvectorCoord(i, j), '.');
		}
	}
	delete board, mCoord, snake;
}

TEST(TestBoard, SnakeMoveOnBordTwoFieldEeatsAnAppleAndGrows)
{
	int size = BOARDSIZE / 2; //7
	ICoord * coord = new Coord(size, size);
	ISnake * snake = new Snake(coord);
	IApple * apple = new Apple(size, (size+3) );
	IBoard * board = new Board(snake, apple, BOARDSIZE);
	
	compareCoordValues(snake->getSnakeHead() , size, size);
	compareCoordValues(apple->getAppleCoords(), size, size+3);
	EXPECT_EQ(snake->getSnakeLength(), 2);

	for (int i = 0; i < 3; ++i) //in third move snake eat apple
	{
		snake->changeSnakeHeadCoordinates(snake->getDirection());
		board->SnakeEatsApple();
		if (i==2)
			EXPECT_TRUE( board->eatApple);
		else
			EXPECT_FALSE(board->eatApple);
		snake->setSnakeTail();
	}
	EXPECT_EQ(snake->getSnakeLength(), 3);
	
	delete board, coord, snake, apple;
}

TEST(TestBoard, SnakeMoveOnBordAndHitItself)
{
	int size = BOARDSIZE / 2; //7
	ISnake * snake = new Snake(new Coord(1,0));
	snake->putSnakeHeadCoorinatesToDeque(Coord(0, 0));	//Dodaje nowy element na końcu kontenera » standard C++ ♦ deque. (metoda)
	snake->putSnakeHeadCoorinatesToDeque(Coord(0, 1));
	snake->putSnakeHeadCoorinatesToDeque(Coord(1, 1));

	compareCoordValues(new Coord(snake->getCoord_Container().at(0)) , 0,0);
	compareCoordValues(new Coord(snake->getCoord_Container().at(1)), 0, 1);
	compareCoordValues(new Coord(snake->getCoord_Container().at(2)), 1, 1);
	/*	#####
		#O O#
		#O>O# -> snake moves right hit his body
		#####
	*/
	ASSERT_FALSE(snake->snakeHitItself());
	snake->changeSnakeHeadCoordinates(snake->getDirection());
	ASSERT_TRUE (snake->snakeHitItself());
	delete  snake;

 }

TEST(TestBoard, SnakeMoveOnBordEeatsTwoApplesGrowsAndHitHisBody)
{
	int size = BOARDSIZE / 2; //7
	ISnake * snake = new Snake(new Coord(1, 0));
	IApple * apple = new Apple(1, 1);
	IApple * apple2 = new Apple(1, 2);
	IBoard * board = new Board(snake, apple, BOARDSIZE);

	for (int a = 0; a < 4; a++)
	{
		snake->putSnakeHeadCoorinatesToDeque(Coord(0, a)); //snake Tail
		compareCoordValues(new Coord(snake->getCoord_Container().at(a)), 0, a);
	}
	snake->putSnakeHeadCoorinatesToDeque(Coord(1, 3));	//Dodaje nowy element na końcu kontenera » standard C++ ♦ deque. (metoda)
	compareCoordValues(new Coord(snake->getCoord_Container().at(4)), 1, 3);
	/*	#########
		#O O O O#
		#O>X>X O# -> snake moves right hit his body
		#########
	*/

	for (int b = 0; b < 2; b++)
	{
		ASSERT_FALSE(snake->snakeHitItself());
		snake->changeSnakeHeadCoordinates(snake->getDirection());
		board->SnakeEatsApple();
		if (board->eatApple) //change apple coord to next field
		{
			apple->getAppleCoords()->setCoordX(1);
			apple->getAppleCoords()->setCoordY(2);
		}
		ASSERT_TRUE(board->eatApple);
		ASSERT_FALSE(snake->snakeHitItself());
	}
	snake->changeSnakeHeadCoordinates(snake->getDirection());
	ASSERT_TRUE(snake->snakeHitItself());
	delete board, apple, snake, apple2;

}

TEST(TestBoard, SnakeMoveOnWholeBoardCrossBordersAndEatsApples)
{
	int size = BOARDSIZE / 2; //7
	int numberOfeatedApples = 0;
	ISnake * snake = new Snake(new Coord(BOARDSIZE/2, size- size));
	IApple * apple = new Apple(new Coord());
	IBoard * board = new Board(snake, apple, BOARDSIZE);

	int counter = 0;
	int numberOfEatApple = 0;

	for (int x = 0; x < (BOARDSIZE + 1)*(BOARDSIZE + 1); x++)
	{
		snake->changeSnakeHeadCoordinates(snake->getDirection()); //add head to cont and chceck borders
		if (counter == BOARDSIZE + 1) {
			snake->setDirection('s');
			counter = 0;
		}
		else
			snake->setDirection('d');
		board->drawSnakeOnBoardbyIcoord();
		board->SnakeEatsApple(); //put random apple on '.' field	
		if (board->eatApple) numberOfEatApple++;
		board->drawApplOnBoardbyIcoord();
		counter++;
	}
	EXPECT_EQ( 2, snake->getSnakeLength()- numberOfEatApple);
	compareCoordValues(snake->getSnakeHead() , size, 1); //snake starts and end in the same point
	delete board, snake, apple;
}

TEST(TestBoard, SnakeMoveOnWholeBoardCrossBordersAndEatsApplesUntilHislengthIs20)
{
	int size = BOARDSIZE / 2; //7
	int numberOfeatedApples = 0;
	ISnake * snake = new Snake(new Coord(BOARDSIZE / 2, size - size));
	IApple * apple = new Apple(new Coord());
	IBoard * board = new Board(snake, apple, BOARDSIZE);

	int counter = 0;
	int numberOfEatApple = 0;

	for (;  ; )
	{
		snake->changeSnakeHeadCoordinates(snake->getDirection()); //add head to cont and chceck borders
		if (counter == BOARDSIZE + 1) {
			snake->setDirection('s');
			counter = 0;
		}
		else
			snake->setDirection('d');
		board->drawSnakeOnBoardbyIcoord();
		board->SnakeEatsApple(); //put random apple on '.' field	
		if (board->eatApple) numberOfEatApple++;
		board->drawApplOnBoardbyIcoord();
		counter++;

		if (snake->getSnakeLength() == 20)
		{
			break;
		}
	}
	
	EXPECT_EQ(snake->getSnakeLength(), 20);
	delete board, snake, apple;
}

TEST(TestBoard, SnakeMoveOnWholeBoardCrossBordersAndEatsMockApplesUntilThereIsNoSpaceAngGameEnds)
{
	using::testing::Return;
	int size = BOARDSIZE / 2; //7
	ISnake * snake = new Snake(new Coord(BOARDSIZE / 2, size - size));
	
	MockApple * mApple = new MockApple();
	EXPECT_CALL(*mApple , getAppleCoords()).WillRepeatedly(Return(new Coord(BOARDSIZE / 2, size+1 - size)));
	//EXPECT_CALL(*mApple , getAppleCoordX()).Times(6).WillRepeatedly(Return(7));
	//EXPECT_CALL(*mApple, getAppleCoordY()).Times(6).WillRepeatedly(Return(1));

	EXPECT_CALL(*mApple, getAppleCoordY()).WillRepeatedly(Return(11));
	//EXPECT_CALL(*mApple , putRandomAppleOnboard()).Times(2).WillRepeatedly(Return());

	IBoard * board = new Board(snake, mApple, BOARDSIZE);

	compareCoordValues(snake->getSnakeHead(), 7, 0);
	snake->changeSnakeHeadCoordinates(snake->getDirection()); //add head to cont and chceck borders
	board->drawSnakeOnBoardbyIcoord();
	board->SnakeEatsApple(); //put random apple on '.' field	
	
	EXPECT_EQ(mApple->getAppleCoords()->getCoordY(), snake->getSnakeHead()->getCoordY());
	//EXPECT_TRUE(board->eatApple);

	//board->drawApplOnBoardbyIcoord();
	//board->printVector();
	//EXPECT_TRUE(board->eatApple);

	EXPECT_EQ(mApple->getAppleCoords()->getCoordX() , 7);
	EXPECT_EQ(mApple->getAppleCoords()->getCoordY(), 1);

	delete board, snake, mApple;
}
//=============================================================================================
//Helping Methods:
void compareSnakeHeadCoord(ISnake *  snake, int x, int y)
{
	EXPECT_EQ((snake->getSnakeHead())->getCoordX(), x);
	EXPECT_EQ((snake->getSnakeHead())->getCoordY(), y);
}

void compareCoordValues(ICoord *  coord, int x, int y)
{
	EXPECT_EQ(coord->getCoordX(), x);
	EXPECT_EQ(coord->getCoordY(), y);
}
bool compareCoordsAreNotEq(ICoord *  P1, ICoord *  P2)
{
	if ((P1->getCoordX() == P2->getCoordX()) 
		&& (P1->getCoordY() == P2->getCoordY()))
		return false;
	else
		return true;
}

//========================================================================================================
//===========================================APPLE TEST===================================================

TEST(TestApple, CreateAppleInstanceWithDefaultConstructor)
{
	IApple * apple = new Apple(); //BOARDSIZE/2-1

	EXPECT_EQ(apple->getAppleCoordX() , BOARDSIZE / 2 - 1); 
	EXPECT_EQ(apple->getAppleCoordY() , BOARDSIZE / 2 - 1);

	delete apple;
}

TEST(TestApple, CreateAppleInstancesWithDifrentValues)
{
	IApple * apple = new Apple(3 ,5);
	IApple * apple2 = new Apple(3, 123);

	int randomAplleCoordX = apple->getAppleCoordX();
	int randomAplleCoordY = apple->getAppleCoordY();

	compareCoordValues(apple->getAppleCoords() , 3 ,5);
	compareCoordValues(apple2->getAppleCoords(), 3, 0);
	
	apple->getAppleCoords()->setCoordX(1234);
	apple->getAppleCoords()->setCoordY(-1234);
	compareCoordValues(apple->getAppleCoords(), 0, BOARDSIZE-1);

	delete apple, apple2;
}

TEST(TestApple, PutAndPrintAppleAndSnakeOnBoardDuringCreation)
{
	ISnake * snake = new Snake(new Coord());
	IApple * apple = new Apple(new Coord());
	IBoard * board = new Board(snake, apple, BOARDSIZE);

	compareCoordValues(snake->getSnakeHead(), BOARDSIZE/2 , BOARDSIZE/2);
	ASSERT_TRUE(compareCoordsAreNotEq(snake->getSnakeHead(), apple->getAppleCoords()));

	delete apple, snake, board;
}

TEST(TestApple, PutAndPrintAppleOnBoardOnTheSameLocationAsSnakeHasDuringCreation)
{
	IApple * apple = new Apple(5 , 7);
	ISnake * snake = new Snake(5 , 7);
	ASSERT_FALSE(compareCoordsAreNotEq(snake->getSnakeHead(), apple->getAppleCoords()));
	IBoard * board = new Board(snake, apple , BOARDSIZE);

	compareCoordValues(snake->getSnakeHead(), 5, 7);
	ASSERT_TRUE(compareCoordsAreNotEq(snake->getSnakeHead() , apple->getAppleCoords()) );

	delete apple, snake, board;
}

TEST(TestApple, PutAndPrintAppleOnBoardwhenOnlyOneFieldIsEmptyRestIsSnakeBody)
{
	IApple * apple = new Apple(new Coord(0,1));
	ISnake * snake = new Snake(new Coord(0,0));
	IBoard * board = new Board(snake, apple, BOARDSIZE);

	//set every field on board by snake body except field 0,0 witch is empty
	for (int x = 0; x < BOARDSIZE; x++)
	{
		for (int y = 0; y < BOARDSIZE; y++)
		{
			if ( (x == 0) && (y == 0))
				board->setvectorCoord(0, 0, '.');
			else
				board->setvectorCoord(x, y, 'o');
		}
	}

	ASSERT_EQ(board->getvectorCoord(0,0) , '.');

	board->drawApplOnBoardbyIcoord(); //drow random apple on empty field
	ASSERT_EQ(board->getvectorCoord(0, 0), 'x');

	delete apple, snake, board;
}

TEST(TestApple, EveryTimeAppleIsPrintedOnRandomEmptyField)
{
	IApple * apple = new Apple(new Coord(0, 1));
	ISnake * snake = new Snake(new Coord(0, 0));
	IBoard * board = new Board(snake, apple, BOARDSIZE);

	//set every field on board by snake body except field 0,0 witch is empty
	for (int x = 0; x < BOARDSIZE; x++)
	{
		for (int y = 0; y < BOARDSIZE; y++)
			board->setvectorCoord(x, y, 'o');
	}
	
	for (int row = 0; row < 100; row++)
	{
		int rnd = rand() % (BOARDSIZE*BOARDSIZE);
		int cx = rnd % BOARDSIZE;
		int cy = rnd / BOARDSIZE;
		board->setvectorCoord(cx, cy, '.');
		EXPECT_EQ(board->getvectorCoord(cx, cy), '.');

		board->drawApplOnBoardbyIcoord(); //drow random apple on empty field
		EXPECT_EQ(board->getvectorCoord(cx, cy), 'x') << apple->getAppleCoords()->printCoordinates() << " cx " << cx << " cy " << cy;
		board->setvectorCoord(cx, cy, 'o');
	}
	delete apple, snake, board;

}

TEST(TestApple, NospaceForApple)
{
	IApple * apple = new Apple(new Coord());
	ISnake * snake = new Snake(new Coord());
	IBoard * board = new Board(snake, apple, BOARDSIZE);

	for (int x = 0; x < BOARDSIZE; x++)
	{
		for (int y = 0; y < BOARDSIZE; y++)
			board->setvectorCoord(x, y, 'o');
	}
	apple->getAppleCoords()->setCoordX(1);	apple->getAppleCoords()->setCoordY(1);

	snake->getSnakeHead()->setCoordX(1);	snake->getSnakeHead()->setCoordY(1);
	board->SnakeEatsApple();
	EXPECT_TRUE(board->SnakeEatAllApple);

	delete apple, snake, board;
}