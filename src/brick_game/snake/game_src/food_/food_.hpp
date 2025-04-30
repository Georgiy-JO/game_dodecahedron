#pragma once

#include "../service.hpp"

namespace s21 {
class food_ {
 private:
  coords_t position;
  const int val;

 public:
  food_(int V = 0);
  food_(u_int x, u_int y, int V = 0);

  void setPosition(u_int x, u_int y);
  coords_t getPosition() const;
  int getValue() const;
};

class insect_ : public food_ {
 private:
  static constexpr int VALUE = 1;

 public:
  insect_();
  insect_(u_int x, u_int y);
};

class mouse_ : public food_ {
 private:
  static constexpr int VALUE = 2;

 public:
  mouse_();
  mouse_(u_int x, u_int y);
};
}  // namespace s21