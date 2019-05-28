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

class TestSnake : public ::testing::Test {
protected:
	ICoord * coord;
	ISnake * snake;
	int expected = BOARDSIZE / 2;

	void SetUp() override
	{
		snake = new Snake();
		coord = new Coord();
	}

	void TearDown() override
	{
		delete snake;
		delete coord;
	}
};


TEST_F(TestSnake , CreateSnakeInstanceAndSetSnakeHeadCoordinatedInTheCenterOfTheBoard)
{
	compareCoordValues(snake->getSnakeHead(), expected, expected);
}

TEST_F(TestSnake, CreateSnakeInstanceAndSetSnakeHeadCoordinatedByCoordObjectValues)
{
	coord = new Coord((BOARDSIZE - 2), expected);
	snake = new Snake(coord);

	EXPECT_EQ(snake->getSnakeHead(), coord);
	EXPECT_GE(snake->getSnakeHead()->getCoordX(), (BOARDSIZE - 2));
	EXPECT_LE(snake->getSnakeHead()->getCoordY(), expected);
}

TEST_F(TestSnake, TestDefaultSnakeConstructorWithTwoIntParameters)
{
	snake = new Snake(5, 5);
	compareCoordValues(snake->getSnakeHead(), 5,5);
}

TEST_F(TestSnake, setSnakeMovementDirectionBasedOnThePressedKey)
{
	coord = new Coord();
	snake = new Snake(coord);
	char pressedKey_W = 'w';	//press w to set the direction up
	char pressedKey_S = 's';	//press s to set the direction down
	char pressedKey_D = 'd';	//press d to set the direction right
	char pressedKey_A = 'a';	//press a to set the direction left

	EXPECT_EQ(snake->getDirection(), 'r');  //snake by default always starts going right

	EXPECT_EQ(snake->setDirection(pressedKey_D), 'r');
	EXPECT_EQ(snake->getDirection(), 'r');

	EXPECT_EQ(snake->setDirection(pressedKey_S), 'd');
	EXPECT_EQ(snake->getDirection(), 'd');

	EXPECT_EQ(snake->setDirection(pressedKey_A), 'l');
	EXPECT_EQ(snake->getDirection(), 'l');

	EXPECT_EQ(snake->setDirection(pressedKey_W), 'u');
	EXPECT_EQ(snake->getDirection(), 'u');
}

TEST_F(TestSnake, setMovementDirectionToRightWhenPreesedKeyIsLeftAndMovementDirectionIsRight)
{
	snake = new Snake(coord);
	EXPECT_EQ(snake->getDirection(), 'r');
	char leftKey = 'a';
	EXPECT_EQ(snake->setDirection(leftKey), 'r');
	EXPECT_EQ(snake->getDirection(), 'r');
	EXPECT_NE(snake->getDirection(), 'l');
}
TEST_F(TestSnake, setMovementDirectionToLeftWhenPreesedKeyIsRightAndMovementDirectionIsLeft)
{
	snake = new Snake(coord);
	char leftKey = 'a';
	EXPECT_EQ(snake->setDirection('w'), 'u'); //first set direction to up
	EXPECT_EQ(snake->setDirection(leftKey), 'l'); //then set direction to left
	EXPECT_EQ(snake->setDirection('r'), 'l');
	EXPECT_NE(snake->getDirection(), 'r');
	EXPECT_EQ(snake->getDirection(), 'l');
}
TEST_F(TestSnake, setMovementDirectionToDefaultWhenOtherKeyWaspressedthenASDW)
{
	snake = new Snake(coord);
	char leftKey = 'a';
	EXPECT_EQ(snake->setDirection('q'), 'r'); 
	EXPECT_EQ(snake->setDirection('t'), 'r');
	EXPECT_EQ(snake->setDirection('='), 'r');
	EXPECT_EQ(snake->getDirection(), 'r');
}

TEST_F(TestSnake, setMovementDirectionToUpWhenPreesedKeyIsDownAndMovementDirectionIsUp)
{
	snake = new Snake(coord);
	char upKey = 'w';
	EXPECT_EQ(snake->setDirection(upKey), 'u');
	EXPECT_EQ(snake->setDirection('s'), 'u');
	EXPECT_EQ(snake->getDirection(), 'u');
}
TEST_F(TestSnake, setMovementDirectionToDownWhenPreesedKeyIsUpAndMovementDirectionIsDown)
{
	snake = new Snake(coord);
	EXPECT_EQ(snake->setDirection('s'), 'd');

	char downKey = 's';
	EXPECT_EQ(snake->setDirection(downKey), 'd');
	EXPECT_EQ(snake->setDirection('u'), 'd');
	EXPECT_EQ(snake->getDirection(), 'd');
}

