
#include "S-snakeMain.h"

namespace s21 {
const SnakeGame* gameInstanceKeeper() {
  static SnakeGame game;
  if(game.getGameState()==SnakeGame::st_Moving)
    game.catchUpMovement();
  if(game.getGameState()==SnakeGame::st_Exit)
    return nullptr;
  return &game;
}
}  // namespace s21
