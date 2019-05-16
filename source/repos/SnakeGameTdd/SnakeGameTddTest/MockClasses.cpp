#include <gmock/gmock.h>
#include "../SnakeGameTdd/ICoord.h"
#include "../SnakeGameTdd/ICoord.cpp"
#include "../SnakeGameTdd/ISnake.h"
#include "../SnakeGameTdd/ISnake.cpp"

class MockCoord : public ICoord
{
public:
	MockCoord() {};

	MOCK_METHOD0(getCoordX , int(void) );
	MOCK_METHOD0(getCoordY , int(void));
	MOCK_METHOD1(setCoordX, int (int x));
	MOCK_METHOD1(setCoordY, int(int x));
	MOCK_METHOD0(printCoordinates , std::string(void));
	MOCK_METHOD1(checkBorders , int(int a));

};

class MockSnake : public ISnake
{
public:
	MOCK_METHOD1(setDirection , char(char moveKey));
	MOCK_METHOD1(changeSnakeHeadCoordinates , ICoord * (char _direction) );
	MOCK_METHOD0(setSnakeTail, void(void));
	MOCK_METHOD0(snakeHitItself, bool());
	MOCK_METHOD1(putSnakeHeadCoorinatesToDeque, void(Coord& coord));

	MOCK_METHOD0(getDirection, char(void) );
	MOCK_METHOD0(getSnakeHead , ICoord* (void));
	MOCK_METHOD0(getSnakeTail, ICoord* (void));
	MOCK_METHOD0(getFieldToClear, ICoord* (void));
	MOCK_METHOD0(getCoord_Container , std::deque<Coord>(void));
	MOCK_METHOD0(setSnakeLength, int(void));
	MOCK_METHOD0(getSnakeLength, int(void));
	MOCK_METHOD0(getEndGame, bool(void));
};
