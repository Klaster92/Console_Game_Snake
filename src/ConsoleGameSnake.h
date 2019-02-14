#ifndef SRC_CONSOLEGAMESNAKE_H
#define SRC_CONSOLEGAMESNAKE_H
#include "ConsoleGameBase.h"
class ConsoleGameSnake : public ConsoleGameBase {
public:
	ConsoleGameSnake();
	virtual ~ConsoleGameSnake();
	
	virtual bool Setup();
	virtual bool Draw();
	virtual bool Input();
	virtual bool Logic();
	
private:
	int width;
	int height;
	int x, y, fruitX, fruitY, score;
	int tailX[100], tailY[100];
	int nTail;
	enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
	eDirection dir;
};
#endif