TEST_F(TestSnake, ExpectToThrowOutOfRangeException)
{
	coord = new Coord(2, 3);
	snake = new Snake(coord);

	EXPECT_THROW(snake->getCoord_Container().at(0), std::out_of_range);
    	snake->putSnakeHeadCoorinatesToDeque(Coord(coord));
	EXPECT_EQ(snake->getCoord_Container().size(), 1);
	EXPECT_THROW(snake->getCoord_Container().at(1), std::out_of_range);
}

	TEST_F(TestSnake, snkakeContainerTests)
	{
		using::testing::ElementsAreArray;
		coord = new Coord(2, 3);
		snake = new Snake(coord);
		MockSnake * Msnake = new MockSnake();

		std::deque<Coord> Coord_Container2 = { coord };
		EXPECT_CALL(*Msnake, getCoord_Container()).WillOnce(::testing::Return(Coord_Container2));

		EXPECT_THAT(snake->getCoord_Container(), ::testing::IsEmpty());
			snake->putSnakeHeadCoorinatesToDeque(Coord (coord->getCoordX(), coord->getCoordY()));			
		EXPECT_THAT(snake->getCoord_Container(), ::testing::SizeIs(1));
		//EXPECT_THAT(snake->getCoord_Container(), ::testing::UnorderedElementsAre(::testing::Pointee( coord)));
	}

TEST_F(TestSnake, putHeadSnakeCoordinatesToDequeContainer)
{
	coord = new Coord(2,3);
    snake = new Snake(coord);
	Coord x(coord->getCoordX() , coord->getCoordY());
	snake->putSnakeHeadCoorinatesToDeque(x);
	
	EXPECT_EQ(snake->getCoord_Container().size(), 1);
		compareCoordValues(new Coord (snake->getCoord_Container().at(0)), 2,3);
	EXPECT_EQ(snake->getSnakeHead(), coord); //Compare addresses
}

TEST_F(TestSnake, putHeadSnakeCoordinatesToDequeContainerMockingSnakeHeadCoord)
{
	using::testing::Return; 	using::testing::AnyNumber;
	MockCoord * mCoord = new MockCoord();
	snake = new Snake(mCoord);

	EXPECT_CALL(*mCoord, getCoordX()).WillRepeatedly(Return(expected+2));
	EXPECT_CALL(*mCoord, getCoordY()).WillRepeatedly(Return(expected));

	snake->putSnakeHeadCoorinatesToDeque( 
		Coord(snake->getSnakeHead()->getCoordX() , snake->getSnakeHead()->getCoordY()));
	
	EXPECT_GE(snake->getCoord_Container().size(), 0);
	EXPECT_EQ(snake->getCoord_Container().at(0).getCoordX(), (expected+2));
	EXPECT_EQ(snake->getCoord_Container().at(0).getCoordY(), (expected));
	delete mCoord;
}

TEST_F(TestSnake, MoveSnakeToRightOnBoard)
{
	snake = new Snake(coord);
	char direction = 'r';
	snake->changeSnakeHeadCoordinates(direction);
	compareSnakeHeadCoord(snake, expected, expected+1);
}

TEST_F(TestSnake, MoveSnakeToRightOnBoardAndPutSnakeHeadCoordinatesToDeque)
{
	snake = new Snake(coord);
	char direction = 'r';
	snake->changeSnakeHeadCoordinates(direction);
	
	compareSnakeHeadCoord(snake, expected, expected + 1);	
	compareCoordValues(new Coord(snake->getCoord_Container().at(0)), expected, expected);
	EXPECT_EQ(snake->getCoord_Container().size(), 1);
	EXPECT_THROW(snake->getCoord_Container().at(1) ,std::out_of_range ); //throw out_of_range exception
}

	TEST_F(TestSnake, SnakeMovesRigtOneFildAndThenPlayerPresUpKeySnakeMovesUpOneField)
	{
		snake = new Snake(coord);
		char pressedKey = 'w';
		snake->changeSnakeHeadCoordinates(snake->getDirection()); //right
		snake->setDirection(pressedKey); //key w is up
		snake->changeSnakeHeadCoordinates(snake->getDirection()); //up
		compareSnakeHeadCoord(snake, expected - 1, expected + 1);
	}

