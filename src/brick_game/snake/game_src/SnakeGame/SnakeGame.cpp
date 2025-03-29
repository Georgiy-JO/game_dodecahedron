

#include "SnakeGame.hpp"
namespace s21 {
SnakeGame::SnakeGame(char type) :  field(), game_type(type) { inputRecordScore(); }
SnakeGame::~SnakeGame(){
  std::ifstream file(save_file);
  if( file.good())
    gameOver();
}
void SnakeGame::inputRecordScore() {
  std::ifstream ifs;
  ifs.open(save_file);
  if (!ifs.is_open()) throw FileOpenError();  // chatch me
  std::string leader("nan");                       // Vsauce 123
  int leader_score=0;
  ifs >> leader >> leader_score;
  ifs.close();
  record_score = leader_score;
}
void SnakeGame::saveRecordScore() const {
  std::ifstream ifs(save_file);
  const char* temp_file = "saves/tmp.txt";
  std::ofstream ofs(temp_file);
  if (!ifs.is_open()) throw FileOpenError();  // chatch me
  if (!ofs.is_open()) throw FileOpenError();  // chatch me
  std::string leader("nan"), new_name("nan");
  int leader_score=0;
  int counter = 5;
  bool flag=0;
  while (!ifs.eof() && counter  > 0) {
    ifs >> leader >> leader_score;
    if (!flag &&leader_score < score) {
      flag=1;
      new_name = setRecordName();
      ofs << new_name << " " << score << std::endl;
      counter--;
    }
    if (counter && leader != new_name)
      ofs << leader << " " << leader_score << std::endl;
    counter--;
  }
  if(counter  > 0 && !flag)    
    ofs <<setRecordName()<< " " << score << std::endl;
  
  ifs.close();
  ofs.close();
  std::remove(save_file);
  std::rename(temp_file, save_file);
}
std::string SnakeGame::setRecordName() const {
  // update in better version for github
  return "user_1";
}
void SnakeGame::updateScoreSpeed() {
  score += field.getFoodValue();  // different score for different types of food
  if (score / SPEEDSTEP >= timer.getSpeed()+1) {
    timer.updateSpeed();
  }
  if (score >= record_score) record_score = score;
}
void SnakeGame::moving() {
  if (field.moveSnake()) game_state=st_Eat;
  if(game_state==st_Eat) gameEatingUpdate();    //just  for the sake of FSM
  if (field.checkForCrach()) gameOver();
  if (score >= 200) gameOver();
}
void SnakeGame::gameEatingUpdate(){
  updateScoreSpeed(); 
  field.spawnFood();
  game_state=st_Moving; 
}
u_int SnakeGame::getSpeed() const { return timer.getSpeed() + 1; }
void SnakeGame::catchUpMovement() {
  if (game_state == st_Moving) {
    u_int move_number = timer.getMovesNumber();
    for (u_int i = 0; i < move_number; i++) {
      moving();
    }
  }
}
void SnakeGame::userActionHandler(int action) {
  switch (action) {
    case ac_Start:
      if (game_state == st_GameOver)        gameReStart();
      else if (game_state == st_Pause)        gameContinue();
      break;
    case ac_Esc:
      if (game_state == st_Moving || game_state == st_Pause) gameOver();
      else if (game_state == st_GameOver) game_state = st_Exit;  // handle
      break;
    case ac_Pause:
      if (game_state == st_Moving) gamePause();
      else if (game_state == st_Pause) gameContinue();
      break;
    case ac_Right:
      if (game_state == st_Moving) {
        field.snakeTurnRight();
        manualMove();
      }
      break;
    case ac_Left:
      if (game_state == st_Moving) {
        field.snakeTurnLeft();
        manualMove();
      }
      break;
    case ac_Forvard:
      if (game_state == st_Moving)
        manualMove();  // manage the pressing of the button
      break;
    default:
      throw InputError();  // catch me
      break;
  }
}
void SnakeGame::manualMove() {
  moving();
  timer.reset();  
}
void SnakeGame::gameReStart() {
  field.reset();
  timer.totalReset();
  score = 0;
  inputRecordScore();
  game_state = st_Moving;
}
void SnakeGame::gameOver() {
  saveRecordScore();
  game_state = st_GameOver;  // leaks here??
}
void SnakeGame::gamePause() { game_state = st_Pause; }
void SnakeGame::gameContinue() {
  game_state = st_Moving;
  timer.reset();
}
int SnakeGame::getGameState() const{
  return game_state;
}
int SnakeGame::getScore() const{
  return score;
}
int SnakeGame::getRecordScore() const{
  return record_score;
}
int SnakeGame::getField(int x, int y) const{
  return field(x,y);
}

}  // namespace s21