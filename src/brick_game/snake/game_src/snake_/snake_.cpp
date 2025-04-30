
#include "snake_.hpp"

namespace s21 {
snake_::snake_() {
  for (int i = 0; i < 4; i++) {
    nodes.push_back(node_(0, i));
  }
}
snake_::snake_(int x_begining, int y_begining) {
  reset(x_begining, y_begining);
}
u_int snake_::getSize() const { return nodes.size(); }
snake_::node_ snake_::operator[](u_int index) const {
  if (index >= getSize()) throw OutOfRangeError();
  return nodes[index];
}
void snake_::snakeMove() {
  snakeGrow();
  nodes.pop_back();
}
void snake_::snakeGrow() {
  switch (direction) {
    case Up:
      nodes.push_front(node_(nodes[0].first, nodes[0].second - 1));
      break;
    case Down:
      nodes.push_front(node_(nodes[0].first, nodes[0].second + 1));
      break;
    case Right:
      nodes.push_front(node_(nodes[0].first + 1, nodes[0].second));
      break;
    case Left:
      nodes.push_front(node_(nodes[0].first - 1, nodes[0].second));
      break;
  }
}
void snake_::changeDirection(int change) {
  int flag = (change == Left || change == Right) ? (change - 2) : 0;
  if (flag) {
    direction -= flag;
    if (direction < 0) direction = 3;
    if (direction > 3) direction = 0;
  } else
    throw InputError();  // catch me
}
snake_::node_ snake_::getHead() const { return (coords_t)nodes[0]; }
int snake_::getDirection() const { return direction; }
void snake_::reset(int x_begining, int y_begining) {
  nodes.clear();
  for (int i = 0; i < 4; i++) {
    nodes.push_back(node_(x_begining, y_begining - i));
  }
  direction = Down;
}
bool snake_::selfCrash() const {
  bool flag = 0;
  u_int size = getSize();
  for (u_int i = 1; !flag && i < size; i++) {
    if (nodes[0].first == nodes[i].first && nodes[0].second == nodes[i].second)
      flag = 1;
  }
  return flag;
}

}  // namespace s21