TEST_F(TestSnake, GetSnakeSeadCoordXFourTimes)
{
	using::testing::Return;
	MockCoord * mCoord = new MockCoord();
		EXPECT_CALL(*mCoord, getCoordY()).Times(4)
		.WillOnce(Return(1))
		.WillOnce(Return(2))
		.WillOnce(Return(3))
		.WillRepeatedly(Return(0));

	snake = new Snake(mCoord);

	EXPECT_EQ(snake->getSnakeHead()->getCoordY(), 1);
	EXPECT_EQ(snake->getSnakeHead()->getCoordY(), 2);
	EXPECT_EQ(snake->getSnakeHead()->getCoordY(), 3);
	EXPECT_EQ(snake->getSnakeHead()->getCoordY(), 0);
}

TEST_F(TestSnake, SnakeMovedRightReachedTheBoardEndheadCoordinatesAreSetFrom15to0andThenfrom0to1)
{
	using::testing::Return;
	using::testing::_;
	MockCoord * mCoord = new MockCoord();
	snake = new Snake(mCoord);


	EXPECT_CALL(*mCoord, setCoordY(15)).Times(1).WillOnce(Return(0));
	EXPECT_CALL(*mCoord, setCoordY(1)).Times(1).WillOnce(Return(1));

	EXPECT_CALL(*mCoord, getCoordY()).Times(4)
		.WillOnce(Return(14)).WillOnce(Return(14))
		.WillOnce(Return(0)).WillOnce(Return(0));

	EXPECT_CALL(*mCoord, getCoordX())
		.WillRepeatedly(Return(0));

	compareCoordValues(snake->changeSnakeHeadCoordinates('r'), 0,14); //call twice
	compareCoordValues(snake->changeSnakeHeadCoordinates('r'), 0, 0);
}

TEST_F(TestSnake, SnakeReachedTheBoardEnd)
{
	using::testing::Return;
	using::testing::_;
	MockCoord * mCoord = new MockCoord();
	snake = new Snake(mCoord);

	EXPECT_CALL(*mCoord, getCoordX()).Times(1).WillRepeatedly(Return(0));
	EXPECT_CALL(*mCoord, getCoordY()).WillRepeatedly(Return(5));
	
	compareSnakeHeadCoord(snake, 0, 5);
	delete mCoord;
}


	using::testing::Return;								//#1	

	TEST_F(TestSnake, SnakeTakeMockCoordInConstructor)
	{
		int returnValue = 12, returnValueTwo = 7;

		MockCoord * mCoord = new MockCoord();			//#2

		EXPECT_CALL(*mCoord, getCoordX()).Times(1).		//#3
			WillRepeatedly(Return(returnValue));
		EXPECT_CALL(*mCoord, getCoordY()).Times(1).
			WillRepeatedly(Return(returnValueTwo));

		snake = new Snake(mCoord);						//#4

		EXPECT_THAT(snake->getSnakeHead()->getCoordX(), returnValue);		//#5
		EXPECT_THAT(snake->getSnakeHead()->getCoordY(), returnValueTwo);
		delete mCoord;
	}																		//#6

TEST_F(TestSnake, SnakeReachedTheBoardEndTwice)
{
	coord = new Coord((BOARDSIZE - 1), (BOARDSIZE - 1));
	snake = new Snake(coord);

	snake->changeSnakeHeadCoordinates(snake->getDirection()); //right
	snake->setDirection('s'); //key w is up
	
	compareSnakeHeadCoord(snake, (BOARDSIZE - 1), 0);
	snake->changeSnakeHeadCoordinates(snake->getDirection()); //up
	
	compareSnakeHeadCoord(snake, 0 ,0);
	EXPECT_EQ(snake->getCoord_Container().size() , 2);
}

TEST_F(TestSnake, SnakeMovesRigtOneFildSetSnakeTail)
{
	coord = new Coord(5, 5); //snake tail [5,5]
	snake = new Snake(coord);
	for (int i = 0; i < 2; ++i)
	{
		snake->changeSnakeHeadCoordinates(snake->getDirection()); //right , deque [5,6][5,7]
		snake->setSnakeTail();
	}
	compareSnakeHeadCoord(snake, 5, 7);
	EXPECT_EQ(snake->getCoord_Container().size(), 1);
	compareCoordValues(snake->getSnakeTail(), 5, 6);
	compareCoordValues(new Coord (snake->getCoord_Container().at(0)) , 5, 6);
}

TEST_F(TestSnake, SnakeMovesRigtTwoFieldAndCrossBorder)
 {
	coord = new Coord(5, BOARDSIZE - 1); //snake tail [5,14]
	snake = new Snake(coord);
	
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
}

TEST_F(TestSnake, SnakeMovesToTheRightUntilHeFindsHimselfInTheSamePositionAndThenMovesUpCrossingTheBoundariesTwice)
{
	coord = new Coord(0, BOARDSIZE - 1); //snake tail [0,14]
	snake = new Snake(coord);

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
}

