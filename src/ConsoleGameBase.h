#ifndef SRC_CONSOLEGAMEBASE_H
#define SRC_CONSOLEGAMEBASE_H

class ConsoleGameBase {
public:
	ConsoleGameBase();
	virtual ~ConsoleGameBase();
	
	virtual bool Setup() = 0;
	virtual bool Draw() = 0;
	virtual bool Input() = 0;
	virtual bool Logic() = 0;
	
	bool GameOver() const;
	bool gameOver;
};
#endif
