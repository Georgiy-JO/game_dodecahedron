#pragma once

#include <vector>  
#include "../service.hpp"

namespace s21 {
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
          node_ getHead();
          int getDirection();
          void reset(int x_begining, int y_begining);
      };
}