TEST_F(TestSnake, SnakeMovesDownUntilHeFindsHimselfInTheSamePositionAndThenMovesLeftCrossingTheBoundariesTwice)
{
	coord = new Coord(BOARDSIZE - 1, 0); //snake tail [14,0]
	snake = new Snake(coord);
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
		EXPECT_STREQ("Coord parameter cannot be minus value\n", err.what());
	}
}
TEST_F(TestCoord, CreateCoordInstanceAndSetCoordinatesWithMinusValueCatchExceptionSetMinusToBoardSize)
{
	int Xcoord = -4;	int Ycoord = -6;
	Icoord = new Coord(Xcoord, Ycoord);
	compareCoordValues(Icoord, BOARDSIZE-1, BOARDSIZE - 1);
}

TEST_F(TestCoord, CreateCoordInstanceAndSetCoordinatesWithValuBiggerThanBoardsizeAndChangItToZero)
{
	int Xcoord = BOARDSIZE+1;	int Ycoord = BOARDSIZE+2;
	Icoord = new Coord(Xcoord, Ycoord);
	compareCoordValues(Icoord, 0, 0);
}

TEST_F(TestCoord, MockingSnakeMovesToRightAndLeftWhenSnakeCroosBoardSize)
{
	using::testing::Return;
	using::testing::_;

	MockSnake * mSnake = new MockSnake();
	ICoord * snakeHead = new Coord(BOARDSIZE, 0);
	ICoord * snakeHead1 = new Coord(0, -1);

	EXPECT_CALL(*mSnake, changeSnakeHeadCoordinates(_)).Times(2)
		.WillOnce(Return(snakeHead))
		.WillOnce(Return(snakeHead1));

	compareCoordValues(mSnake->changeSnakeHeadCoordinates('r'), 0, 0);
	compareCoordValues(mSnake->changeSnakeHeadCoordinates('l'), 0, BOARDSIZE - 1);
	
	delete snakeHead, snakeHead1;
}

TEST_F(TestCoord, MockingSnakeMovesToUpAndDownWhenSnakeCroosBoardSize)
{
	using::testing::Return;
	ICoord * snakeHead = new Coord(-1 , 0);
	ICoord * snakeHead1 = new Coord(BOARDSIZE+1 , 0);
	MockSnake * mSnake = new MockSnake();

	EXPECT_CALL(*mSnake, getDirection()).WillOnce(Return('r'));
	EXPECT_CALL(*mSnake, changeSnakeHeadCoordinates(mSnake->getDirection())).Times(1).WillRepeatedly(Return(Icoord));

	EXPECT_CALL(*mSnake, getDirection()).WillOnce(Return('l'));
	EXPECT_CALL(*mSnake, changeSnakeHeadCoordinates(mSnake->getDirection())).Times(1).WillRepeatedly(Return(Icoord));

	compareCoordValues(snakeHead, BOARDSIZE-1, 0);
	compareCoordValues(snakeHead1, 0, 0);

	delete snakeHead, snakeHead1;

}

//========================================================================================================
//===========================================BOARD TEST===================================================

class TestBoard : public ::testing::Test {
protected:
	IBoard * Iboard;
	ISnake * snake;
	IApple * apple;
	int expected = BOARDSIZE / 2;

	void SetUp() override
	{
		Iboard = new Board();
		snake = new Snake();
		apple = new Apple();
	}

	void TearDown() override
	{
		delete Iboard, snake, apple;
	}
};

TEST_F(TestBoard, TestBoardCreateAndSetvectorSizeAndFillItFields) {
	IBoard * Iboard = new Board(10);
	EXPECT_THAT(Iboard->getvectorSize(), 10);

	Iboard->clear();
	for (auto line : Iboard->getVector())
		for (auto segment : line)
		{
			EXPECT_THAT(segment, '.');
		}
	delete Iboard;
}

TEST_F(TestBoard, CreateAndSetvectorSizetoZeroAndMinusCatchLogicErrorAndChangValueToDefault)
{
	Iboard = new Board(-1);
	EXPECT_THAT(Iboard->getvectorSize(), BOARDSIZE);
	Iboard = new Board(0);
	EXPECT_THAT(Iboard->getvectorSize(), BOARDSIZE);
}

