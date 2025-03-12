
#include"food_.hpp"

namespace s21 {
    void food_::setPosition(u_int x, u_int y){position=std::pair{x,y};}
    coords_t food_::getPosition(){
    return position;
    }
    int food_::getValue(){
    return VALUE;
    }

}