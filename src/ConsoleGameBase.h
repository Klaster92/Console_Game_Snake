#ifndef SRC_CONSOLEGAMEBASE_H
#define SRC_CONSOLEGAMEBASE_H

#ifdef __linux__
#include <unistd.h>
bool _kbhit();
#endif

class ConsoleGameBase {
public:
	ConsoleGameBase();
	virtual ~ConsoleGameBase();

	virtual bool Setup(int w, int h);
	virtual bool Draw() = 0;
	virtual bool Input() = 0;
	virtual bool Logic() = 0;

	bool GameOver() const;
	bool game_over_;

	int width_;
	int height_;
};
#endif
