
#include "field_.hpp"
namespace s21 {
    field_::field_():snake(WIDTH/2, HEIGHT/2+2), food(nullptr), rand_gen(WIDTH, HEIGHT){ spawnFood();}
    void field_::spawnFood(){
    u_int x, y, binary=rand_gen.getBinary();

    u_int snake_size=snake.snakeSize();
    int flag =1;

    while(flag){
        flag=0;
        x = rand_gen.getX();
        y= rand_gen.getY();
        for(u_int i=0;!flag && i<snake_size ;i++){
            if((int)x==(int)snake[i].first || (int)y==snake[i].second)
                flag=1;
        }
    }
    if(binary)
        food=std::make_unique<mouse_>(x,y);
    else
        food=std::make_unique<insect_>(x,y);
    // food->setPosition(x,y);
    }
    bool field_::checkForFood(){
    auto next_step=snake.getHead();
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
    return (next_step==(snake_::node_)food->getPosition())?true:false;
    }
    bool field_::checkForCrach(){
        bool flag=(snake[0].first<0 || snake[0].first>=WIDTH || snake[0].second<0||snake[0].second>=HEIGHT)?1:0;
        for(unsigned int i=0;!flag &&i<snake.snakeSize();i++){
            if(snake[0].first==snake[i].first && snake[0].second==snake[i].second)
            flag=1;
        }
        return flag;
    }
    void field_::moveSnake (){
    snake.snakeMove();
    }
    int field_::getFoodValue(){
    return food->getValue();
    }
    void field_::snakeTurnRight(){
    snake.changeDirection(snake.Right);
    }
    void field_::snakeTurnLeft(){
    snake.changeDirection(snake.Left);
    }
    void field_::reset(){
    snake.reset(WIDTH/2, HEIGHT/2+2);
    spawnFood();
    }
}