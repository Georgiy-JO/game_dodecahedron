#pragma once

#include <memory>

#include "../snake_/snake_.hpp"
#include "../randGen_/randGen_.hpp"
#include "../food_/food_.hpp"

namespace s21 {
    class field_ {
        public:
          static constexpr int WIDTH = 10;
          static constexpr int HEIGHT = 20;
        private:
          snake_ snake;
          std::unique_ptr<food_> food;
      
          randGen_ rand_gen;
        public:
          field_();
      
          void spawnFood();
          bool checkForFood();  //check if will happen
          bool checkForCrach(); //check if hammened
          void moveSnake ();
          void snakeTurnRight();
          void snakeTurnLeft();
          int getFoodValue();
          void reset();
      };
}