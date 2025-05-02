#ifndef S_SNAKE_H
#define S_SNAKE_H

/**
 * @note Enables compatibility with C++ compilers by using C linkage.
 */
#ifdef __cplusplus
extern "C" {
#endif

/**
 * @enum FieldSize_c
 * @brief Constants for main and second fields dimensions and relative sizes.
 * Standart structure.
 * @note `Second_*` values are unused in this game.
 */
typedef enum {
  RelativeSize = 0,        /**< Default relative size. */
  Width = 10,              /**< Width of the field in blocks. */
  Height = 20,             /**< Height of the field in blocks. */
  Second_RelativeSize = 0, /**< Not used in this game. */
  Second_Width = 0,        /**< Not used in this game. */
  Second_Height = 0        /**< Not used in this game. */
} FieldSize_c;

/**
 * @struct GameInfo_t
 * @brief Structure holding game data in the form that UI understands.
 */
typedef struct {
  int **field;    /**< Pointer to current game field (2D array). */
  int **next;     /**< Second field (Not used in this game). */
  int score;      /**< Current score of the player. */
  int high_score; /**< Highest score achieved. */
  int level;      /**< Current level. */
  int speed;      /**< Has the same values as level + handls winning.  */
  int pause;      /**< Pause state flag (1 = paused, 0 = running). */
} GameInfo_t;

/**
 * @enum UserAction_t
 * @brief Represents possible user input actions.
 * @note This actions is translated by the controller into game inside logic
 * actions (UserActions_t).
 */
typedef enum {
  Start,     /**< Press start the game (used to start or resume the game). */
  Pause,     /**< Press pause/unpause the game. */
  Terminate, /**< Press end the game (if double press - exits the game). */
  Left,      /**< Press left (used to turn the snake left). */
  Right,     /**< Press right (used to turn the snake right). */
  Up,        /**< Press up (used to speed up the snake). */
  Down,      /**< Press down (Not used in this game). */
  Action     /**< Press action button (used to speed up the snake).. */
} UserAction_t;

/**
 * @brief Updates and returns the current game data in GameInfo_t form.
 * @return GameInfo_t The state of the game.
 */
GameInfo_t updateCurrentState();

/**
 * @brief Processes user input action.
 * @param action The user input action.
 * @param hold Whether the action is held (true) or tapped (false) - not used.
 */
void userInput(UserAction_t action, bool hold);

#ifdef __cplusplus
}
#endif

#endif  // S_SNAKE_H
