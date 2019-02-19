#ifndef SRC_CONSOLEGAMESNAKE_H
#define SRC_CONSOLEGAMESNAKE_H

#include <list>

#include "ConsoleGameBase.h"

//#define STRONG_WALL

struct TailSegment {
public:
  TailSegment();
  virtual ~TailSegment();

	int x, y;
};

class Fruits {
public:
  Fruits();
  virtual ~Fruits();

  void Generate(int w, int h);
  int Get_x_();
  int Get_y_();
  void Draw();

private:
  int x_, y_;

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
	int x_, y_, score_;
  Fruits apple;
	std::list <TailSegment> tail_;
	enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
	eDirection dir_;
};
#endif
