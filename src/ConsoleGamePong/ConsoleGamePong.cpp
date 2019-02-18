#include "ConsoleGamePong.h"

#include <time.h>
#include <chrono>
#include <iostream>
#include <thread>
#ifdef _WIN32
#include <conio.h>
#endif

Ball::Ball() {
  original_x_ = 0;
  original_y_ = 0;
  x_ = 0;
  y_ = 0;
  direction_ = STOP;  // cBall
}

void Ball::Setup(int x_external, int y_external) {
  x_ = x_external;
  y_ = y_external;
  original_x_ = x_external;
  original_y_ = y_external;
}

void Ball::Reset() {
  x_ = original_x_;
  y_ = original_y_;
  direction_ = STOP;  // reset()
}

void Ball::ChangeDirection(const eDir& d) {
  direction_ = d;
}

void Ball::RandomDirection() {
  direction_ = static_cast<eDir>((rand() % 6) + 1);
}

inline int Ball::GetX() const {
  return x_;
}

inline int Ball::GetY() const {
  return y_;
}

inline eDir Ball::GetDirection() const {
  return direction_;
}

void Ball::Move() {
  switch (direction_) {
    case STOP:
      break;
    case LEFT:
      x_--;
      break;
    case RIGHT:
      x_++;
      break;
    case UPLEFT:
      x_--;
      y_--;
      break;
    case DOWNLEFT:
      x_--;
      y_++;
      break;
    case UPRIGHT:
      x_++;
      y_--;
      break;
    case DOWNRIGHT:
      x_++;
      y_++;
      break;
    default:
      break;
  }
}

Paddle::Paddle() {
  x_ = y_ = 0;
}

Paddle::Paddle(int pos_x, int pos_y) : Paddle() {
  Setup(pos_x, pos_y);
}

void Paddle::Setup(int pos_x, int pos_y) {
  original_x_ = pos_x;
  original_y_ = pos_y;
  x_ = pos_x;
  y_ = pos_y;
}

inline void Paddle::Reset() {
  x_ = original_x_;
  y_ = original_y_;
}

inline int Paddle::GetX() const {
  return x_;
}

inline int Paddle::GetY() const {
  return y_;
}

inline void Paddle::MoveUp() {
  y_--;
}

inline void Paddle::MoveDown() {
  y_++;
}

ConsoleGamePong::ConsoleGamePong()
    : ball_ptr_(std::make_shared<Ball>()),
      player1_ptr_(std::make_shared<Paddle>()),
      player2_ptr_(std::make_shared<Paddle>()) {}
ConsoleGamePong::~ConsoleGamePong() {}

bool ConsoleGamePong::Control() {
  std::cout << " 1Player: w - up, s - down.\n 2Player: i - up, k - down.\n x - exit to menu.\n Press any key to continue." << std::endl;
#ifdef _WIN32
  _getch();
#else
#ifdef __linux__
  getchar();
#endif
#endif
  return true;
}

bool ConsoleGamePong::Setup(int w, int h) {
  if (w < 5 || h < 5) {
    game_over_ = true;
    return false;
  }
  ConsoleGameBase::Setup(w, h);

  ball_ptr_->Setup(w / 2, h / 2);

  player1_ptr_->Setup(1, h / 2 - 3);
  player2_ptr_->Setup(w - 2, h / 2 - 3);

  srand(static_cast<unsigned int>(time(nullptr)));
  game_over_ = false;
  up1_ = 'w';
  up2_ = 'i';
  down1_ = 's';
  down2_ = 'k';
  score1_ = score2_ = 0;
  width_ = w;
  height_ = h;
  return true;
}

