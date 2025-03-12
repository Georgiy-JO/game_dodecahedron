
#include "SnakeGame/SnakeGame.hpp"


namespace s21 {
SnakeGame& gameInstanceKeeper(){
  static SnakeGame game;
  game.catchUpMovement();
  return game;
}
}