TEST_F(TestBoard, SetvectorCoordWithCharSymbol)
{
	snake = new Snake(1, 1);
	apple = new Apple(2, 2);
	Iboard = new Board(BOARDSIZE);

	Iboard->setvectorCoord(0, 1, '.');
	Iboard->setvectorCoord(snake->getSnakeHead()->getCoordX(),snake->getSnakeHead()->getCoordY(), 'o');
	Iboard->setvectorCoord(apple->getAppleCoords()->getCoordX(),apple->getAppleCoords()->getCoordY(), 'x');

	EXPECT_EQ(Iboard->getvectorCoord(0, 1), '.');
	EXPECT_EQ(Iboard->getvectorCoord(1, 1), 'o');
	EXPECT_EQ(Iboard->getvectorCoord(2, 2), 'x');
}

TEST_F(TestBoard, TestBoardFillItFields)
{
	Iboard = new Board(3);
	Iboard->clear();

	std::vector <std::vector<char> >
		expected = { {'.','.','.'} ,{'.','.','.'}, {'.','.','.'} }; // "{...}{...}{...}";
	std::vector <std::vector<char> >
		expectedFail = { {'.','.','x'} ,{'.','.','.'}, {'.','.','.'} }; // "{..x}{...}{...}";

	EXPECT_EQ(Iboard->clear(), expected);
	EXPECT_NE(Iboard->clear(), expectedFail);
}

TEST_F(TestBoard, TestBoardScore)
{
	Iboard = new Board(3);
	EXPECT_EQ(Iboard->getScore(), 0);
	Iboard->setScore(); Iboard->setScore();
	EXPECT_EQ(Iboard->setScore(), 2);
}

TEST_F(TestBoard, DrawSnakeCoordOnBoard)
{
	snake = new Snake(1,1);
	Iboard = new Board(snake, BOARDSIZE);

	Iboard->clear(); //set every field on Board to '.'
	Iboard->drawSnakeOnBoardbyIcoord();

	EXPECT_EQ(Iboard->getvectorCoord(1, 1), 'o');
}

TEST_F(TestBoard, TestDrawSnakeOnBoard)
{
	Iboard = new Board(BOARDSIZE);
	snake = new Snake();
	Iboard->clear();
	std::vector <std::vector<char> > expectedEmpty = Iboard->getVector();

	EXPECT_THAT(snake->getCoord_Container(), ::testing::IsEmpty());

	Iboard->drawSnakeOnBoard(snake->getSnakeHead()->getCoordX(), snake->getSnakeHead()->getCoordY());
	std::vector <std::vector<char> > expectedSnake = Iboard->getVector();

	compareCoordValues(snake->getSnakeHead(), expected, expected);
	EXPECT_NE(expectedEmpty, expectedSnake);
	EXPECT_EQ(Iboard->getvectorCoord(expected , expected), 'o');
}

TEST(TestMockSnake, createMockSnakeAndPutCoordinatesOfSnakeHeadOnTheBoard)
{
	using::testing::Return;
	ICoord * coord = new Coord(BOARDSIZE-2, BOARDSIZE - 2);
	MockSnake * mSnake = new MockSnake();
	
	EXPECT_CALL(*mSnake, getSnakeHead()).WillRepeatedly(Return(coord));
	IBoard * board = new Board(mSnake , BOARDSIZE);

	EXPECT_EQ(board->getvectorSize() , BOARDSIZE);
	compareSnakeHeadCoord(mSnake, (BOARDSIZE - 2), (BOARDSIZE - 2));
	EXPECT_EQ(board->getvectorCoord((mSnake->getSnakeHead())->getCoordX() , 
									(mSnake->getSnakeHead())->getCoordY()), 
									'o');
	delete board;	delete coord;	delete mSnake;
}

TEST_F(TestBoard, PrintSnakeOnBoardUsingCoordMock)
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

TEST_F(TestBoard, SnakeMoveOnBordTwoFieldRightAndWasPrintOnBoard)
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

TEST_F(TestBoard, SnakeMoveOnBordTwoFieldRightCrossBoardEndAndWasPrintOnBoard)
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

TEST_F(TestBoard, SnakeMoveOnBordTwoFieldEeatsAnAppleAndGrows)
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

TEST_F(TestBoard, SnakeMoveOnBordAndHitItself)
{
	snake = new Snake(new Coord(1,0));
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
	EXPECT_FALSE(snake->snakeHitItself());
	snake->changeSnakeHeadCoordinates(snake->getDirection());
	EXPECT_TRUE (snake->snakeHitItself());
 }

