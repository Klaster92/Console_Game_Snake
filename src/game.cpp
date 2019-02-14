#include "ConsoleGameBase.h"
#include "ConsoleGameSnake.h"

int main() {
	ConsoleGameBase* gameptr = new ConsoleGameSnake();
	gameptr->Setup();
	while(!gameptr->GameOver()) {
	gameptr->Draw();
	gameptr->Input();
	gameptr->Logic();
	}
	return 0;
}
