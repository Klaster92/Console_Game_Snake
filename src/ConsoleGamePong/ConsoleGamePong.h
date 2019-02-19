#ifndef SRC_CONSOLEGAMEPONG_H
#define SRC_CONSOLEGAMEPONG_H
#include "../ConsoleGameBase.h"

#include <iostream>
#include <memory>

enum eDir {
  STOP = 0,
  LEFT = 1,
  UPLEFT = 2,
  DOWNLEFT = 3,
  RIGHT = 4,
  UPRIGHT = 5,
  DOWNRIGHT = 6
};

class Ball {
 public:
  Ball();
  void Setup(int x_external, int y_external);
  void Reset();
  void ChangeDirection(const eDir& d);
  void RandomDirection();
  inline int GetX() const;
  inline int GetY() const;
  inline eDir GetDirection() const;
  void Move();

 private:
  int x_, y_;
  int original_x_, original_y_;
  eDir direction_;
};

class Paddle {
 public:
  Paddle();
  Paddle(int posX, int posY);
  void Setup(int posX, int posY);
  inline void Reset();
  inline int GetX() const;
  inline int GetY() const;
  inline void MoveUp();
  inline void MoveDown();

 private:
  int x_, y_;
  int original_x_, original_y_;
};

class ConsoleGamePong : public ConsoleGameBase {
 public:
  ConsoleGamePong();
  virtual ~ConsoleGamePong();

  virtual bool Control();
  virtual bool Setup(int w, int h);
  virtual bool Draw();
  virtual bool Input();
  virtual bool Logic();

  void ScoreUp(const std::shared_ptr<Paddle>&);

 private:
  int score1_, score2_;
  char up1_, down1_, up2_, down2_;
  std::shared_ptr<Ball> ball_ptr_;
  std::shared_ptr<Paddle> player1_ptr_;
  std::shared_ptr<Paddle> player2_ptr_;
};
#endif
