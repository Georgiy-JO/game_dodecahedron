#include <iostream>
#include <fstream>    //SnakeGame
#include <vector>     // snake_
#include <random>     // RandomGenerator_
#include <chrono>     // RandomGenerator_  SnakeTimer_
#include <memory>     // feild_

namespace s21 {

using u_int=unsigned int;
using coords_t = std::pair <u_int, u_int>;


class RandomGenerator_{
  private:
    std::mt19937 mt;
    std::uniform_int_distribution<u_int> x_dist;
    std::uniform_int_distribution<u_int> y_dist;
    std::uniform_int_distribution<char> bynary;
  public:
    RandomGenerator_(u_int WIDTH_, u_int HEIGHT_);
    std::mt19937 getMT();
    u_int getX();
    u_int getY();
    char getBinary();
};

class SnakeTimer_{
  public:
    static constexpr int MAX_SPEED = 9; //from 0 to 9 - 10 speeds
  private:
    static constexpr u_int SPEED_TO_INTERVAL [10]={1,2,3,4,5,6,7,8,9,10};

    using clock = std::chrono::steady_clock;
    clock::time_point startTime;
    clock::time_point lastUpdate;

    int speed=0;
    
    u_int getInterval();
  public:
  SnakeTimer_();

  void setSpeed(int speed);
  void updateSpeed();
  int getSpeed();
  u_int getMovesNumber();
  void reset();
};


class SnakeError_ : public std::exception {
  std::string msg;
public:
  SnakeError_ (const char* error = "Unknown error."):msg(error){}
  SnakeError_ (const SnakeError_& other):msg(other.msg){}
  const char* what() const noexcept override {return msg.c_str();}
};
class FileOpenError : public SnakeError_{
public:
FileOpenError(const char* error = "File was not open or can't be found."): SnakeError_(error){}
};
class InputError: public SnakeError_{
public:
InputError(const char* error = "User input error."): SnakeError_(error){}
};




class snake_ {
  public:
    enum Directions { 
        Up,
        Right,
        Down,
        Left};
    using node_=std::pair <int, int>;
  private:
    std::vector<node_> nodes;
    int direction=Down;
  public:
    snake_();
    snake_(int x_begining, int y_begining);
    u_int snakeSize();
    node_ operator [](u_int index);
    void snakeMove ();
    void changeDirection(int change);
    void snakeGrow();
    coords_t getHead();
    int getDirection();
};

class food_{
  protected:
    coords_t position;
  public:
    food_():position(0,0){}
    food_(u_int x, u_int y):position(x,y){}
    virtual ~food_() {}

    void setPosition(u_int x, u_int y);
    coords_t getPosition();
};

class insect_: public food_{
    public:
      static constexpr int VALUE =1;
      insect_():food_(){}
      insect_(u_int x, u_int y):food_(x,y){}
};

class mouse_:public food_{
    public:
      static constexpr int VALUE =2;
      mouse_():food_(){}
      mouse_(u_int x, u_int y):food_(x,y){}
};

class field_ {
  public:
    static constexpr int WIDTH = 10;
    static constexpr int HEIGHT = 20;
  private:
    snake_ snake;
    std::unique_ptr<food_> food;

    RandomGenerator_ rand_gen;
  public:
    field_();

    void spawnFood();
    bool checkForFood();  //check if will happen
    bool checkForCrach(); //check if hammened
    void moveSnake ();
};

class SnakeGame{
  public:
    enum Game_t {
        Standart_snake,
        Borderless_snake
    };
    enum GameState_t {
        st_Exit=-1,
        st_Start,
        st_Moving,
        st_Turn,
        st_Eat,
        st_GameOver,
        st_Message,
        st_Pause,
        st_BorderTransfort
    };
  private:
    static constexpr char* save_file = "saves/high_score_snake.txt";
    static constexpr int SPEEDSTEP = 5;

    field_ field;
    // int speed=1;
    int score =0;
    int record_score;
    char game_type=Standart_snake;
    GameState_t game_state=st_Start;

  public:
    SnakeGame():field(), record_score(inputRecordScore()){}
    SnakeGame(char type):SnakeGame() {game_type=type;}

    const int inputRecordScore();
    void saveRecordScore();
    std::string saveNewRecord();

