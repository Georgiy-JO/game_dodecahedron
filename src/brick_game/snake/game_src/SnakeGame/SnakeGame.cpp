

#include "SnakeGame.hpp"
namespace s21 {
    SnakeGame::SnakeGame():field(){
        inputRecordScore();
    }
    SnakeGame::SnakeGame(char type):SnakeGame() {game_type=type;}
    void SnakeGame::inputRecordScore(){
        std::ifstream ifs;
        ifs.open(save_file);
        if(!ifs.is_open()) throw FileOpenError();               //chatch me
        std::string leader{};                                   //Vsauce 123
        int leader_score;
        ifs >> leader >> leader_score;
        ifs.close();
        record_score=leader_score;
    }
    void SnakeGame::saveRecordScore(){
        std::ifstream ifs(save_file);
        const char* temp_file="save/tmp.txt";
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
        // update in better version for github
        return "user_1";
    }
    void SnakeGame::updateScoreSpeed(){
    score+=field.getFoodValue();                                //different score for different types of food
    if(score/SPEEDSTEP>=timer.getSpeed()){
        timer.updateSpeed();                                      //speed mechanics update!!!
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
    if(score>=200)
        game_state=st_GameOver;
    }
    u_int SnakeGame::getSpeed(){
    return timer.getSpeed()+1;
    }
    void SnakeGame::catchUpMovement(){
    if(game_state==st_Moving){
        u_int move_number=timer.getMovesNumber();
        for(u_int i=0;i<move_number;i++){
        moving();
        }
    }
    }
    void SnakeGame::userActionHandler(int action){
    switch(action){
        case ac_Start:
            if(game_state==st_GameOver)
                gameReStart();
            else if (game_state==st_Pause)
                gameContinue();
            break;
        case ac_Esc:
            if(game_state==st_Moving|| game_state==st_Pause)
                gameOver();
            if(game_state==st_GameOver)
                game_state=st_Exit;               //handle
            break;
        case ac_Pause:
            if(game_state==st_Moving)
                gamePause();
            if(game_state==st_Pause)
                gameContinue();
            break;
        case ac_Right:
            if(game_state==st_Moving){
                field.snakeTurnRight();
                moving();
            }
            break;
        case ac_Left:
            if(game_state==st_Moving){
                field.snakeTurnLeft();
                moving();
            }
            break;
        case ac_Forvard:
        moving();                       //manage the pressing of the button
        break;
        default:
        throw InputError();            // catch me
        break;
    }
    }
    void SnakeGame::gameReStart(){
    field.reset();
    timer.totalReset();
    score=0;
    inputRecordScore();
    game_state=st_Moving;
    }
    void SnakeGame::gameOver(){
    saveRecordScore();
    game_state=st_GameOver;         //leaks here??
    }
    void SnakeGame::gamePause(){
    game_state=st_Pause;
    }
    void SnakeGame::gameContinue(){
    game_state=st_Moving;
    timer.reset();
    }

}