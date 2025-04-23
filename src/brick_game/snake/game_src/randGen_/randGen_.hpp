#pragma once

#include <chrono>
#include <random>

namespace s21 {
class randGen_ {
 private:
  static constexpr int binary_kind_chance=5;
  std::mt19937 mt;
  std::uniform_int_distribution<u_int> x_dist;
  std::uniform_int_distribution<u_int> y_dist;
  std::uniform_int_distribution<char> binary;

 public:
  randGen_(u_int WIDTH_, u_int HEIGHT_);
  u_int getX();
  u_int getY();
  char getBinary();
};
}  // namespace s21