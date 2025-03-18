#include <gtest/gtest.h>

#include "../src/brick_game/snake/s-snake.hpp"

using std::cout, std::endl;
static constexpr const char* save_file = "saves/high_score_s-snake.txt";

void printField(s21::field_& field){
  for(int i=0;i<s21::field_::HEIGHT;i++){
    for(int j=0;j<s21::field_::WIDTH;j++){
      if(field(j,i)==1)
        cout <<"x";
      else
        cout <<"_";
    }
    cout<<endl;
  }
}
void printGame(s21::SnakeGame& game){
  for(int i=0;i<s21::field_::HEIGHT;i++){
    for(int j=0;j<s21::field_::WIDTH;j++){
      if(game.getField(j,i)==1)
        cout <<"x";
      else if(game.getField(j,i)==2)
        cout <<"o";
        else if(game.getField(j,i)==3)
          cout <<"O";
      else
        cout <<" ";
    }
    cout<<endl;
  }
}

TEST(SnakeTest__timer_, Basic_1) {
  using cl = std::chrono::steady_clock;
  s21::timer_ timer;
  EXPECT_EQ(timer.getMovesNumber(), 0);
  EXPECT_EQ(timer.getSpeed(), 0);
  timer.setSpeed(4);
  EXPECT_EQ(timer.getSpeed(), 4);
  timer.updateSpeed();
  EXPECT_EQ(timer.getSpeed(), 5);
  timer.setSpeed(14);
  EXPECT_EQ(timer.getSpeed(), 5);
  timer.updateSpeed();
  timer.updateSpeed();
  timer.updateSpeed();
  timer.updateSpeed();
  timer.updateSpeed();
  timer.updateSpeed();
  timer.updateSpeed();
  timer.updateSpeed();
  timer.updateSpeed();
  timer.updateSpeed();
  timer.updateSpeed();
  EXPECT_EQ(timer.getSpeed(), 9);
  auto check_timer = cl::now();
  timer.reset();
  while (std::chrono::duration_cast<std::chrono::milliseconds>(cl::now() -
                                                               check_timer)
             .count() < 1000) {
  }
  EXPECT_EQ(timer.getMovesNumber(), 10);
  timer.totalReset();
  check_timer = cl::now();
  while (std::chrono::duration_cast<std::chrono::milliseconds>(cl::now() -
                                                               check_timer)
             .count() < 1000) {
  }
  EXPECT_EQ(timer.getMovesNumber(), 2);
}
TEST(SnakeTest__food_, Basic_1) {
  s21::food_ food_0, food_01(2,3);
  s21::insect_ food_10, food_11(4,5);
  s21::mouse_ food_20, food_21(6,7);
  std::unique_ptr <s21::food_> food_13, food_23;
  food_13 =std::make_unique<s21::insect_>(8,9);
  food_23 =std::make_unique<s21::mouse_ >(0,1);

  EXPECT_EQ(food_0.getPosition(),s21::coords_t(0,0));
  EXPECT_EQ(food_01.getPosition(),s21::coords_t(2,3));
  EXPECT_EQ(food_10.getPosition(),s21::coords_t(0,0));
  EXPECT_EQ(food_11.getPosition(),s21::coords_t(4,5));
  EXPECT_EQ(food_20.getPosition(),s21::coords_t(0,0));
  EXPECT_EQ(food_21.getPosition(),s21::coords_t(6,7));
  EXPECT_EQ(food_13->getPosition(),s21::coords_t(8,9));
  EXPECT_EQ(food_23->getPosition(),s21::coords_t(0,1));

  EXPECT_EQ(food_0.getValue(), 0);
  EXPECT_EQ(food_01.getValue(), 0);
  EXPECT_EQ(food_10.getValue(), 1);
  EXPECT_EQ(food_11.getValue(), 1);
  EXPECT_EQ(food_20.getValue(), 2);
  EXPECT_EQ(food_21.getValue(), 2);
  EXPECT_EQ(food_13->getValue(), 1);
  EXPECT_EQ(food_23->getValue(), 2);

  food_20.setPosition(1,2);
  EXPECT_EQ(food_20.getPosition(),s21::coords_t(1,2));

  food_13=std::make_unique<s21::mouse_ >(10,11);
  EXPECT_EQ(food_13->getPosition(),s21::coords_t(10,11));
  EXPECT_EQ(food_13->getValue(), 2);

}
TEST(SnakeTest__randGen_, Basic_1){
  int x_max=10, y_max=20;
  for(int i=0;i<20;i++){
    s21::randGen_ gena(x_max,y_max);
    EXPECT_LE(gena.getX(),x_max);
    EXPECT_GE(gena.getX(),0);
    EXPECT_LE(gena.getY(),y_max);
    EXPECT_GE(gena.getY(),0);
    EXPECT_LE(gena.getBinary(),1);
    EXPECT_GE(gena.getBinary(),0);
  }
  x_max=5;
  y_max=100;
  for(int i=0;i<20;i++){
    s21::randGen_ gena(x_max,y_max);
    EXPECT_LE(gena.getX(),x_max);
    EXPECT_GE(gena.getX(),0);
    EXPECT_LE(gena.getY(),y_max);
    EXPECT_GE(gena.getY(),0);
    EXPECT_LE(gena.getBinary(),1);
    EXPECT_GE(gena.getBinary(),0);
  }
}
TEST(SnakeTest__snake_, Basic_1){
  s21::snake_ snake0;
  EXPECT_EQ(snake0[0],s21::snake_::node_(0,0));
  EXPECT_EQ(snake0[1],s21::snake_::node_(0,1));
  EXPECT_EQ(snake0[2],s21::snake_::node_(0,2));
  EXPECT_EQ(snake0[3],s21::snake_::node_(0,3));
  s21::snake_ snake(s21::field_::WIDTH/2,s21::field_::HEIGHT/2+2);
  int x=s21::field_::WIDTH/2, y=s21::field_::HEIGHT/2+2;
  EXPECT_EQ(snake[0],s21::snake_::node_(x,y));
  EXPECT_EQ(snake[1],s21::snake_::node_(x,y-1));
  EXPECT_EQ(snake[2],s21::snake_::node_(x,y-2));
  EXPECT_EQ(snake[3],s21::snake_::node_(x,y-3));

  EXPECT_EQ(snake.getDirection(),s21::snake_::Directions::Down);
  EXPECT_EQ(snake.getSize(),4);
  EXPECT_EQ(snake.getHead(),s21::snake_::node_(x,y));
  EXPECT_EQ(snake.getHead(),snake[0]);
  EXPECT_THROW(snake[4], s21::OutOfRangeError);
}
TEST(SnakeTest__snake_, Move){
  s21::snake_ snake(s21::field_::WIDTH/2,s21::field_::HEIGHT/2+2);
  int x=s21::field_::WIDTH/2, y=s21::field_::HEIGHT/2+2;
  int moves=10, size=4;

  for(int i=0;i<moves;i++){
    snake.snakeMove();
  }

  for(int i=0;i<4;i++){
    EXPECT_EQ(snake[i],s21::snake_::node_(x,y+moves-i));
  }

  EXPECT_EQ(snake.getDirection(),s21::snake_::Directions::Down);
  EXPECT_EQ(snake.getSize(),size);
  EXPECT_EQ(snake[0],s21::snake_::node_(x,y+moves));
  EXPECT_THROW(snake[4], s21::OutOfRangeError);

}
TEST(SnakeTest__snake_, Turn){
  s21::snake_ snake(s21::field_::WIDTH/2,s21::field_::HEIGHT/2+2);
  int x=s21::field_::WIDTH/2, y=s21::field_::HEIGHT/2+2;
  int moves=10, size=4;

  for(int i=0;i<moves;i++){
    snake.snakeMove();
  }

  for(int i=0;i<4;i++){
    EXPECT_EQ(snake[i],s21::snake_::node_(x,y+moves-i));
  }

  EXPECT_EQ(snake.getDirection(),s21::snake_::Directions::Down);
  EXPECT_EQ(snake.getSize(),size);
  EXPECT_EQ(snake[0],s21::snake_::node_(x,y+moves));
  EXPECT_THROW(snake[4], s21::OutOfRangeError);

  int turn_l=s21::snake_::Directions::Left, turn_r=s21::snake_::Directions::Right;
  snake.changeDirection(turn_l);
  EXPECT_EQ(snake.getDirection(),s21::snake_::Directions::Right);
  snake.changeDirection(turn_l);
  EXPECT_EQ(snake.getDirection(),s21::snake_::Directions::Up);
  snake.changeDirection(turn_l);
  EXPECT_EQ(snake.getDirection(),s21::snake_::Directions::Left);
  snake.changeDirection(turn_l);
  EXPECT_EQ(snake.getDirection(),s21::snake_::Directions::Down);
  snake.changeDirection(turn_r);
  EXPECT_EQ(snake.getDirection(),s21::snake_::Directions::Left);
  snake.changeDirection(turn_r);
  EXPECT_EQ(snake.getDirection(),s21::snake_::Directions::Up);
  snake.changeDirection(turn_r);
  EXPECT_EQ(snake.getDirection(),s21::snake_::Directions::Right);
  snake.changeDirection(turn_r);
  EXPECT_EQ(snake.getDirection(),s21::snake_::Directions::Down);
  snake.changeDirection(turn_r);
  snake.changeDirection(turn_l);
  EXPECT_EQ(snake.getDirection(),s21::snake_::Directions::Down);
  snake.changeDirection(turn_r);
  snake.changeDirection(turn_r);
  snake.changeDirection(turn_l);
  snake.changeDirection(turn_l);
  snake.changeDirection(turn_l);
  EXPECT_EQ(snake.getDirection(),s21::snake_::Directions::Right);

  EXPECT_THROW(snake.changeDirection(2), s21::InputError);
}
TEST(SnakeTest__snake_, Turn_Move){
  int x=10, y=10;
  int size=4;
  int turn_l=s21::snake_::Directions::Left, turn_r=s21::snake_::Directions::Right;
  s21::snake_ snake(x,y);

  for(int i=0;i<4;i++){
    EXPECT_EQ(snake[i],s21::snake_::node_(x,y-i));
  }
  EXPECT_EQ(snake.getDirection(),s21::snake_::Directions::Down);
  EXPECT_EQ(snake.getSize(),size);
  EXPECT_EQ(snake[0],s21::snake_::node_(x,y));
  EXPECT_THROW(snake[4], s21::OutOfRangeError);
  EXPECT_EQ(snake.selfCrash(),0);

  snake.changeDirection(turn_r);
  snake.snakeMove();
  EXPECT_EQ(snake[0],s21::snake_::node_(x-1,y));
  EXPECT_EQ(snake[1],s21::snake_::node_(x,y));
  EXPECT_EQ(snake[2],s21::snake_::node_(x,y-1));
  EXPECT_EQ(snake[3],s21::snake_::node_(x,y-2));
  EXPECT_THROW(snake[4], s21::OutOfRangeError);
  EXPECT_EQ(snake.getDirection(),s21::snake_::Directions::Left);
  EXPECT_EQ(snake.getSize(),size);
  EXPECT_EQ(snake.selfCrash(),0);

  snake.changeDirection(turn_l);
  snake.snakeMove();
  EXPECT_EQ(snake[0],s21::snake_::node_(x-1,y+1));
  EXPECT_EQ(snake[1],s21::snake_::node_(x-1,y));
  EXPECT_EQ(snake[2],s21::snake_::node_(x,y));
  EXPECT_EQ(snake[3],s21::snake_::node_(x,y-1));
  EXPECT_THROW(snake[4], s21::OutOfRangeError);
  EXPECT_EQ(snake.getDirection(),s21::snake_::Directions::Down);
  EXPECT_EQ(snake.getSize(),size);
  EXPECT_EQ(snake.selfCrash(),0);

  snake.changeDirection(turn_r);
  snake.snakeMove();
  EXPECT_EQ(snake[0],s21::snake_::node_(x-2,y+1));
  EXPECT_EQ(snake[1],s21::snake_::node_(x-1,y+1));
  EXPECT_EQ(snake[2],s21::snake_::node_(x-1,y));
  EXPECT_EQ(snake[3],s21::snake_::node_(x,y));
  EXPECT_THROW(snake[4], s21::OutOfRangeError);
  EXPECT_EQ(snake.getDirection(),s21::snake_::Directions::Left);
  EXPECT_EQ(snake.getSize(),size);
  EXPECT_EQ(snake.selfCrash(),0);

  snake.changeDirection(turn_r);
  snake.snakeMove();
  EXPECT_EQ(snake[0],s21::snake_::node_(x-2,y));
  EXPECT_EQ(snake[1],s21::snake_::node_(x-2,y+1));
  EXPECT_EQ(snake[2],s21::snake_::node_(x-1,y+1));
  EXPECT_EQ(snake[3],s21::snake_::node_(x-1,y));
  EXPECT_THROW(snake[4], s21::OutOfRangeError);
  EXPECT_EQ(snake.getDirection(),s21::snake_::Directions::Up);
  EXPECT_EQ(snake.getSize(),size);
  EXPECT_EQ(snake.selfCrash(),0);
}
TEST(SnakeTest__snake_, Grow){
  int x=10, y=10;
  int size=4;
  int turn_l=s21::snake_::Directions::Left, turn_r=s21::snake_::Directions::Right;
  s21::snake_ snake(x,y);

  EXPECT_EQ(snake[0],s21::snake_::node_(x,y));
  EXPECT_EQ(snake[1],s21::snake_::node_(x,y-1));
  EXPECT_EQ(snake[2],s21::snake_::node_(x,y-2));
  EXPECT_EQ(snake[3],s21::snake_::node_(x,y-3));
  EXPECT_THROW(snake[4], s21::OutOfRangeError);
  EXPECT_EQ(snake.getDirection(),s21::snake_::Directions::Down);
  EXPECT_EQ(snake.getSize(),size);
  EXPECT_EQ(snake.selfCrash(),0);

  snake.snakeGrow();
  size++;
  EXPECT_EQ(snake[0],s21::snake_::node_(x,y+1));
  EXPECT_EQ(snake[1],s21::snake_::node_(x,y));
  EXPECT_EQ(snake[2],s21::snake_::node_(x,y-1));
  EXPECT_EQ(snake[3],s21::snake_::node_(x,y-2));
  EXPECT_EQ(snake[4],s21::snake_::node_(x,y-3));
  EXPECT_THROW(snake[5], s21::OutOfRangeError);
  EXPECT_EQ(snake.getDirection(),s21::snake_::Directions::Down);
  EXPECT_EQ(snake.getSize(),size);
  EXPECT_EQ(snake.selfCrash(),0);

  snake.changeDirection(turn_r);
  snake.snakeGrow();
  size++;
  EXPECT_EQ(snake[0],s21::snake_::node_(x-1,y+1));
  EXPECT_EQ(snake[1],s21::snake_::node_(x,y+1));
  EXPECT_EQ(snake[2],s21::snake_::node_(x,y));
  EXPECT_EQ(snake[3],s21::snake_::node_(x,y-1));
  EXPECT_EQ(snake[4],s21::snake_::node_(x,y-2));
  EXPECT_EQ(snake[5],s21::snake_::node_(x,y-3));
  EXPECT_THROW(snake[6], s21::OutOfRangeError);
  EXPECT_EQ(snake.getDirection(),s21::snake_::Directions::Left);
  EXPECT_EQ(snake.getSize(),size);
  EXPECT_EQ(snake.selfCrash(),0);

  snake.changeDirection(turn_l);
  snake.snakeGrow();
  size++;
  EXPECT_EQ(snake[0],s21::snake_::node_(x-1,y+2));
  EXPECT_EQ(snake[1],s21::snake_::node_(x-1,y+1));
  EXPECT_EQ(snake[2],s21::snake_::node_(x,y+1));
  EXPECT_EQ(snake[3],s21::snake_::node_(x,y));
  EXPECT_EQ(snake[4],s21::snake_::node_(x,y-1));
  EXPECT_EQ(snake[5],s21::snake_::node_(x,y-2));
  EXPECT_EQ(snake[6],s21::snake_::node_(x,y-3));
  EXPECT_THROW(snake[7], s21::OutOfRangeError);
  EXPECT_EQ(snake.getDirection(),s21::snake_::Directions::Down);
  EXPECT_EQ(snake.getSize(),size);
  EXPECT_EQ(snake.selfCrash(),0);
}
TEST(SnakeTest__snake_, Crash){
  int x=10, y=10;
  int size=4;
  int turn_l=s21::snake_::Directions::Left, turn_r=s21::snake_::Directions::Right;
  s21::snake_ snake(x,y);

  for(int i=0;i<4;i++){
    EXPECT_EQ(snake[i],s21::snake_::node_(x,y-i));
  }
  EXPECT_EQ(snake.getDirection(),s21::snake_::Directions::Down);
  EXPECT_EQ(snake.getSize(),size);
  EXPECT_EQ(snake[0],s21::snake_::node_(x,y));
  EXPECT_THROW(snake[4], s21::OutOfRangeError);
  EXPECT_EQ(snake.selfCrash(),0);

  snake.changeDirection(turn_r);
  snake.snakeMove();
  EXPECT_EQ(snake[0],s21::snake_::node_(x-1,y));
  EXPECT_EQ(snake[1],s21::snake_::node_(x,y));
  EXPECT_EQ(snake[2],s21::snake_::node_(x,y-1));
  EXPECT_EQ(snake[3],s21::snake_::node_(x,y-2));
  EXPECT_THROW(snake[4], s21::OutOfRangeError);
  EXPECT_EQ(snake.getDirection(),s21::snake_::Directions::Left);
  EXPECT_EQ(snake.getSize(),size);
  EXPECT_EQ(snake.selfCrash(),0);

  snake.changeDirection(turn_l);
  snake.snakeMove();
  EXPECT_EQ(snake[0],s21::snake_::node_(x-1,y+1));
  EXPECT_EQ(snake[1],s21::snake_::node_(x-1,y));
  EXPECT_EQ(snake[2],s21::snake_::node_(x,y));
  EXPECT_EQ(snake[3],s21::snake_::node_(x,y-1));
  EXPECT_THROW(snake[4], s21::OutOfRangeError);
  EXPECT_EQ(snake.getDirection(),s21::snake_::Directions::Down);
  EXPECT_EQ(snake.getSize(),size);
  EXPECT_EQ(snake.selfCrash(),0);

  snake.changeDirection(turn_r);
  snake.snakeMove();
  EXPECT_EQ(snake[0],s21::snake_::node_(x-2,y+1));
  EXPECT_EQ(snake[1],s21::snake_::node_(x-1,y+1));
  EXPECT_EQ(snake[2],s21::snake_::node_(x-1,y));
  EXPECT_EQ(snake[3],s21::snake_::node_(x,y));
  EXPECT_THROW(snake[4], s21::OutOfRangeError);
  EXPECT_EQ(snake.getDirection(),s21::snake_::Directions::Left);
  EXPECT_EQ(snake.getSize(),size);
  EXPECT_EQ(snake.selfCrash(),0);

  snake.changeDirection(turn_r);
  snake.snakeMove();
  EXPECT_EQ(snake[0],s21::snake_::node_(x-2,y));
  EXPECT_EQ(snake[1],s21::snake_::node_(x-2,y+1));
  EXPECT_EQ(snake[2],s21::snake_::node_(x-1,y+1));
  EXPECT_EQ(snake[3],s21::snake_::node_(x-1,y));
  EXPECT_THROW(snake[4], s21::OutOfRangeError);
  EXPECT_EQ(snake.getDirection(),s21::snake_::Directions::Up);
  EXPECT_EQ(snake.getSize(),size);
  EXPECT_EQ(snake.selfCrash(),0);

  
  snake.changeDirection(turn_r);
  snake.snakeGrow();
  EXPECT_EQ(snake[0],s21::snake_::node_(x-1,y));
  EXPECT_EQ(snake[1],s21::snake_::node_(x-2,y));
  EXPECT_EQ(snake[2],s21::snake_::node_(x-2,y+1));
  EXPECT_EQ(snake[3],s21::snake_::node_(x-1,y+1));
  EXPECT_EQ(snake[4],s21::snake_::node_(x-1,y));
  EXPECT_THROW(snake[5], s21::OutOfRangeError);
  EXPECT_EQ(snake.getDirection(),s21::snake_::Directions::Right);
  EXPECT_EQ(snake.getSize(),size+1);
  EXPECT_EQ(snake.selfCrash(),1);


  snake.reset(x,y);
  for(int i=0;i<4;i++){
    EXPECT_EQ(snake[i],s21::snake_::node_(x,y-i));
  }
  EXPECT_EQ(snake[0],s21::snake_::node_(x,y));
  EXPECT_THROW(snake[4], s21::OutOfRangeError);
  EXPECT_EQ(snake.getDirection(),s21::snake_::Directions::Down);
  EXPECT_EQ(snake.getSize(),size);
  EXPECT_EQ(snake.selfCrash(),0);
}
TEST(SnakeTest__field_, Basic_1){
  s21::field_ field;
  int snake_length=4;
  int count=0, count_snake=0, count_food=0, count_error=0;
  EXPECT_LE(field.getFoodValue(),2);
  EXPECT_GT(field.getFoodValue(),0);
  for(int i=0;i<s21::field_::WIDTH ;i++){
    for(int j=0;j<s21::field_::HEIGHT;j++){
      if(field(i,j)>0){
        count++;
        if(field(i,j)==1)
          count_snake++;
        else  
        count_food++;
      }
      else if(field(i,j)<0)
      count_error++;
    }
  }
  EXPECT_EQ(count, snake_length+1);
  EXPECT_EQ(count_snake, snake_length);
  EXPECT_EQ(count_food, 1);
  EXPECT_EQ(count_error, 0);
  EXPECT_EQ(field(s21::field_::WIDTH/2,s21::field_::HEIGHT/2-1),1);
  EXPECT_EQ(field(s21::field_::WIDTH/2,s21::field_::HEIGHT/2),1);
  EXPECT_EQ(field(s21::field_::WIDTH/2,s21::field_::HEIGHT/2+1),1);
  EXPECT_EQ(field(s21::field_::WIDTH/2,s21::field_::HEIGHT/2+2),1);
  EXPECT_EQ(field(50,50),-1);
  EXPECT_EQ(field(-1,0),-1);
}
TEST(SnakeTest__field_, Food_1){
  s21::field_ field;
  EXPECT_LE(field.checkForFood(),1);
  EXPECT_GE(field.checkForFood(),0);
}
TEST(SnakeTest__field_, Snake_1){
  s21::field_ field;
  int steps=s21::field_::HEIGHT-(s21::field_::HEIGHT/2+2);
  int temp=field(s21::field_::WIDTH/2,s21::field_::HEIGHT-4);
  for(int i=0;i<steps;i++){
    EXPECT_EQ(field.checkForCrach(),false);
    field.moveSnake();
  }
  EXPECT_EQ(field.checkForCrach(),true);

  EXPECT_EQ(field(s21::field_::WIDTH/2,s21::field_::HEIGHT-1),1);
  EXPECT_EQ(field(s21::field_::WIDTH/2,s21::field_::HEIGHT-2),1);
  EXPECT_EQ(field(s21::field_::WIDTH/2,s21::field_::HEIGHT-3),1);
  EXPECT_EQ(field(s21::field_::WIDTH/2,s21::field_::HEIGHT-4),temp);
  EXPECT_EQ(field(s21::field_::WIDTH/2,s21::field_::HEIGHT/2-1),0);
  EXPECT_EQ(field(s21::field_::WIDTH/2,s21::field_::HEIGHT/2),0);
  EXPECT_EQ(field(s21::field_::WIDTH/2,s21::field_::HEIGHT/2+1),0);
  EXPECT_EQ(field(s21::field_::WIDTH/2,s21::field_::HEIGHT/2+2),0);
}
TEST(SnakeTest__field_, Basic_2){
  s21::field_ field;
  int steps=s21::field_::HEIGHT-(s21::field_::HEIGHT/2+2);
  for(int i=0;i<steps;i++)
    field.moveSnake();
  
  EXPECT_EQ(field(s21::field_::WIDTH/2,s21::field_::HEIGHT-1),1);
  EXPECT_EQ(field(s21::field_::WIDTH/2,s21::field_::HEIGHT-2),1);
  EXPECT_EQ(field(s21::field_::WIDTH/2,s21::field_::HEIGHT-3),1);
  EXPECT_EQ(field(s21::field_::WIDTH/2,s21::field_::HEIGHT/2-1),0);
  EXPECT_EQ(field(s21::field_::WIDTH/2,s21::field_::HEIGHT/2),0);
  EXPECT_EQ(field(s21::field_::WIDTH/2,s21::field_::HEIGHT/2+1),0);
  EXPECT_EQ(field(s21::field_::WIDTH/2,s21::field_::HEIGHT/2+2),0);
  
  field.reset();

  EXPECT_EQ(field(s21::field_::WIDTH/2,s21::field_::HEIGHT/2-1),1);
  EXPECT_EQ(field(s21::field_::WIDTH/2,s21::field_::HEIGHT/2),1);
  EXPECT_EQ(field(s21::field_::WIDTH/2,s21::field_::HEIGHT/2+1),1);
  EXPECT_EQ(field(s21::field_::WIDTH/2,s21::field_::HEIGHT/2+2),1);

}
TEST(SnakeTest__field_, Snake_2){
  s21::field_ field;
  int steps=s21::field_::WIDTH-(s21::field_::WIDTH/2);
  field.snakeTurnRight();
  for(int i=0;i<steps;i++){
    EXPECT_EQ(field.checkForCrach(),false);
    field.moveSnake();
  }
  EXPECT_EQ(field.checkForCrach(),false);
  field.moveSnake();
  EXPECT_EQ(field.checkForCrach(),true);
  
  EXPECT_EQ(field(s21::field_::WIDTH/2,s21::field_::HEIGHT/2-1),0);
  EXPECT_EQ(field(s21::field_::WIDTH/2,s21::field_::HEIGHT/2),0);
  EXPECT_EQ(field(s21::field_::WIDTH/2,s21::field_::HEIGHT/2+1),0);
  EXPECT_EQ(field(s21::field_::WIDTH/2,s21::field_::HEIGHT/2+2),0);
  EXPECT_EQ(field(0,s21::field_::HEIGHT/2+2),1);
  EXPECT_EQ(field(1,s21::field_::HEIGHT/2+2),1);
  EXPECT_EQ(field(2,s21::field_::HEIGHT/2+2),1);

  // printField(field);
  
  field.snakeTurnLeft();
  field.moveSnake();
  field.snakeTurnLeft();
  field.moveSnake();

  for(int i=0;i<s21::field_::WIDTH;i++){
    EXPECT_EQ(field.checkForCrach(),false);
    field.moveSnake();
  }
  EXPECT_EQ(field.checkForCrach(),true);

  EXPECT_EQ(field(s21::field_::WIDTH/2,s21::field_::HEIGHT/2-1),0);
  EXPECT_EQ(field(s21::field_::WIDTH/2,s21::field_::HEIGHT/2),0);
  EXPECT_EQ(field(s21::field_::WIDTH/2,s21::field_::HEIGHT/2+1),0);
  EXPECT_EQ(field(s21::field_::WIDTH/2,s21::field_::HEIGHT/2+2),0);
  EXPECT_EQ(field(s21::field_::WIDTH-1,s21::field_::HEIGHT/2+3),1);
  EXPECT_EQ(field(s21::field_::WIDTH-2,s21::field_::HEIGHT/2+3),1);
  EXPECT_EQ(field(s21::field_::WIDTH-3,s21::field_::HEIGHT/2+3),1);

}
TEST(SnakeTest__field_, Food_2){
  s21::field_ field;
  EXPECT_LE(field.checkForFood(),1);
  EXPECT_GE(field.checkForFood(),0);
  field.snakeTurnLeft();
  EXPECT_LE(field.checkForFood(),1);
  EXPECT_GE(field.checkForFood(),0);
  field.snakeTurnLeft();
  EXPECT_EQ(field.checkForFood(),0);
  field.snakeTurnLeft();
  EXPECT_LE(field.checkForFood(),1);
  EXPECT_GE(field.checkForFood(),0);
}
TEST(SnakeTest__SnakeGame, Basic_1){
  s21::SnakeGame game;
  EXPECT_EQ(game.getRecordScore(),0);
  EXPECT_EQ(game.getScore(),0);
  EXPECT_EQ(game.getSpeed(),1);
  EXPECT_EQ(game.getGameState(),s21::SnakeGame::st_Moving);
  EXPECT_EQ(game.getGameState(),0);
  EXPECT_EQ(game.getField(s21::field_::WIDTH/2,s21::field_::HEIGHT/2+2),1);
  EXPECT_EQ(game.getField(s21::field_::WIDTH/2,s21::field_::HEIGHT/2+1),1);
  EXPECT_EQ(game.getField(s21::field_::WIDTH/2,s21::field_::HEIGHT/2+0),1);
  EXPECT_EQ(game.getField(s21::field_::WIDTH/2,s21::field_::HEIGHT/2-1),1);
}
TEST(SnakeTest__SnakeGame, Record_1){
  s21::SnakeGame game;
  EXPECT_EQ(game.getRecordScore(),0);
  EXPECT_EQ(game.getScore(),0);
  EXPECT_EQ(game.getSpeed(),1);
  EXPECT_EQ(game.getGameState(),s21::SnakeGame::st_Moving);
  EXPECT_EQ(game.getGameState(),0);
  EXPECT_EQ(game.getField(s21::field_::WIDTH/2,s21::field_::HEIGHT/2+2),1);
  EXPECT_EQ(game.getField(s21::field_::WIDTH/2,s21::field_::HEIGHT/2+1),1);
  EXPECT_EQ(game.getField(s21::field_::WIDTH/2,s21::field_::HEIGHT/2+0),1);
  EXPECT_EQ(game.getField(s21::field_::WIDTH/2,s21::field_::HEIGHT/2-1),1);

  game.saveRecordScore();
  
  std::ifstream ifs(save_file);
  std::string leader;
  int score;
  ifs>>leader>>score;
  ifs.close();

  EXPECT_EQ(leader,"user_1");
  EXPECT_EQ(score,0);
}
TEST(SnakeTest__SnakeGame, Record_2){
  std::ofstream ofs(save_file);
  ofs<<"Leader 100";
  ofs.close();
  s21::SnakeGame game;
  EXPECT_EQ(game.getRecordScore(),100);
  EXPECT_EQ(game.getScore(),0);
  EXPECT_EQ(game.getSpeed(),1);
  EXPECT_EQ(game.getGameState(),s21::SnakeGame::st_Moving);
  EXPECT_EQ(game.getGameState(),0);

  game.saveRecordScore();

  std::ifstream ifs(save_file);
  std::string leader;
  int score;
  ifs>>leader>>score;
  EXPECT_EQ(leader,"Leader");
  EXPECT_EQ(score,100);

  ifs>>leader>>score;
  EXPECT_EQ(leader,"user_1");
  EXPECT_EQ(score,0);
  ifs.close();

}
TEST(SnakeTest__SnakeGame, Record_3){
  std::ofstream ofs(save_file);
  ofs<<"Leader 100"<<endl;
  ofs<<"Leader_2 25"<<endl;
  ofs<<"Leader_3 -3"<<endl;
  ofs<<"Leader_4 -25"<<endl;
  ofs.close();

  s21::SnakeGame game;
  EXPECT_EQ(game.getRecordScore(),100);
  EXPECT_EQ(game.getScore(),0);
  EXPECT_EQ(game.getSpeed(),1);
  EXPECT_EQ(game.getGameState(),s21::SnakeGame::st_Moving);
  EXPECT_EQ(game.getGameState(),0);

  game.saveRecordScore();

  std::ifstream ifs(save_file);
  std::string leader;
  int score;
  ifs>>leader>>score;
  EXPECT_EQ(leader,"Leader");
  EXPECT_EQ(score,100);

  ifs>>leader>>score;
  EXPECT_EQ(leader,"Leader_2");
  EXPECT_EQ(score,25);

  ifs>>leader>>score;
  EXPECT_EQ(leader,"user_1");
  EXPECT_EQ(score,0);

  ifs>>leader>>score;
  EXPECT_EQ(leader,"Leader_3");
  EXPECT_EQ(score,-3);

  ifs>>leader>>score;
  EXPECT_EQ(leader,"Leader_4");
  EXPECT_EQ(score,-25);

  ifs.close();
}
TEST(SnakeTest__SnakeGame, Record_4){
  std::ofstream ofs(save_file);
  ofs<<"Leader 100"<<endl;
  ofs<<"Leader_2 25"<<endl;
  ofs<<"Leader_3 -3"<<endl;
  ofs<<"Leader_4 -25"<<endl;
  ofs<<"Leader_5 -50"<<endl;
  ofs.close();

  s21::SnakeGame game;
  EXPECT_EQ(game.getRecordScore(),100);
  EXPECT_EQ(game.getScore(),0);
  EXPECT_EQ(game.getSpeed(),1);
  EXPECT_EQ(game.getGameState(),s21::SnakeGame::st_Moving);
  EXPECT_EQ(game.getGameState(),0);

  game.saveRecordScore();

  std::ifstream ifs(save_file);
  std::string leader;
  int score;
  ifs>>leader>>score;
  EXPECT_EQ(leader,"Leader");
  EXPECT_EQ(score,100);

  ifs>>leader>>score;
  EXPECT_EQ(leader,"Leader_2");
  EXPECT_EQ(score,25);

  ifs>>leader>>score;
  EXPECT_EQ(leader,"user_1");
  EXPECT_EQ(score,0);

  ifs>>leader>>score;
  EXPECT_EQ(leader,"Leader_3");
  EXPECT_EQ(score,-3);

  ifs>>leader>>score;
  EXPECT_EQ(leader,"Leader_4");
  EXPECT_EQ(score,-25);

  ifs.close();
}
TEST(SnakeTest__SnakeGame, Record_5){
  std::ofstream ofs(save_file);
  ofs<<"Leader 100"<<endl;
  ofs<<"Leader_2 25"<<endl;
  ofs<<"Leader_3 20"<<endl;
  ofs<<"Leader_4 15"<<endl;
  ofs<<"Leader_5 10"<<endl;
  ofs.close();

  s21::SnakeGame game;
  EXPECT_EQ(game.getRecordScore(),100);
  EXPECT_EQ(game.getScore(),0);
  EXPECT_EQ(game.getSpeed(),1);
  EXPECT_EQ(game.getGameState(),s21::SnakeGame::st_Moving);
  EXPECT_EQ(game.getGameState(),0);

  game.saveRecordScore();

  std::ifstream ifs(save_file);
  std::string leader;
  int score;
  ifs>>leader>>score;
  EXPECT_EQ(leader,"Leader");
  EXPECT_EQ(score,100);

  ifs>>leader>>score;
  EXPECT_EQ(leader,"Leader_2");
  EXPECT_EQ(score,25);

  ifs>>leader>>score;
  EXPECT_EQ(leader,"Leader_3");
  EXPECT_EQ(score,20);

  ifs>>leader>>score;
  EXPECT_EQ(leader,"Leader_4");
  EXPECT_EQ(score,15);

  ifs>>leader>>score;
  EXPECT_EQ(leader,"Leader_5");
  EXPECT_EQ(score,10);

  ifs.close();
}
TEST(SnakeTest__SnakeGame, Record_6){
  std::ofstream ofs(save_file);
  ofs<<"Leader -100"<<endl;
  ofs<<"Leader_2 -250"<<endl;
  ofs<<"Leader_3 -300"<<endl;
  ofs<<"Leader_4 -350"<<endl;
  ofs<<"Leader_5 -400"<<endl;
  ofs.close();

  s21::SnakeGame game;
  EXPECT_EQ(game.getRecordScore(),-100);
  EXPECT_EQ(game.getScore(),0);
  EXPECT_EQ(game.getSpeed(),1);
  EXPECT_EQ(game.getGameState(),s21::SnakeGame::st_Moving);

  game.saveRecordScore();

  std::ifstream ifs(save_file);
  std::string leader;
  int score;

  ifs>>leader>>score;
  EXPECT_EQ(leader,"user_1");
  EXPECT_EQ(score,0);

  ifs>>leader>>score;
  EXPECT_EQ(leader,"Leader");
  EXPECT_EQ(score,-100);

  ifs>>leader>>score;
  EXPECT_EQ(leader,"Leader_2");
  EXPECT_EQ(score,-250);

  ifs>>leader>>score;
  EXPECT_EQ(leader,"Leader_3");
  EXPECT_EQ(score,-300);

  ifs>>leader>>score;
  EXPECT_EQ(leader,"Leader_4");
  EXPECT_EQ(score,-350);
  ifs>>leader>>score;
  EXPECT_EQ(ifs.eof(),true);

  ifs.close();
}
TEST(SnakeTest__SnakeGame, Speed){
  std::ofstream ofs(save_file);
  ofs<<"";
  ofs.close();

  s21::SnakeGame game;
  game.updateScoreSpeed();

  game.saveRecordScore();

  std::ifstream ifs(save_file);
  std::string leader;
  int score;
  ifs>>leader>>score;
  ifs.close();

  if(score==1){
    for(int i=0;i<4;i++){
      EXPECT_EQ(game.getSpeed(),1);
      game.updateScoreSpeed();
    }
    EXPECT_EQ(game.getSpeed(),2);

    for(int i=0;i<5;i++){
      EXPECT_EQ(game.getSpeed(),2);
      game.updateScoreSpeed();
    }
    EXPECT_EQ(game.getSpeed(),3);
  }
  else{
    for(int i=0;i<2;i++){
      EXPECT_EQ(game.getSpeed(),1);
      game.updateScoreSpeed();
    }
    EXPECT_EQ(game.getSpeed(),2);
    for(int i=0;i<2;i++){
      EXPECT_EQ(game.getSpeed(),2);
      game.updateScoreSpeed();
    }
    EXPECT_EQ(game.getSpeed(),3);
  }
  game.gameOver();
  EXPECT_EQ(game.getGameState(),s21::SnakeGame::st_GameOver);
  std::ifstream ifs2(save_file);
  ifs2>>leader>>score;
  EXPECT_EQ(score,10);
  ifs2.close();

}
TEST(SnakeTest__SnakeGame, Movement){
  s21::SnakeGame game;
  EXPECT_EQ(game.getRecordScore(),10);
  EXPECT_EQ(game.getScore(),0);
  EXPECT_EQ(game.getSpeed(),1);
  EXPECT_EQ(game.getField(s21::field_::WIDTH/2,s21::field_::HEIGHT/2+2),1);
  EXPECT_EQ(game.getField(s21::field_::WIDTH/2,s21::field_::HEIGHT/2+1),1);
  EXPECT_EQ(game.getField(s21::field_::WIDTH/2,s21::field_::HEIGHT/2+0),1);
  EXPECT_EQ(game.getField(s21::field_::WIDTH/2,s21::field_::HEIGHT/2-1),1);
  EXPECT_EQ(game.getGameState(),s21::SnakeGame::st_Moving);

  game.moving();
  EXPECT_EQ(game.getField(s21::field_::WIDTH/2,s21::field_::HEIGHT/2+2),1);
  EXPECT_EQ(game.getField(s21::field_::WIDTH/2,s21::field_::HEIGHT/2+1),1);
  EXPECT_EQ(game.getField(s21::field_::WIDTH/2,s21::field_::HEIGHT/2+0),1);
  EXPECT_EQ(game.getField(s21::field_::WIDTH/2,s21::field_::HEIGHT/2-1),0);
  EXPECT_EQ(game.getGameState(),s21::SnakeGame::st_Moving);

  game.moving();
  EXPECT_EQ(game.getField(s21::field_::WIDTH/2,s21::field_::HEIGHT/2+2),1);
  EXPECT_EQ(game.getField(s21::field_::WIDTH/2,s21::field_::HEIGHT/2+1),1);
  EXPECT_EQ(game.getField(s21::field_::WIDTH/2,s21::field_::HEIGHT/2+0),0);
  EXPECT_EQ(game.getField(s21::field_::WIDTH/2,s21::field_::HEIGHT/2-1),0);
  EXPECT_EQ(game.getGameState(),s21::SnakeGame::st_Moving);

  game.moving();
  EXPECT_EQ(game.getField(s21::field_::WIDTH/2,s21::field_::HEIGHT/2+2),1);
  EXPECT_EQ(game.getField(s21::field_::WIDTH/2,s21::field_::HEIGHT/2+1),0);
  EXPECT_EQ(game.getField(s21::field_::WIDTH/2,s21::field_::HEIGHT/2+0),0);
  EXPECT_EQ(game.getField(s21::field_::WIDTH/2,s21::field_::HEIGHT/2-1),0);
  EXPECT_EQ(game.getGameState(),s21::SnakeGame::st_Moving);

  game.moving();
  EXPECT_EQ(game.getField(s21::field_::WIDTH/2,s21::field_::HEIGHT/2+2),0);
  EXPECT_EQ(game.getField(s21::field_::WIDTH/2,s21::field_::HEIGHT/2+1),0);
  EXPECT_EQ(game.getField(s21::field_::WIDTH/2,s21::field_::HEIGHT/2+0),0);
  EXPECT_EQ(game.getField(s21::field_::WIDTH/2,s21::field_::HEIGHT/2-1),0);
  EXPECT_EQ(game.getGameState(),s21::SnakeGame::st_Moving);

  game.moving();
  game.moving();
  game.moving();
  EXPECT_EQ(game.getField(s21::field_::WIDTH/2,s21::field_::HEIGHT-1),1);
  EXPECT_EQ(game.getField(s21::field_::WIDTH/2,s21::field_::HEIGHT-2),1);
  EXPECT_EQ(game.getField(s21::field_::WIDTH/2,s21::field_::HEIGHT-3),1);
  EXPECT_EQ(game.getField(s21::field_::WIDTH/2,s21::field_::HEIGHT-4),1);
  EXPECT_EQ(game.getGameState(),s21::SnakeGame::st_Moving);
  game.moving();
  EXPECT_EQ(game.getGameState(),s21::SnakeGame::st_GameOver);

}
TEST(SnakeTest__SnakeGame, Timer){
  using cl = std::chrono::steady_clock;
  s21::SnakeGame game;

  EXPECT_EQ(game.getField(s21::field_::WIDTH/2,s21::field_::HEIGHT/2+2),1);
  EXPECT_EQ(game.getField(s21::field_::WIDTH/2,s21::field_::HEIGHT/2+1),1);
  EXPECT_EQ(game.getField(s21::field_::WIDTH/2,s21::field_::HEIGHT/2+0),1);
  EXPECT_EQ(game.getField(s21::field_::WIDTH/2,s21::field_::HEIGHT/2-1),1);
  EXPECT_EQ(game.getGameState(),s21::SnakeGame::st_Moving);

  auto check_timer = cl::now();
  while (std::chrono::duration_cast<std::chrono::milliseconds>(cl::now() -
                                                               check_timer)
             .count() < 1000) {
  }
  game.catchUpMovement();
  EXPECT_EQ(game.getField(s21::field_::WIDTH/2,s21::field_::HEIGHT/2+2),1);
  EXPECT_EQ(game.getField(s21::field_::WIDTH/2,s21::field_::HEIGHT/2+1),1);
  EXPECT_EQ(game.getField(s21::field_::WIDTH/2,s21::field_::HEIGHT/2+0),0);
  EXPECT_EQ(game.getField(s21::field_::WIDTH/2,s21::field_::HEIGHT/2-1),0);
  EXPECT_EQ(game.getGameState(),s21::SnakeGame::st_Moving);

  check_timer = cl::now();
  while (std::chrono::duration_cast<std::chrono::milliseconds>(cl::now() -
                                                               check_timer)
             .count() < 1000) {
  }
  game.catchUpMovement();
  EXPECT_EQ(game.getField(s21::field_::WIDTH/2,s21::field_::HEIGHT/2+2),0);
  EXPECT_EQ(game.getField(s21::field_::WIDTH/2,s21::field_::HEIGHT/2+1),0);
  EXPECT_EQ(game.getField(s21::field_::WIDTH/2,s21::field_::HEIGHT/2+0),0);
  EXPECT_EQ(game.getField(s21::field_::WIDTH/2,s21::field_::HEIGHT/2-1),0);
  EXPECT_EQ(game.getGameState(),s21::SnakeGame::st_Moving);

  game.gameReStart();
  EXPECT_EQ(game.getField(s21::field_::WIDTH/2,s21::field_::HEIGHT/2+2),1);
  EXPECT_EQ(game.getField(s21::field_::WIDTH/2,s21::field_::HEIGHT/2+1),1);
  EXPECT_EQ(game.getField(s21::field_::WIDTH/2,s21::field_::HEIGHT/2+0),1);
  EXPECT_EQ(game.getField(s21::field_::WIDTH/2,s21::field_::HEIGHT/2-1),1);
  EXPECT_EQ(game.getGameState(),s21::SnakeGame::st_Moving);
  EXPECT_EQ(game.getRecordScore(),10);
  EXPECT_EQ(game.getScore(),0);
  EXPECT_EQ(game.getSpeed(),1);

  game.gamePause();
  EXPECT_EQ(game.getGameState(),s21::SnakeGame::st_Pause);
  check_timer = cl::now();
  while (std::chrono::duration_cast<std::chrono::milliseconds>(cl::now() -
                                                               check_timer)
             .count() < 1000) {
  }
  EXPECT_EQ(game.getGameState(),s21::SnakeGame::st_Pause);

  game.gameContinue();
  EXPECT_EQ(game.getGameState(),s21::SnakeGame::st_Moving);
  game.catchUpMovement();
  EXPECT_EQ(game.getField(s21::field_::WIDTH/2,s21::field_::HEIGHT/2+2),1);
  EXPECT_EQ(game.getField(s21::field_::WIDTH/2,s21::field_::HEIGHT/2+1),1);
  EXPECT_EQ(game.getField(s21::field_::WIDTH/2,s21::field_::HEIGHT/2+0),1);
  EXPECT_EQ(game.getField(s21::field_::WIDTH/2,s21::field_::HEIGHT/2-1),1);
  EXPECT_EQ(game.getRecordScore(),10);
  EXPECT_EQ(game.getScore(),0);
  EXPECT_EQ(game.getSpeed(),1);
}
TEST(SnakeTest__SnakeGame, User_actions){
  s21::SnakeGame game;

  EXPECT_THROW(game.userActionHandler(10), s21::InputError);

  game.gameOver();
  EXPECT_EQ(game.getGameState(),s21::SnakeGame::st_GameOver);
  game.userActionHandler(s21::SnakeGame::ac_Start);
  EXPECT_EQ(game.getGameState(),s21::SnakeGame::st_Moving);
  EXPECT_EQ(game.getField(s21::field_::WIDTH/2,s21::field_::HEIGHT/2+2),1);
  EXPECT_EQ(game.getField(s21::field_::WIDTH/2,s21::field_::HEIGHT/2+1),1);
  EXPECT_EQ(game.getField(s21::field_::WIDTH/2,s21::field_::HEIGHT/2+0),1);
  EXPECT_EQ(game.getField(s21::field_::WIDTH/2,s21::field_::HEIGHT/2-1),1);
  game.gamePause();
  EXPECT_EQ(game.getGameState(),s21::SnakeGame::st_Pause);
  game.userActionHandler(s21::SnakeGame::ac_Start);
  EXPECT_EQ(game.getGameState(),s21::SnakeGame::st_Moving);



  game.userActionHandler(s21::SnakeGame::ac_Esc);
  EXPECT_EQ(game.getGameState(),s21::SnakeGame::st_GameOver);

  game.userActionHandler(s21::SnakeGame::ac_Start);
  EXPECT_EQ(game.getGameState(),s21::SnakeGame::st_Moving);
  game.gamePause();
  EXPECT_EQ(game.getGameState(),s21::SnakeGame::st_Pause);
  game.userActionHandler(s21::SnakeGame::ac_Esc);
  EXPECT_EQ(game.getGameState(),s21::SnakeGame::st_GameOver);

  game.userActionHandler(s21::SnakeGame::ac_Esc);
  EXPECT_EQ(game.getGameState(),s21::SnakeGame::st_Exit);
  
  game.gameReStart();
  EXPECT_EQ(game.getGameState(),s21::SnakeGame::st_Moving);
  game.userActionHandler(s21::SnakeGame::ac_Pause);
  EXPECT_EQ(game.getGameState(),s21::SnakeGame::st_Pause);

  auto check_timer = std::chrono::steady_clock::now();
  while (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() -
                                                               check_timer)
             .count() < 1000) {
  }
  
  game.catchUpMovement();
  EXPECT_EQ(game.getGameState(),s21::SnakeGame::st_Pause);
  game.userActionHandler(s21::SnakeGame::ac_Pause);
  EXPECT_EQ(game.getGameState(),s21::SnakeGame::st_Moving);
  EXPECT_EQ(game.getField(s21::field_::WIDTH/2,s21::field_::HEIGHT/2+2),1);
  EXPECT_EQ(game.getField(s21::field_::WIDTH/2,s21::field_::HEIGHT/2+1),1);
  EXPECT_EQ(game.getField(s21::field_::WIDTH/2,s21::field_::HEIGHT/2+0),1);
  EXPECT_EQ(game.getField(s21::field_::WIDTH/2,s21::field_::HEIGHT/2-1),1);

  game.userActionHandler(s21::SnakeGame::ac_Right);
  EXPECT_EQ(game.getField(s21::field_::WIDTH/2,s21::field_::HEIGHT/2+2),1);
  EXPECT_EQ(game.getField(s21::field_::WIDTH/2,s21::field_::HEIGHT/2+1),1);
  EXPECT_EQ(game.getField(s21::field_::WIDTH/2,s21::field_::HEIGHT/2+0),1);
  EXPECT_EQ(game.getField(s21::field_::WIDTH/2-1,s21::field_::HEIGHT/2+2),1);

  game.userActionHandler(s21::SnakeGame::ac_Left);
  EXPECT_EQ(game.getField(s21::field_::WIDTH/2,s21::field_::HEIGHT/2+2),1);
  EXPECT_EQ(game.getField(s21::field_::WIDTH/2,s21::field_::HEIGHT/2+1),1);
  EXPECT_EQ(game.getField(s21::field_::WIDTH/2-1,s21::field_::HEIGHT/2+3),1);
  EXPECT_EQ(game.getField(s21::field_::WIDTH/2-1,s21::field_::HEIGHT/2+2),1);

  game.userActionHandler(s21::SnakeGame::ac_Forvard);
  EXPECT_EQ(game.getField(s21::field_::WIDTH/2,s21::field_::HEIGHT/2+2),1);
  EXPECT_EQ(game.getField(s21::field_::WIDTH/2-1,s21::field_::HEIGHT/2+4),1);
  EXPECT_EQ(game.getField(s21::field_::WIDTH/2-1,s21::field_::HEIGHT/2+3),1);
  EXPECT_EQ(game.getField(s21::field_::WIDTH/2-1,s21::field_::HEIGHT/2+2),1);
  game.userActionHandler(s21::SnakeGame::ac_Forvard);
  EXPECT_EQ(game.getField(s21::field_::WIDTH/2-1,s21::field_::HEIGHT/2+5),1);
  EXPECT_EQ(game.getField(s21::field_::WIDTH/2-1,s21::field_::HEIGHT/2+4),1);
  EXPECT_EQ(game.getField(s21::field_::WIDTH/2-1,s21::field_::HEIGHT/2+3),1);
  EXPECT_EQ(game.getField(s21::field_::WIDTH/2-1,s21::field_::HEIGHT/2+2),1);
}
TEST(SnakeTest__SnakeGame, Test_run){
  s21::SnakeGame game;

  game.userActionHandler(s21::SnakeGame::ac_Left);
  int count=3;
  while(count){
    count--;
    game.userActionHandler(s21::SnakeGame::ac_Forvard);
  }

  game.userActionHandler(s21::SnakeGame::ac_Right);
  count=6;
  while(count){
    count--;
    game.userActionHandler(s21::SnakeGame::ac_Forvard);
  }

  game.userActionHandler(s21::SnakeGame::ac_Right);
  game.userActionHandler(s21::SnakeGame::ac_Right);
  count=7;
  while(count){
    count--;
    game.userActionHandler(s21::SnakeGame::ac_Forvard);
  }

  game.userActionHandler(s21::SnakeGame::ac_Right);
  game.userActionHandler(s21::SnakeGame::ac_Left);
  count=10;
  while(count){
    count--;
    game.userActionHandler(s21::SnakeGame::ac_Forvard);
  }
  // printGame(game);
  EXPECT_EQ(game.getField(s21::field_::WIDTH-1,0),1);

  game.userActionHandler(s21::SnakeGame::ac_Left);
  game.userActionHandler(s21::SnakeGame::ac_Left);
  count=18;
  while(count){
    count--;
    game.userActionHandler(s21::SnakeGame::ac_Forvard);
  }

  game.userActionHandler(s21::SnakeGame::ac_Right);
  game.userActionHandler(s21::SnakeGame::ac_Right);
  count=18;
  while(count){
    count--;
    game.userActionHandler(s21::SnakeGame::ac_Forvard);
  }

  game.userActionHandler(s21::SnakeGame::ac_Left);
  game.userActionHandler(s21::SnakeGame::ac_Left);
  count=18;
  while(count){
    count--;
    game.userActionHandler(s21::SnakeGame::ac_Forvard);
  }

  game.userActionHandler(s21::SnakeGame::ac_Right);
  game.userActionHandler(s21::SnakeGame::ac_Right);
  count=18;
  while(count){
    count--;
    game.userActionHandler(s21::SnakeGame::ac_Forvard);
  }

  EXPECT_EQ(game.getField(0,0),0);
  game.userActionHandler(s21::SnakeGame::ac_Left);
  game.userActionHandler(s21::SnakeGame::ac_Left);
  EXPECT_EQ(game.getGameState(),s21::SnakeGame::st_Moving);
  count=18;
  while(count){
    count--;
    game.userActionHandler(s21::SnakeGame::ac_Forvard);
  }

  game.userActionHandler(s21::SnakeGame::ac_Right);
  game.userActionHandler(s21::SnakeGame::ac_Right);
  count=18;
  while(count){
    count--;
    game.userActionHandler(s21::SnakeGame::ac_Forvard);
  }

  game.userActionHandler(s21::SnakeGame::ac_Left);
  game.userActionHandler(s21::SnakeGame::ac_Left);
  count=18;
  while(count){
    count--;
    game.userActionHandler(s21::SnakeGame::ac_Forvard);
  }

  game.userActionHandler(s21::SnakeGame::ac_Right);
  game.userActionHandler(s21::SnakeGame::ac_Right);
  count=18;
  while(count){
    count--;
    game.userActionHandler(s21::SnakeGame::ac_Forvard);
  }
  game.userActionHandler(s21::SnakeGame::ac_Left);
  game.userActionHandler(s21::SnakeGame::ac_Left);
  count=18;
  while(count){
    count--;
    game.userActionHandler(s21::SnakeGame::ac_Forvard);
  }
  // printGame(game);
  EXPECT_EQ(game.getField(0,s21::field_::HEIGHT-1),1);

}
TEST(SnakeTest__SnakeGame, Record_7){
  s21::SnakeGame game;
  std::remove(save_file);
  EXPECT_THROW(game.inputRecordScore(),s21::FileOpenError);
}

/*
TEST(SnakeTest__GameKeeperFunction, Basic_1){
  auto game=s21::gameInstanceKeeper();

  EXPECT_EQ(game->getField(s21::field_::WIDTH/2,s21::field_::HEIGHT/2+2),1);
  EXPECT_EQ(game->getField(s21::field_::WIDTH/2,s21::field_::HEIGHT/2+1),1);
  EXPECT_EQ(game->getField(s21::field_::WIDTH/2,s21::field_::HEIGHT/2+0),1);
  EXPECT_EQ(game->getField(s21::field_::WIDTH/2,s21::field_::HEIGHT/2-1),1);
}
*/
// EXPECT_EQ(timer.getSpeed(), 9);
// EXPECT_THROW(tree_ch_st.getParentData('5'), std::out_of_range);
int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}