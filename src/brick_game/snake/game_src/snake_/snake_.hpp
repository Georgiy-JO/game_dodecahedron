#pragma once

#include <deque>

#include "../service.hpp"

namespace s21 {
class snake_ {
 public:
  enum Directions { Up, Right, Down, Left };
  using node_ = std::pair<int, int>;

 private:
  std::deque<node_> nodes;
  int direction = Down;

 public:
  snake_();
  snake_(int x_begining, int y_begining);
  u_int getSize() const;
  node_ operator[](u_int index) const;
  void snakeMove();
  void changeDirection(int change);
  void snakeGrow();
  node_ getHead() const;
  int getDirection() const;
  void reset(int x_begining, int y_begining);
  bool selfCrash() const;
};
}  // namespace s21