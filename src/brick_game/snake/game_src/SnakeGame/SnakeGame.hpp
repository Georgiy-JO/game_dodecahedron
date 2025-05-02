#pragma once
#include <fstream>

#include "../field_/field_.hpp"
#include "../timer_/timer_.hpp"

namespace s21 {
/**
 * @brief Main class that manages the Snake game logic, game state, and user
 * interaction.
 */
class SnakeGame {
 public:
  /**
   * @enum Game_t
   * @brief Types of Snake game modes.
   * @note Is not used in current game version. Waiting for update.
   */
  enum Game_t {
    Standart_snake,   ///< Classic snake with borders.
    Borderless_snake  ///< Snake wraps around the screen.
  };

  /**
   * @enum GameState_t
   * @brief Represents different states the game can be in. FSM implementation.
   */
  enum GameState_t {
    st_Exit = -1,  ///< Game is over and user want to exit game window.
    st_Moving,     ///< Snake is moving (main state).
    st_Eat,        ///< Snake has eaten food.
    st_GameOver,   ///< Game over state (game ended with snake crash).
    st_GameWon,    ///< Winning state(game ended with snake filling the field).
    st_Pause       ///< Game is paused.
  };

  /**
   * @enum UserActions_t
   * @brief Defines user input.
   */
  enum UserActions_t {
    ac_Start,   ///< Start input signal.
    ac_Esc,     ///< Exit input signal.
    ac_Pause,   ///< Pause input signal.
    ac_Right,   ///< Turn right input signal.
    ac_Left,    ///< Turn left input signal.
    ac_Forvard  ///< Move forward input signal.
  };

 private:
  /**
   * @brief Path to the file used for saving the high score.
   */
  static constexpr const char* save_file = "saves/high_score_s-snake.txt";
  /**
   * @brief Score step that affects game speed increase.
   */
  static constexpr int SPEEDSTEP = 5;

  timer_ timer;      ///< Timer controlling game speed and events.
  field_ field;      ///< Game field with snake and food.
  int score = 0;     ///< Current player score.
  int record_score;  ///< Highest score.
  char game_type;    ///< Current game type (from Game_t). Not used in current
                     ///< version.
  GameState_t game_state = st_Moving;  ///< Current game state.

 public:
  /**
   * @brief Constructor for a SnakeGame instance.
   * @param type Type of the game mode (default - Game_t::Standart_snake).
   */
  SnakeGame(char type = Standart_snake);
  /**
   * @brief Destructor for a SnakeGame instance.
   */
  ~SnakeGame();

  /**
   * @brief Loads the previously saved high score from the file (save_file).
   */
  void inputRecordScore();
  /**
   * @brief Saves the current high score to the file (save_file).
   */
  void saveRecordScore() const;

  /**
   * @brief Gets the current game speed.
   * @return Game speed as an unsigned integer.
   */
  u_int getSpeed() const;
  /**
   * @brief Updates the score and if needed increases game speed.
   */
  void updateScoreSpeed();
  /**
   * @brief Updates the game parameters (like speed and score) and spawns new
   * food after the snake eats food.
   */
  void gameEatingUpdate();
  /**
   * @brief Forces a single manual movement of the snake.
   */
  void manualMove();

  /**
   * @brief Restarts the game.
   */
  void gameReStart();
  /**
   * @brief Pauses the game.
   */
  void gamePause();
  /**
   * @brief Resumes the game from pause.
   */
  void gameContinue();
  /**
   * @brief Ends the game.
   * @param status True if game is won, false if game is over with crash.
   */
  void gameOver(bool status = false);

  /**
   * @brief The main game cicle function (FSM).
   */
  void moving();
  /**
   * @brief Performs moves if enough time has passed (timer-based).
   */
  void catchUpMovement();
  /**
   * @brief Processes user input actions.
   * @param action Integer representing a user action (UserActions_t).
   */
  void userActionHandler(int action);

  /**
   * @brief Returns the current game state.
   * @return Integer representing the GameState_t.
   */
  int getGameState() const;
  /**
   * @brief Returns the current score.
   * @return Current score as an integer.
   */
  int getScore() const;
  /**
   * @brief Returns the highest score from the game (does not inc files).
   * @return High score as an integer.
   */
  int getRecordScore() const;
  /**
   * @brief Gets the value at a specific field cell.
   * @param x Horizontal position.
   * @param y Vertical position.
   * @return Integer representing the field content at (x, y).
   */
  int getField(int x, int y) const;
};

}  // namespace s21