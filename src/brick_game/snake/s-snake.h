#ifndef S_SNAKE_H
#define S_SNAKE_H

#ifdef __cplusplus
extern "C" {
#endif

typedef enum{
    RelativeSize=0,
    Width=10,
    Height=20,
    Second_RelativeSize=-1,
    Second_Width=4,
    Second_Height=4
}FieldSize_c;

typedef struct {
    int **field;
    int **next;
    int score;
    int high_score;
    int level;
    int speed;
    int pause;
} GameInfo_t;

typedef enum {
    Start,
    Pause,
    Terminate,
    Left,
    Right,
    Up,
    Down,
    Action
} UserAction_t;

GameInfo_t updateCurrentState();
void userInput(UserAction_t action, bool hold);

#ifdef __cplusplus
}
#endif

#endif //S_SNAKE_H