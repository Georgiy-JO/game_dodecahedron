#pragma once

#include "../service.hpp"

namespace s21 {
    class food_{
        protected:
          coords_t position;
          int VALUE =0;
        public:
          food_():position(0,0){}
          food_(u_int x, u_int y):position(x,y){}
          virtual ~food_() {}
      
          void setPosition(u_int x, u_int y);
          coords_t getPosition();
          int getValue();
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
}