#pragma once

#include <memory>

#include "../food_/food_.hpp"
#include "../randGen_/randGen_.hpp"
#include "../snake_/snake_.hpp"

namespace s21 {
class field_ {
 public:
  static constexpr int WIDTH = 10;
  static constexpr int HEIGHT = 20;

 private:
  snake_ snake;
  std::unique_ptr<food_> food;

  randGen_ rand_gen;

 public:
  field_();

  void spawnFood();
  bool checkForFood() const;   // check if will happen
  bool checkForCrach() const;  // check if hammened
  bool moveSnake();
  void snakeTurnRight();
  void snakeTurnLeft();
  int getFoodValue() const;
  void reset();
  int operator()(int x,int y) const;
};
}  // namespace s21