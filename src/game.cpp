#include <algorithm>
#include <string>
#include <iostream>
#include <cctype>

#include "ConsoleGameBase.h"
#include "ConsoleGameSnake.h"
#include "ConsoleGamePong/ConsoleGamePong.h"

bool CheckUserInput(const std::string& check) {
	if (check.size() > 1 || check.empty()) {
		return false;
	}
	if (!std::all_of(check.begin(), check.end(), ::isdigit)) {
		return false;
	}
	return true;
}

int main() {
	std::shared_ptr<ConsoleGameBase> gameptr = nullptr;
	while (true) {
		std::cout << "Type game number. Aviable games:\n\t1. Snake\n\t2. Pong" << std::endl;
		std::string userInput;
		std::getline(std::cin, userInput);
		if (CheckUserInput(userInput)) {
			int game_number = atoi(userInput.c_str());
			if (game_number == 1) {
				gameptr = std::make_shared<ConsoleGameSnake>();
			}
			else if(game_number == 2) {
				gameptr = std::make_shared<ConsoleGamePong>();
			}
			else {
				std::cout << "Incorrect game number. Try again." << std::endl;
				continue;
			}
			gameptr->Setup(40, 20);
			while (!gameptr->GameOver()) {
				gameptr->Draw();
				gameptr->Input();
				gameptr->Logic();
			}
		}
		else {
			std::cout << "Incorrect input format. Try again." << std::endl;
			continue;
		}
	}
	return 0;
}
