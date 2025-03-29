#include "controller.hpp"

GameInfo_t updateCurrentState() {
    return gameInterector([](GameInfo_t& game){gameUpdater(game);}    );
}
void userInput(UserAction_t action, bool hold){
    gameInterector([&](GameInfo_t&){
        gameInput(action,hold); });

}

template <typename Callable>
GameInfo_t gameInterector (Callable&& gameOperation){
    GameInfo_t game_output{.field=nullptr, .next=nullptr, .score=0, .high_score=0, .level=0,.speed=0,.pause=false};
    try{
        try{
            gameOperation(game_output);
        }catch(std::exception& err ){
            std::cerr << "Error: " << err.what() << std::endl;
            endGame(game_output);
            throw;
        }
    }
    catch(s21::snakeError_& err){
        game_output.level=err.getCode();
    }
    catch(std::exception& err){
        game_output.level=-1;
    }
    return game_output;

}

void gameUpdater(GameInfo_t & game){
    const s21::SnakeGame* game_inside =  s21::gameInstanceKeeper();
    // if(game_inside->getGameState()==s21::SnakeGame::st_Moving)
    game.next=nullptr;
    game.score=game_inside->getScore();
    game.high_score=game_inside->getRecordScore();
    game.level=game_inside->getSpeed();
    game.speed=game.level;
    game.pause=false;
    game.field=outputFieldKeeper();
    if (game_inside->getGameState()==s21::SnakeGame::st_Exit)
        endGame(game);
    else 
    {
        if(game_inside->getGameState()==s21::SnakeGame::st_Pause)
            game.pause=true;
        if(game_inside->getGameState()==s21::SnakeGame::st_GameOver)
            game.field=nullptr;
        if( game.field){
            for(int y=0;y<s21::field_::HEIGHT;y++){
                for(int x=0;x<s21::field_::WIDTH;x++){
                    game.field[y][x]=game_inside->getField(x,y);
                }
            }
        }
    }
}
void gameInput(UserAction_t action, bool hold){
    (void) hold;  // Mark parameter as explicitly unused
    s21::SnakeGame* game_inside =  s21::gameInstanceKeeper();
    switch (action) {
        case UserAction_t::Start:
          game_inside->userActionHandler(s21::SnakeGame::ac_Start);
          break;
        case UserAction_t::Pause:
          game_inside->userActionHandler(s21::SnakeGame::ac_Pause);        
          break;
        case UserAction_t::Terminate:
          game_inside->userActionHandler(s21::SnakeGame::ac_Esc);         
          break;
        case UserAction_t::Left:
          game_inside->userActionHandler(s21::SnakeGame::ac_Left);  
          break;
        case UserAction_t::Right:
          game_inside->userActionHandler(s21::SnakeGame::ac_Right); 
          break;
        case UserAction_t::Up:
          game_inside->userActionHandler(s21::SnakeGame::ac_Forvard); 
          break;
        default:
          break;
    }
}

int **& outputFieldKeeper(){
    static int** field=fieldAllocator();
    return field;
}
int** fieldAllocator(){
    int** field=new int*[s21::field_::HEIGHT]();
    for (int i = 0; i < s21::field_::HEIGHT; i++) {
        field[i] = new int[s21::field_::WIDTH]();
    }
    return field;
}
void fieldDeleter(){
    int**& field=outputFieldKeeper();
    if(field!=nullptr){
        for(int i=0;i<s21::field_::HEIGHT;i++){
            delete[]field[i];
        }
        delete[]field;
    }
    field=nullptr;
}
void fieldReallocator(){
    fieldDeleter();
    outputFieldKeeper()=fieldAllocator();
}

void endGame(GameInfo_t& game){
    fieldDeleter();
    game.field=nullptr;
    game.next=nullptr;
    game.speed=0;
    game.level=0;
    game.pause=false;
}
