#pragma once
#include <fstream>

#include "../field_/field_.hpp"
#include "../timer_/timer_.hpp"

namespace s21 {

class SnakeGame{
    public:
      enum Game_t {
          Standart_snake,
          Borderless_snake
      };
      enum GameState_t {
          st_Exit=-1,
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
      static constexpr const char* save_file = "saves/high_score_snake.txt";
      static constexpr int SPEEDSTEP = 5;
  
      timer_ timer;
  
      field_ field;
      int score =0;
      int record_score;
      char game_type=Standart_snake;
      GameState_t game_state=st_Moving;
  
    public:
      SnakeGame();
      SnakeGame(char type);
  
      void inputRecordScore();
      void saveRecordScore();
      std::string saveNewRecord();
      u_int getSpeed();
      void updateScoreSpeed();
  
      void gameReStart();
      void gamePause();
      void gameContinue();
      void gameOver();
      void moving();
      void catchUpMovement();
      void userActionHandler(int action);
  
  };

}