bool ConsoleGamePong::Draw() {
#ifdef _WIN32
  system("cls");
#else
#ifdef __linux__
  system("clear");
#endif
#endif
  for (int i = 0; i < width_ + 2; i++) {
    std::cout << "\xB2";
  }
  std::cout << std::endl;

  for (int i = 0; i < height_; i++) {
    for (int j = 0; j < width_; j++) {
      int ballx = ball_ptr_->GetX();
      int bally = ball_ptr_->GetY();
      int player1x = player1_ptr_->GetX();
      int player2x = player2_ptr_->GetX();
      int player1y = player1_ptr_->GetY();
      int player2y = player2_ptr_->GetY();

      if (j == 0) {
        std::cout << "\xB2";
      }

      if (ballx == j && bally == i) {
        std::cout << "o";  // ball
      } else if (player1x == j && player1y == i) {
        std::cout << "\xDB";  // player1
      } else if (player2x == j && player2y == i) {
        std::cout << "\xDB";  // player2
      } else if (player1x == j && player1y + 1 == i) {
        std::cout << "\xDB";  // player1
      } else if (player1x == j && player1y + 2 == i) {
        std::cout << "\xDB";  // player1
      } else if (player1x == j && player1y + 3 == i) {
        std::cout << "\xDB";  // player1
      } else if (player2x == j && player2y + 1 == i) {
        std::cout << "\xDB";  // player1
      } else if (player2x == j && player2y + 2 == i) {
        std::cout << "\xDB";  // player1
      } else if (player2x == j && player2y + 3 == i) {
        std::cout << "\xDB";  // player1
      } else {
        std::cout << " ";
      }
      if (j == width_ - 1) {
        std::cout << "\xB2";
      }
    }
    std::cout << std::endl;
  }

  for (int i = 0; i < width_ + 2; i++) {
    std::cout << "\xB2";
  }
  std::cout << std::endl;

  std::cout << "Score 1: " << score1_ << std::endl
            << "Score 2: " << score2_ << std::endl;
  std::this_thread::sleep_for(std::chrono::milliseconds(70));
  return true;
}

bool ConsoleGamePong::Input() {
  ball_ptr_->Move();

  if (_kbhit()) {
#ifdef _WIN32
    char current = _getch();
#else
#ifdef __linux__
    char current = static_cast<char>(getchar());
#endif
#endif

    if (current == up1_) {
      if (player1_ptr_->GetY() > 0) {
        player1_ptr_->MoveUp();
      }
    }
    if (current == up2_) {
      if (player2_ptr_->GetY() > 0) {
        player2_ptr_->MoveUp();
      }
    }
    if (current == down1_) {
      if (player1_ptr_->GetY() + 4 < height_) {
        player1_ptr_->MoveDown();
      }
    }
    if (current == down2_) {
      if (player2_ptr_->GetY() + 4 < height_) {
        player2_ptr_->MoveDown();
      }
    }

    if (ball_ptr_->GetDirection() == STOP) {
      ball_ptr_->RandomDirection();
    }

    if (current == 'x') {
      game_over_ = true;
    }
  }
  return true;
}

bool ConsoleGamePong::Logic() {
  for (int i = 0; i < 4; i++) {
    if (ball_ptr_->GetX() == player1_ptr_->GetX() + 1) {
      if (ball_ptr_->GetY() == player1_ptr_->GetY() + i) {
        ball_ptr_->ChangeDirection(static_cast<eDir>((rand() % 3) + 4));
      }
    }
  }
  // right paddle
  for (int i = 0; i < 4; i++) {
    if (ball_ptr_->GetX() == player2_ptr_->GetX() - 1) {
      if (ball_ptr_->GetY() == player2_ptr_->GetY() + i) {
        ball_ptr_->ChangeDirection(static_cast<eDir>((rand() % 3) + 1));
      }
    }
  }
  // bottom wall
  if (ball_ptr_->GetY() == height_ - 1) {
    ball_ptr_->ChangeDirection(ball_ptr_->GetDirection() == DOWNRIGHT ? UPRIGHT
                                                                      : UPLEFT);
  }
  // top wall
  if (ball_ptr_->GetY() == 0) {
    ball_ptr_->ChangeDirection(ball_ptr_->GetDirection() == UPRIGHT ? DOWNRIGHT
                                                                    : DOWNLEFT);
  }
  // right wall
  if (ball_ptr_->GetX() == width_ - 1) {
    ScoreUp(player1_ptr_);
  }
  // left wall
  if (ball_ptr_->GetX() == 0) {
    ScoreUp(player2_ptr_);
  }
  return true;
}

void ConsoleGamePong::ScoreUp(const std::shared_ptr<Paddle>& p) {
  if (p.get() == player1_ptr_.get())
    score1_++;
  else if (p.get() == player2_ptr_.get())
    score2_++;

  ball_ptr_->Reset();
  player1_ptr_->Reset();
  player2_ptr_->Reset();
}