TEST_F(TestBoard, SnakeMoveOnBordEeatsTwoApplesGrowsAndHitHisBody)
{
	snake = new Snake(new Coord(1, 0));
	IApple * apple = new Apple(1, 1);
	IApple * apple2 = new Apple(1, 2);
	Iboard = new Board(snake, apple, BOARDSIZE);

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
		EXPECT_FALSE(snake->snakeHitItself());
		snake->changeSnakeHeadCoordinates(snake->getDirection());
		Iboard->SnakeEatsApple();
		if (Iboard->eatApple) //change apple coord to next field
		{
			apple->getAppleCoords()->setCoordX(1);
			apple->getAppleCoords()->setCoordY(2);
		}
		EXPECT_TRUE(Iboard->eatApple);
		EXPECT_FALSE(snake->snakeHitItself());
	}
	snake->changeSnakeHeadCoordinates(snake->getDirection());
	EXPECT_TRUE(snake->snakeHitItself());
	delete apple, apple2;
}

TEST_F(TestBoard, SnakeMoveOnWholeBoardCrossBordersAndEatsApples)
{
	int numberOfeatedApples = 0;
	snake = new Snake(new Coord(BOARDSIZE/2, 0));
	IApple * apple = new Apple(new Coord());
	Iboard = new Board(snake, apple, BOARDSIZE);

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
		Iboard->drawSnakeOnBoardbyIcoord();
		Iboard->SnakeEatsApple(); //put random apple on '.' field	
		if (Iboard->eatApple) numberOfEatApple++;
		Iboard->drawApplOnBoardbyIcoord();
		counter++;
	}
	EXPECT_EQ( 2, snake->getSnakeLength()- numberOfEatApple);
	compareCoordValues(snake->getSnakeHead() , expected, 1); //snake starts and end in the same point
	delete apple;
}

TEST_F(TestBoard, SnakeMoveOnWholeBoardCrossBordersAndEatsApplesUntilHislengthIs20)
{
	int numberOfeatedApples = 0;
	snake = new Snake(new Coord(BOARDSIZE / 2, 0));
	IApple * apple = new Apple(new Coord());
	Iboard = new Board(snake, apple, BOARDSIZE);

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
		Iboard->drawSnakeOnBoardbyIcoord();
		Iboard->SnakeEatsApple(); //put random apple on '.' field	
		if (Iboard->eatApple) numberOfEatApple++;
		Iboard->drawApplOnBoardbyIcoord();
		counter++;

		if (snake->getSnakeLength() == 20)
		{
			break;
		}
	}
	
	EXPECT_EQ(snake->getSnakeLength(), 20);
	delete apple;
}

TEST_F(TestBoard, SnakeMoveOnWholeBoardCrossBordersAndEatsMockApplesUntilThereIsNoSpaceAngGameEnds)
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
class TestApple : public ::testing::Test {
protected:
	IApple * apple;
	int expected = BOARDSIZE / 2;

	void SetUp() override
	{
		apple = new Apple();
	}

	void TearDown() override
	{
		delete apple;
	}
};

TEST_F(TestApple, CreateAppleInstanceWithDefaultConstructor)
{
	compareCoordValues(apple->getAppleCoords(), expected - 1, expected - 1);
}

TEST_F(TestApple, CreateAppleInstancesWithDifrentValues)
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

TEST_F(TestApple, PutAndPrintAppleAndSnakeOnBoardDuringCreation)
{
	ISnake * snake = new Snake(new Coord());
	IApple * apple = new Apple(new Coord());
	IBoard * board = new Board(snake, apple, BOARDSIZE);

	compareCoordValues(snake->getSnakeHead(), BOARDSIZE/2 , BOARDSIZE/2);
	EXPECT_TRUE(compareCoordsAreNotEq(snake->getSnakeHead(), apple->getAppleCoords()));

	delete apple, snake, board;
}

TEST_F(TestApple, PutAndPrintAppleOnBoardOnTheSameLocationAsSnakeHasDuringCreation)
{
	IApple * apple = new Apple(5 , 7);
	ISnake * snake = new Snake(5 , 7);
	EXPECT_FALSE(compareCoordsAreNotEq(snake->getSnakeHead(), apple->getAppleCoords())) <<"ARTUR"<< snake->getSnakeHead()->printCoordinates();
	IBoard * board = new Board(snake, apple , BOARDSIZE);

	compareCoordValues(snake->getSnakeHead(), 5, 7);
	EXPECT_TRUE(compareCoordsAreNotEq(snake->getSnakeHead() , apple->getAppleCoords()) );

	delete apple, snake, board;
}

TEST_F(TestApple, PutAndPrintAppleOnBoardwhenOnlyOneFieldIsEmptyRestIsSnakeBody)
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

	EXPECT_EQ(board->getvectorCoord(0,0) , '.');

	board->drawApplOnBoardbyIcoord(); //drow random apple on empty field
	EXPECT_EQ(board->getvectorCoord(0, 0), 'x');

	delete apple, snake, board;
}

