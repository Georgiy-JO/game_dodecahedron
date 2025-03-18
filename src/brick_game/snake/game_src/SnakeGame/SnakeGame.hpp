#pragma once
#include <fstream>

#include "../field_/field_.hpp"
#include "../timer_/timer_.hpp"

namespace s21 {

class SnakeGame {
 public:
  enum Game_t { Standart_snake, Borderless_snake };
  enum GameState_t {
    st_Exit = -1,
    // st_Start,
    st_Moving,
    // st_Turn,
    // st_Eat,
    st_GameOver,
    // st_Message,
    st_Pause,
    // st_BorderTransfort
  };
  enum UserActions_t {
    ac_Start,
    ac_Esc,
    ac_Pause,
    ac_Right,
    ac_Left,
    ac_Forvard
  };

 private:
  static constexpr const char* save_file = "saves/high_score_s-snake.txt";
  static constexpr int SPEEDSTEP = 5;

  timer_ timer;

  field_ field;
  int score = 0;
  int record_score;
  char game_type;
  GameState_t game_state = st_Moving;

 public:
  SnakeGame(char type=Standart_snake);

  void inputRecordScore();
  void saveRecordScore() const;
  std::string setRecordName() const;
  u_int getSpeed() const;
  void updateScoreSpeed();

  void gameReStart();
  void gamePause();
  void gameContinue();
  void gameOver();
  void moving();
  void catchUpMovement();
  void userActionHandler(int action);
  int getGameState() const;
  int getScore() const;
  int getRecordScore() const;
  int getField(int x, int y) const;
};
}  // namespace s21