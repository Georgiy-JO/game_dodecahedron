
#include "S-snakeMain.hpp"

namespace s21 {
SnakeGame* gameInstanceKeeper() {
  static SnakeGame game;
  if (game.getGameState() == SnakeGame::st_Moving) game.catchUpMovement();
  return &game;
}
}  // namespace s21
