
#include "snake_.hpp"

namespace s21 {
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
    snake_::node_ snake_::getHead(){
    return (coords_t) nodes[0]; 
    }
    int snake_::getDirection(){
    return direction;
    }
    void snake_::reset(int x_begining, int y_begining){
    nodes.clear();
    for(int i=0;i<4;i++){
        nodes.push_back(node_(x_begining-i,y_begining));
    } 
    direction=Down;
    }

}