    void gameStart();
    void gamePause();
    void gameOver();
    void moving();
    void updateScoreSpeed();

};












// snake_ functions
snake_::snake_(){
    for(int i=0;i<4;i++){
        nodes.push_back(node_(0,i));
    }
}
snake_::snake_(int x_begining, int y_begining){
    for(int i=0;i<4;i++){
        nodes.push_back(node_(x_begining-i,y_begining));
    } 
}
u_int snake_::snakeSize(){
  return nodes.size();
}
snake_::node_ snake_::operator [](u_int index){
  return nodes[index];
}
void snake_::snakeMove (){
  u_int x_tmp=nodes[0].first, y_tmp=nodes[0].second;
  switch (direction){
    case Up:
      nodes[0].second--;
      break;
    case Down:
      nodes[0].second++;
      break;
    case Right:
      nodes[0].first++;
      break;
    case Left:
      nodes[0].first--;
      break;
  }

  for(int i=nodes.size()-1;i>1;i--){
    nodes[i].first=nodes[i-1].first;
    nodes[i].second=nodes[i-1].second;
  }
  nodes[1].first=x_tmp;
  nodes[1].second=y_tmp;
}
void snake_::snakeGrow(){
  switch (direction){
    case Up:
      nodes.insert(nodes.begin(),node_(nodes[0].first,nodes[0].second--));
      break;
    case Down:
      nodes.insert(nodes.begin(),node_(nodes[0].first,nodes[0].second++));
      break;
    case Right:
      nodes.insert(nodes.begin(),node_(nodes[0].first++,nodes[0].second));
      break;
    case Left:
      nodes.insert(nodes.begin(),node_(nodes[0].first--,nodes[0].second));
      break;
  }
}
void snake_::changeDirection(int change){
  int flag=(change==Left ||change==Right)?(change-2):0;
  if(flag){
    direction-=flag;
    if(direction<0)
      direction=3;
    if(direction>3)
      direction=0;
  }
  else
    throw InputError ();            // catch me
}
coords_t snake_::getHead(){
  return (coords_t) nodes[0]; 
}
int snake_::getDirection(){
  return direction;
}

// RandomGenerator_ functions
RandomGenerator_::RandomGenerator_(u_int WIDTH_, u_int HEIGHT_):mt(std::chrono::steady_clock::now().time_since_epoch().count()), x_dist(0, WIDTH_-1), y_dist(0, HEIGHT_-1), bynary(0,1){}
std::mt19937 RandomGenerator_::getMT(){
  return mt;
}
u_int RandomGenerator_::getX(){
  return x_dist(mt);
}
u_int RandomGenerator_::getY(){
  return y_dist(mt);
}
char RandomGenerator_::getBinary(){
  return bynary(mt);
}

// SnakeTimer_ functions
SnakeTimer_::SnakeTimer_(){}
u_int SnakeTimer_::getInterval(){}
void SnakeTimer_::setSpeed(int speed){}
void SnakeTimer_::updateSpeed(){}
int SnakeTimer_::getSpeed(){}
u_int SnakeTimer_::getMovesNumber(){}
void SnakeTimer_::reset(){}

// field_ functions
field_::field_():snake(WIDTH/2, HEIGHT/2+2), rand_gen(WIDTH, HEIGHT), food(nullptr){ spawnFood();}
void field_::spawnFood(){
  u_int x, y, bynary=rand_gen.getBinary();
  while(1){
    x = rand_gen.getX();
    y= rand_gen.getY();
    for(int i=0;i< snake.snakeSize();i++){
      if(x==snake[i].first || y==snake[i].second)
        continue;
      break;
    }
  }
  if(bynary)
    food=std::make_unique<mouse_>(x,y);
  else
    food=std::make_unique<insect_>(x,y);
  // food->setPosition(x,y);
}
bool field_::checkForFood(){
  coords_t next_step=snake.getHead();
  switch (snake.getDirection()){
    case snake_::Up:
      next_step.second--;
      break;
    case snake_::Down:
      next_step.second++;
      break;
    case snake_::Right:
      next_step.first++;
      break;
    case snake_::Left:
      next_step.first--;
      break;
  }
  return (next_step==food->getPosition())?true:false;
}
bool field_::checkForCrach(){
  bool flag=(snake[0].first<0 || snake[0].first>=WIDTH || snake[0].second<0||snake[0].second>=HEIGHT)?1:0;
  for(unsigned int i=0;!flag &&i<snake.snakeSize();i++){
    if(snake[0].first==snake[i].first && snake[0].second==snake[i].second)
      flag=1;
  }
}
void field_::moveSnake (){
  snake.snakeMove();
}

// food_ functions
void food_::setPosition(u_int x, u_int y){position=std::pair{x,y};}
coords_t food_::getPosition(){
  return position;
}



// SnakeGame functions
const int SnakeGame::inputRecordScore(){
    std::ifstream ifs;
    ifs.open(save_file);
    if(!ifs.is_open()) throw FileOpenError();               //chatch me
    std::string leader{};                                   //Vsauce 123
    int leader_score;
    ifs >> leader >> leader_score;
    ifs.close();
    return leader_score;
}
void SnakeGame::saveRecordScore(){
    std::ifstream ifs(save_file);
    char* temp_file="save/tmp.txt";
    std::ofstream ofs(temp_file);
    if(!ifs.is_open()) throw FileOpenError();               //chatch me
    if(!ofs.is_open()) throw FileOpenError();               //chatch me
    std::string leader{}, new_name{};
    int leader_score;
    int counter=5;
    while(!ifs.eof()&&counter>0){
        ifs >> leader >> leader_score;
        if(leader_score<score){
            new_name=saveNewRecord();
            ofs<< new_name<<" "<<score<<std::endl;
            counter--;
        }
        if(counter && leader!=new_name)
            ofs<<leader<<" "<<leader_score<<std::endl;
        counter--;
    }
    ifs.close();
    ofs.close();
    std::remove(save_file);
    std::rename(temp_file, save_file);
}
std::string SnakeGame::saveNewRecord(){
    //??
    return "user_1";
}
void SnakeGame::updateScoreSpeed(){
  score++;
  if(score%SPEEDSTEP==0){
    speed++;                                      //speed mechanics update!!!
  }
  if(score>=record_score)
    record_score=score;
}
void SnakeGame::moving(){
  if(field.checkForFood())
    updateScoreSpeed();
  field.moveSnake();
  if(field.checkForCrach())
    game_state=st_GameOver; 
}
















}