TEST_F(TestApple, EveryTimeAppleIsPrintedOnRandomEmptyField)
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

TEST_F(TestApple, NospaceForApple)
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

TEST(TestMocks, TestSnakeUsingNiceMockUninterestingcallsIgnore)
{
	using::testing::NiceMock;
	NiceMock<MockCoord> * mCoord =	new NiceMock<MockCoord>;
	ISnake * snake = new Snake(mCoord);
	IBoard * board = new Board(snake, BOARDSIZE);

	EXPECT_CALL(*mCoord, getCoordX()).WillOnce(Return(3));
	EXPECT_CALL(*mCoord, getCoordY()).WillOnce(Return(3));
	compareCoordValues(snake->getSnakeHead(), 3, 3);
	delete snake, board;

}

TEST(TestMocks, TestSnakeUsingStrictMock)
{
	using::testing::StrictMock;
	StrictMock<MockCoord> * mCoord = new StrictMock<MockCoord>;
	ISnake * snake = new Snake(mCoord);

	EXPECT_CALL(*mCoord, getCoordX()).WillOnce(Return(0)).WillOnce(Return(3));
	EXPECT_CALL(*mCoord, getCoordY()).WillOnce(Return(0)).WillOnce(Return(3));

	IBoard * board = new Board(snake, BOARDSIZE);
	compareCoordValues(snake->getSnakeHead() , 3,3);
	delete  snake, board;
}

TEST(TestMocks, TestSnakeEatsApple)
{
	using::testing::StrictMock;
	StrictMock<MockCoord> * mCoord = new StrictMock<MockCoord>;
	
	//MockCoord * mCoord = new MockCoord;
	ISnake * snake = new Snake(mCoord);
	IApple * apple = new Apple(4,4);
	
	EXPECT_CALL(*mCoord, getCoordX()).WillOnce(Return(3)).WillOnce(Return(4));
	EXPECT_CALL(*mCoord, getCoordY()).WillOnce(Return(3)).WillOnce(Return(4));
	
	IBoard * board = new Board(snake, apple, BOARDSIZE);

	EXPECT_CALL(*mCoord, getCoordX()).WillOnce(Return(4)).WillOnce(Return(4)); //calls in constructor
	EXPECT_CALL(*mCoord, getCoordY()).WillOnce(Return(4)).WillOnce(Return(4)); //calls in constructor
	compareCoordValues(apple->getAppleCoords(), 4, 4); //before call SnakeEatsApple

	board->SnakeEatsApple();
	EXPECT_TRUE(board->eatApple);
	ASSERT_EQ(snake->getSnakeLength() , 3);
	compareCoordValues(snake->getSnakeHead(), 4, 4);
	delete apple, snake, board;
}

TEST(TestMocks, TestSnakeDontEatsApple)
{
	using::testing::StrictMock;
	StrictMock<MockCoord> * mCoord = new StrictMock<MockCoord>;
	//MockCoord * mCoord = new MockCoord;
	ISnake * snake = new Snake(mCoord);
	IApple * apple = new Apple(5, 5);

	EXPECT_CALL(*mCoord, getCoordX()).WillOnce(Return(3)).WillOnce(Return(4));//calls in constructor
	EXPECT_CALL(*mCoord, getCoordY()).WillOnce(Return(3)).WillOnce(Return(4));//calls in constructor

	IBoard * board = new Board(snake, apple, BOARDSIZE);
	compareCoordValues(apple->getAppleCoords(), 5, 5); //before call SnakeEatsApple

	EXPECT_CALL(*mCoord, getCoordX()).WillOnce(Return(4))
		.WillOnce(Return(4))
		.WillOnce(Return(4));
	EXPECT_CALL(*mCoord, getCoordY()).WillOnce(Return(4))
		.WillOnce(Return(5))
		.WillOnce(Return(4));
	EXPECT_CALL(*mCoord, setCoordY(5)).WillOnce(Return(5));

	snake->changeSnakeHeadCoordinates(snake->getDirection()); //add head to cont and chceck borders
	board->SnakeEatsApple();
	
	EXPECT_FALSE(board->eatApple);
	ASSERT_EQ(snake->getSnakeLength(), 2);
	EXPECT_EQ(snake->getCoord_Container().size(), 1);

	compareCoordValues(snake->getSnakeHead(), 4, 5);
	delete apple, snake, board;
}

