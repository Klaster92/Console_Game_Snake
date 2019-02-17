#include "ConsoleGameSnake.h"

#include <chrono>
#include <iostream>
#include <thread>
#ifdef _WIN32
#include <conio.h>
#endif
#include <ctime>

ConsoleGameSnake::ConsoleGameSnake() {}
ConsoleGameSnake::~ConsoleGameSnake() {}

bool ConsoleGameSnake::Setup(int w, int h) {
  ConsoleGameBase::Setup(w, h);

  game_over_ = false;
  dir_ = STOP;
  x_ = width_ / 2 - 1;
  y_ = height_ / 2 - 1;
  std::time_t current_time = time(nullptr);
  srand(static_cast<unsigned int>(current_time));
  fruit_x_ = rand() % (width_ - 2);
  fruit_y_ = rand() % (height_ - 2);
  score_ = 0;
  n_tail_ = 0;
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
      } else if (i == fruit_y_ && j == fruit_x_) {
        std::cout << "\xE0";
      } else {
        bool print = false;
        for (int k = 0; k < n_tail_; ++k) {
          if (tail_x_[k] == j && tail_y_[k] == i) {
            print = true;
            std::cout << "o";
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
        dir_ = LEFT;
        break;
      case 'd':
        dir_ = RIGHT;
        break;
      case 'w':
        dir_ = UP;
        break;
      case 's':
        dir_ = DOWN;
        break;
      case 'x':
        game_over_ = true;
        break;
    }
  }
  return true;
}

bool ConsoleGameSnake::Logic() {
  int prev_x = tail_x_[0];
  int prev_y = tail_y_[0];
  int prev_2x, prev_2y;
  tail_x_[0] = x_;
  tail_y_[0] = y_;
  for (int i = 1; i < n_tail_; ++i) {
    prev_2x = tail_x_[i];
    prev_2y = tail_y_[i];
    tail_x_[i] = prev_x;
    tail_y_[i] = prev_y;
    prev_x = prev_2x;
    prev_y = prev_2y;
  }
  switch (dir_) {
    case LEFT:
      x_--;
      break;
    case RIGHT:
      x_++;
      break;
    case UP:
      y_--;
      break;
    case DOWN:
      y_++;
      break;
    default:
      break;
  }

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
  for (int i = 0; i < n_tail_; ++i) {
    if (tail_x_[i] == x_ && tail_y_[i] == y_) {
      game_over_ = true;
    }
  }
  if (x_ == fruit_x_ && y_ == fruit_y_) {
    score_ += 10;
    std::time_t current_time = time(nullptr);
    srand(static_cast<unsigned char>(current_time));
    fruit_x_ = 1 + rand() % (width_ - 2);
    fruit_y_ = 1 + rand() % (height_ - 2);
    n_tail_++;
  }
  return true;
}
