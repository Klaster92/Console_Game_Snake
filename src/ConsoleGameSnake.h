#ifndef SRC_CONSOLEGAMESNAKE_H
#define SRC_CONSOLEGAMESNAKE_H

#include <list>

#include "ConsoleGameBase.h"

//#define STRONG_WALL

struct TailSegment {
public:
	int x, y;
};

class ConsoleGameSnake : public ConsoleGameBase {
public:
	ConsoleGameSnake();
	virtual ~ConsoleGameSnake();
	
	virtual bool Control();
	virtual bool Setup(int w, int h);
	virtual bool Draw();
	virtual bool Input();
	virtual bool Logic();
	
private:
	int x_, y_, fruit_x_, fruit_y_, score_;
	std::list <TailSegment> tail_;
	/*int tail_x_[100], tail_y_[100];
	int n_tail_;*/
	enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
	eDirection dir_;
};
#endif
