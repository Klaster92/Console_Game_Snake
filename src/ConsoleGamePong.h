#ifndef SRC_CONSOLEGAMEPONG_H
#define SRC_CONSOLEGAMEPONG_H
#include "ConsoleGameBase.h"
class ConsoleGamePong : public ConsoleGameBase {
public:
	ConsoleGamePong();
	virtual ~ConsoleGamePong();

	virtual bool Setup();
	virtual bool Draw();
	virtual bool Input();
	virtual bool Logic();

private:
	
};
#endif