TEST(TestMocks, TestSnakedrawSetUpBoardAndDrawSnakeOnBoardbyIcoord)
{
	using::testing::DefaultValue;
	using::testing::StrictMock;
	StrictMock<MockSnake> * mSnake = new StrictMock<MockSnake>;
	IApple * apple = new Apple(5, 5);

	DefaultValue<Coord>::Set(new Coord(2, 2));

	EXPECT_CALL(*mSnake, getSnakeHead()).WillOnce(Return(new Coord(2, 2)))
		.WillOnce(Return(new Coord(2, 2)))
		.WillOnce(Return(new Coord(2, 2)))
		.WillOnce(Return(new Coord(2, 2)))
		.WillOnce(Return(new Coord(2, 2)));

	IBoard * board = new Board(mSnake, apple, BOARDSIZE);
	compareCoordValues(mSnake->getSnakeHead() , 2,2);

	EXPECT_CALL(*mSnake, getDirection()).WillRepeatedly(Return('r'));
	EXPECT_EQ(mSnake->getDirection(), 'r');
	EXPECT_CALL(*mSnake, changeSnakeHeadCoordinates('r'))
		.WillOnce(Return(new Coord(2, 2)));

	board->setvectorCoord(mSnake->getSnakeHead()->getCoordX(), mSnake->getSnakeHead()->getCoordY(), 'o' );
	EXPECT_EQ(board->getvectorCoord(2,2), 'o');
	delete apple, mSnake, board;
}

TEST(TestMocks, SetUpDefaulValueCoord)
{
	using::testing::AnyNumber;
	using::testing::DefaultValue;
	using::testing::StrictMock;

	StrictMock<MockSnake> * snake = new StrictMock<MockSnake>;
	
	ICoord * coord = new Coord(3, 4);
	DefaultValue<ICoord*>::Set(coord);
	
	EXPECT_CALL(*snake, changeSnakeHeadCoordinates('r')).Times(AnyNumber());;
	EXPECT_CALL(*snake , getSnakeHead()).Times(AnyNumber());

	compareCoordValues( snake->changeSnakeHeadCoordinates('r') , 3,4);
	compareCoordValues(snake->getSnakeHead(), 3, 4);
	DefaultValue<Coord>::Clear(); // unset Default Value
	delete snake, coord;
}

TEST(TestMocks, SetSnakeTailUsingDefaultActionMock)
{
	using::testing::Return;
	MockCoord * mCoord = new MockCoord(); //snake tail [3,2]
	ISnake* snake = new Snake(mCoord);

	ON_CALL(*mCoord, getCoordX()).WillByDefault(Return(3));
	ON_CALL(*mCoord, getCoordY()).WillByDefault(Return(2));
	snake->setSnakeTail();
	compareCoordValues(snake->getSnakeHead(), 3, 2);
	compareCoordValues(snake->getSnakeTail(), 3, 2);
	delete snake, mCoord;
}


TEST(TestMocks, SetSnakeTailUsingDefaultActionMock2)
{
	using::testing::Return;
	MockCoord * mCoord = new MockCoord(); //snake tail [3,2]
	ISnake* snake = new Snake(mCoord);

	ON_CALL(*mCoord, getCoordX()).WillByDefault(Return(3));
	ON_CALL(*mCoord, getCoordY()).WillByDefault(Return(2));

	snake->setSnakeTail();
	compareCoordValues(snake->getSnakeHead(), 3, 2);
	compareCoordValues(snake->getSnakeTail(), 3, 2);
	delete snake, mCoord;
}

TEST(TestMocks, SetExpectCallinSequence)
{
	using::testing::Return;
	MockCoord * mCoord = new MockCoord(); //snake tail [3,2]
	ISnake* snake = new Snake(mCoord);

/*#4*/	EXPECT_CALL(*mCoord, setCoordX(::testing::_)).WillOnce(Return(43)).RetiresOnSaturation();
/*#3*/	EXPECT_CALL(*mCoord, setCoordX(3)).WillOnce(Return(11));
/*#2*/	EXPECT_CALL(*mCoord, setCoordX(::testing::_)).WillOnce(Return(10)).RetiresOnSaturation();;
/*#1*/	EXPECT_CALL(*mCoord, setCoordX(::testing::_)).WillOnce(Return(4)).RetiresOnSaturation();

/*	for (int i = 3; i > 0; i--) {
		EXPECT_CALL(*mCoord, setCoordX(::testing::_))
			.WillOnce(Return(10 * i))
			.RetiresOnSaturation();
		}*/
	ASSERT_EQ(snake->getSnakeHead()->setCoordX(2), 4); //#1
	ASSERT_EQ(snake->getSnakeHead()->setCoordX(2), 10);//#2
	ASSERT_EQ(snake->getSnakeHead()->setCoordX(3), 11);//#3
	ASSERT_EQ(snake->getSnakeHead()->setCoordX(34), 43);//#4
}