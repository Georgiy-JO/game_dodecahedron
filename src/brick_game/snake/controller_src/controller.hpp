#pragma once

#include "../game_src/S-snakeMain.hpp"
#include "../s-snake.h"

/**
 * @brief Executes a given game operation and returns the resulting game
 * information in the GameInfo_t form.
 *
 * @note Basically is a wrapper for another functions that is passed to it. Is
 * needed for errorrs handling.
 * @tparam Callable A callable object (e.g., lambda, function pointer, functor)
 * that performs a game operation.
 * @param gameOperation The callable that will be executed.
 *      In this particular version it is either gameUpdater(...) or
 * gameInput(...).
 * @return GameInfo_t The resulting game state and data after executing the
 * operation (game parameters for the UI).
 */
template <typename Callable>
GameInfo_t gameInterector(Callable&& gameOperation);
/**
 * @brief Updates the game (perform timer related movement etc.),
 *      transforms and writes data to the parameter as GameInfo_t.
 * @param game_output A reference to the GameInfo_t structure that will be
 * updated.
 */
void gameUpdater(GameInfo_t& game_output);
/**
 * @brief Processes user input for controlling the game into business logic
 * understandable terms.
 *
 * @param action The user action to be handled.
 * @param hold If true, indicates the action is being held; otherwise, it's a
 * single press (not used).
 */
void gameInput(UserAction_t action, bool hold);

/**
 * @brief Keeps and provides access to the field output buffer (part of
 * GameInfo_t).
 *
 * @return A reference to a pointer to the 2D int array representing the game
 * field.
 */
int**& outputFieldKeeper();
/**
 * @brief Allocates memory for the game field (2D array).
 *
 * @return Pointer to the newly allocated 2D int array.
 */
int** fieldAllocator();
/**
 * @brief Deallocates memory used by the game field.
 */
void fieldDeleter();
/**
 * @brief Reallocates the field memory, cleaning and preparing it for reuse.
 */
void fieldReallocator();

/**
 * @brief Used in case of the final end (user wants to exit) of the game
 *      and updates the output GameInfo_t accordingly.
 *
 * @param game_output A reference to the GameInfo_t structure that keeps game
 * parameters for UI.
 */
void endGame(GameInfo_t& game_output);
