#include "ConsoleGameSnake.h"

#include <chrono>
#include <iostream>
#include <thread>
#ifdef _WIN32
#include <conio.h>
#endif
#include <ctime>

TailSegment::TailSegment() {}
TailSegment::~TailSegment() {}

Fruits::Fruits() {}
Fruits::~Fruits() {}

void Fruits::Generate(int w, int h) {
  std::time_t current_time = time(nullptr);
  srand(static_cast<unsigned int>(current_time));
  x_ = rand() % (w - 2);
  y_ = rand() % (h - 2);
}
int Fruits::Get_x_() {
  return x_;
}
int Fruits::Get_y_() {
  return y_;
}
void Fruits::Draw() {
  std::cout << "O";
}



ConsoleGameSnake::ConsoleGameSnake() {}
ConsoleGameSnake::~ConsoleGameSnake() {}

bool ConsoleGameSnake::Control() {
  std::cout << " w - up, s - down, a - left, d - right, x - exit to menu.\n Press any key to continue." << std::endl;
#ifdef _WIN32
  _getch();
#else
#ifdef __linux__
  getchar();
#endif
#endif
  return true;
}
bool ConsoleGameSnake::Setup(int w, int h) {
  ConsoleGameBase::Setup(w, h);

  game_over_ = false;
  dir_ = STOP;
  x_ = width_ / 2 - 1;
  y_ = height_ / 2 - 1;
  apple.Generate(width_, height_);
  score_ = 0;
  return true;
}

bool ConsoleGameSnake::Draw() {
#ifdef _WIN32
  system("cls");
#else
#ifdef __linux__
  system("clear");
#endif
#endif
  for (int i = 0; i < width_ + 1; ++i) {
    std::cout << "\xB2";
  }
  std::cout << std::endl;
  for (int i = 0; i < height_; ++i) {
    for (int j = 0; j < width_; ++j) {
      if (j == 0 || j == width_ - 1) {
        std::cout << "\xB2";
      }
      if (i == y_ && j == x_) {
        std::cout << "0";
      } else if (i == apple.Get_y_() && j == apple.Get_x_()) {
        apple.Draw();
      } else {
        bool print = false;
		for (auto it = tail_.begin(); it != tail_.end(); ++it) {
			if (it->x == j && it->y == i) {
				print = true;
				std::cout << "o";
				break;
			}
		}
        if (!print) {
          std::cout << " ";
        }
      }
    }
    std::cout << std::endl;
  }
  for (int i = 0; i < width_ + 1; ++i) {
    std::cout << "\xB2";
  }
  std::cout << std::endl;
  std::cout << "Score: " << score_ << std::endl;
  std::this_thread::sleep_for(std::chrono::milliseconds(70));
  return true;
}

bool ConsoleGameSnake::Input() {
  if (_kbhit()) {
#ifdef _WIN32
    switch (_getch()) {
#else
#ifdef __linux__
    switch (getchar()) {
#endif
#endif
      case 'a':
		  if (dir_ != eDirection::RIGHT) {
			  dir_ = eDirection::LEFT;
		  }
        break;
      case 'd':
		  if (dir_ != eDirection::LEFT) {
			  dir_ = eDirection::RIGHT;
		  }
        break;
      case 'w':
		  if (dir_ != eDirection::DOWN) {
			  dir_ = eDirection::UP;
		  }
        break;
      case 's':
		  if (dir_ != eDirection::UP) {
			  dir_ = eDirection::DOWN;
		  }
        break;
      case 'x':
        game_over_ = true;
        break;
    }
  }
  return true;
}

bool ConsoleGameSnake::Logic() {
  // insert new tail segment
  TailSegment prev_head;
  prev_head.x = x_;
  prev_head.y = y_;
  
  // move head
  switch (dir_) {
    case LEFT:
      x_--;
      tail_.push_front(prev_head);
      break;
    case RIGHT:
      x_++;
      tail_.push_front(prev_head);
      break;
    case UP:
      y_--;
      tail_.push_front(prev_head);
      break;
    case DOWN:
      y_++;
      tail_.push_front(prev_head);
      break;
    default:
      break;
  }
  //check wall
#ifdef STRONG_WALL
  if (x_ > width_ || x_ < 0 || y_ > height_ || y_ < 0) {
    game_over_ = true;
  }
#endif
  if (x_ >= width_ - 1) {
    x_ = 0;
  } else if (x_ < 0) {
    x_ = width_ - 2;
  }
  if (y_ >= height_) {
    y_ = 0;
  } else if (y_ < 0) {
    y_ = height_ - 1;
  }
  //check yourself
  for (auto it = tail_.begin(); it != tail_.end(); ++it) {
    if (it->x == x_ && it->y == y_) {
      game_over_ = true;
    }
  }
  //check fruit
  if (x_ == apple.Get_x_() && y_ == apple.Get_y_()) {
    score_ += 10;
    apple.Generate(width_,height_);
  }
  else {
    if (!tail_.empty()) {
      tail_.pop_back();
    }
  }
  return true;
}
