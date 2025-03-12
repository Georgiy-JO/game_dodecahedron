#pragma once

#include <random>
#include <chrono> 

namespace s21 {
    class randGen_{
        private:
          std::mt19937 mt;
          std::uniform_int_distribution<u_int> x_dist;
          std::uniform_int_distribution<u_int> y_dist;
          std::uniform_int_distribution<char> binary;
        public:
          randGen_(u_int WIDTH_, u_int HEIGHT_);
          std::mt19937 getMT();
          u_int getX();
          u_int getY();
          char getBinary();
      };
}