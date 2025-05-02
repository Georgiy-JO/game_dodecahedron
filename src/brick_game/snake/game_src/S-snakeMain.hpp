#pragma once
#include "SnakeGame/SnakeGame.hpp"

namespace s21 {
/**
 * @note Creats and keeps the SnakeGame object - all the game data.
 * @return SnakeGame Pointer to SnakeGame object keeping all the game data.
 */
SnakeGame* gameInstanceKeeper();
}  // namespace s21
