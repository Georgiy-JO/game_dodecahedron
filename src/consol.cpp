
#include "brick_game/snake/s-snake.h"
#include "iostream"
#include <chrono>


int main (){

    using std::endl, std::cout, std::cin;
    int key;
    cin>>key;
    cout<<key<<endl;
    if (key == 1){
        GameInfo_t game;
        auto check_timer = std::chrono::steady_clock::now();
        
        while(1){
            if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() -check_timer).count() > 200) {
                game=updateCurrentState();
                check_timer = std::chrono::steady_clock::now();
                for(int i=0;i<20;i++){
                    for(int j=0;j<10;j++){
                        if(game.field[i][j]>0)
                            cout<<"0";
                        else 
                        cout<<" ";
                    }
                    cout<<endl;
                }
            }
            cin>>key;
            if (key==2)
                break;
        }
        cout<<"HERE"<<endl;
    }



    return 0;
}