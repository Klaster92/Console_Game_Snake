#include "ConsoleGameBase.h"

ConsoleGameBase::ConsoleGameBase(): width_(0), height_(0) {}
ConsoleGameBase::~ConsoleGameBase(){}

bool ConsoleGameBase::Setup(int w, int h) {
	width_ = w;
	height_ = h;
	return true;
}

bool ConsoleGameBase::GameOver() const {
	return game_over_; 
}
