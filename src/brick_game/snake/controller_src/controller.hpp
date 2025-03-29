#pragma once

#include "../s-snake.h"
#include "../game_src/S-snakeMain.hpp"

template <typename Callable>
GameInfo_t gameInterector (Callable&& gameOperation);

void  gameUpdater(GameInfo_t& game_output);
void gameInput(UserAction_t action, bool hold);

int**& outputFieldKeeper();
int** fieldAllocator();
void fieldDeleter();
void fieldReallocator();

void endGame(GameInfo_t& game_output);
