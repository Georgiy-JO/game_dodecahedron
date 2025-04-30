
#include "field_.hpp"
namespace s21 {
field_::field_()
    : snake(WIDTH / 2, HEIGHT / 2 + 2), food(nullptr), rand_gen(WIDTH, HEIGHT) {
  spawnFood();
}
void field_::spawnFood() {  // this must be chacked with the borderless snake:
                            // too big snake
  if (isFieldFull())
    food = std::make_unique<food_>();
  else {
    u_int x, y, binary = rand_gen.getBinary();

    u_int snake_size = snake.getSize();
    int flag = 1;

    while (flag) {
      flag = 0;
      x = rand_gen.getX();
      y = rand_gen.getY();
      for (u_int i = 0; !flag && i < snake_size; i++) {
        if ((int)x == (int)snake[i].first && (int)y == snake[i].second)
          flag = 1;
      }
    }
    if (binary)
      food = std::make_unique<mouse_>(x, y);
    else
      food = std::make_unique<insect_>(x, y);
  }
}
bool field_::checkForFood() const {
  auto next_step = snake.getHead();
  switch (snake.getDirection()) {
    case snake_::Up:
      next_step.second--;
      break;
    case snake_::Down:
      next_step.second++;
      break;
    case snake_::Right:
      next_step.first++;
      break;
    case snake_::Left:
      next_step.first--;
      break;
  }
  return food->getValue() && next_step == (snake_::node_)food->getPosition();
}
bool field_::checkForCrash() const {
  bool flag = (snake[0].first < 0 || snake[0].first >= WIDTH ||
               snake[0].second < 0 || snake[0].second >= HEIGHT)
                  ? 1
                  : 0;
  flag = flag || snake.selfCrash();
  return flag;
}
bool field_::moveSnake() {
  bool have_ate = 0;
  if (checkForFood()) {
    snake.snakeGrow();
    have_ate = true;
  } else
    snake.snakeMove();
  return have_ate;
}
int field_::getFoodValue() const { return food->getValue(); }
void field_::snakeTurnRight() { snake.changeDirection(snake.Right); }
void field_::snakeTurnLeft() { snake.changeDirection(snake.Left); }
void field_::reset() {
  snake.reset(WIDTH / 2, HEIGHT / 2 + 2);
  spawnFood();
}
int field_::operator()(int x, int y) const {
  int output = 0;
  if (x < 0 || y < 0 || x >= WIDTH || y >= HEIGHT)
    output = -1;
  else {
    int tmp = snake.getSize();
    snake_::node_ temp(x, y);
    for (int i = 0; !output && i < tmp; i++) {
      if (temp == snake[i]) output = 1;
    }
    if (!output && food->getValue()) {
      if (coords_t(x, y) == food->getPosition()) output = food->getValue() + 1;
    }
  }
  return output;
}

bool field_::isFieldFull() const { return snake.getSize() == HEIGHT * WIDTH; }

}  // namespace s21
