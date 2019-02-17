#include "ConsoleGameBase.h"

#ifdef __linux__
#include <sys/ioctl.h>
#include <termios.h>

bool _kbhit() {
  termios term;
  tcgetattr(0, &term);

  termios term2 = term;
  term2.c_lflag &= static_cast<unsigned int>(~ICANON);
  tcsetattr(0, TCSANOW, &term2);

  int byteswaiting;
  ioctl(0, FIONREAD, &byteswaiting);

  tcsetattr(0, TCSANOW, &term);

  return byteswaiting > 0;
}
#endif

ConsoleGameBase::ConsoleGameBase() : width_(0), height_(0) {}
ConsoleGameBase::~ConsoleGameBase() {}

bool ConsoleGameBase::Setup(int w, int h) {
  width_ = w;
  height_ = h;
  return true;
}

bool ConsoleGameBase::GameOver() const {
  return game_over_;
}
