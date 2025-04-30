
#include "randGen_.hpp"

namespace s21 {

randGen_::randGen_(u_int WIDTH_, u_int HEIGHT_)
    : mt(std::chrono::steady_clock::now().time_since_epoch().count()),
      x_dist(0, WIDTH_ - 1),
      y_dist(0, HEIGHT_ - 1),
      binary(0, binary_kind_chance - 1) {}
u_int randGen_::getX() { return x_dist(mt); }
u_int randGen_::getY() { return y_dist(mt); }
char randGen_::getBinary() { return (binary(mt) == 0) ? 1 : 0; }

}  // namespace s21