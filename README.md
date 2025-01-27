# Dodecahedron games

## Contents
- [Dodecahedron games](#dodecahedron-games)
  - [Contents](#contents)
  - [General](#general)
    - [Project elements](#project-elements)
  - [Theory](#theory)
      - [BrickGame game collection v. 1.0](#brickgame-game-collection-v-10)
- [Specification for the game library from the BrickGame game collection](#specification-for-the-game-library-from-the-brickgame-game-collection)

## General
This project is an implementation of several games, including "The Te-Tris", "The S-Snake", etc. Furthermore, it includes console (TUI) and windowed (GUI) UI for those games. The implementation languages are: C, C++. 

## Theory

Implementation of games in this project are based on [finite-state machine](/materials/Finite-state_machine.md). The structure of the project is chosen based on patterns described in [MVC_MVP_MVVM.md](/materials/MVC_MVP_MVVM.md) ideas.


## Project specifications 

As it was said before this project is meant to be an anthology of several games: **The Te-Tris**, **The S-Snake**. With two kinds of UI that can work with all the games: text user interface - console UI and graphical user interface - windowed UI. In order to support several existing games and possible new games in the future, it is necessary to determine in advance how the API of interfaces and libraries will be organized, so that all the functions will be supported and re-writings are minimized.

|Games block| Games list|
|---|---|
|1|**The Te-Tris**<br>**The S-Snake**|
|2||

### Project elements

| №   | Element    |Game block| Language of <br> implementation | Description |
| --- | ---------- |---| ------------------------------- | ----------- |
| 0   | **The Te-Tris** |1| C                               | [Click](/src/brick_game/tetris/README.md)   |
| 1   | **The S-Snake**  |1| C++                             | [Click](/src/brick_game/snake/README.md)   |
| 2   | TUI |1| C                               | -   |
| 3   | GUI        |1| C++                             | [Click]()   |


### User Interface API

#### The first game block

For these games the main game field is a matrix of ten by twenty dimension. Each element of the matrix corresponds to a "pixel" of the game field and can be in one of two states: empty or filled (different colors supported). In addition to the main field, each game has additional information that is displayed in the sidebar to the right of the game field. If the game does not have these information stubs are provided.
To visualize this UI part of the program expect to receive game state information in the following format from a game library.
``` C
typedef struct {
    int **field;
    int **next;
    int score;
    int high_score;
    int level;
    int speed;
    int pause;
} GameInfo_t;
```

Due to that libraries include `updateCurrentState` function that is intended to get data for rendering in the interface and returns the structure. This function is called from the interface at some intervals to keep the interface up to date.


### User input handling

To be able to let a user effect the game state each game library have a function that accepts user input. 

#### The first game block

The original console of these games had eight physical buttons: start game, pause, end game, action, and four arrows - let's take these as basic and add more if it will be required. 
- For more information about controls see [*controls tables*](/materials/Controls_tables.md)

At the behalf of a library the `userInput` function takes as input the user `action` and an additional parameter `hold`, which is responsible for pressing the button. It is organized the following way:
```C
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

void userInput(UserAction_t action, bool hold);
```

