# Dodecahedron games

## Contents
- [Contents](#contents)
- [General](#general)
  - [Theory](#theory)
- [Project specifications](#project-specifications)
  - [Project elements](#project-elements)
  - [User Interface API](#user-interface-api)
  - [User input handling](#user-input-handling)
- [Tests](#tests)

## General
This project is an implementation of several games, including "The Te-Tris", "The S-Snake", etc. Furthermore, it includes console (TUI) and windowed (GUI) UI for those games. The implementation languages are: C, C++. This version of the project is make for s21 specifications, more advanced versions will appear in the [GitHub repository](https://github.com/Georgiy-JO/game_dodecahedron) later. This version does not allow to have several games in the same client. Due to that installing games separately is required: install_gui_first, install_gui_second, install_tui_first, install_tui_second (for more info checkout main [Makefile](/src/Makefile)).

### Theory

Implementation of games in this project are based on [finite-state machine](/materials/Finite-state_machine.md) ideas. The structure of the project is chosen based on patterns described in [MVC_MVP_MVVM.md](/materials/MVC_MVP_MVVM.md).


## Project specifications 

As it was said before this project is meant to be an anthology of several games: **The Te-Tris**, **The S-Snake**. With two kinds of UI that can work with all the games: text user interface - console UI and graphical user interface - windowed UI. In order to support several existing games and possible new games in the future, it is necessary to determine in advance how the API of interfaces and libraries will be organized, so that all the functions will be supported and re-writings are minimized.

### Project elements

| №   | Element    |Game block| Language of <br> implementation | Description |
| --- | ---------- |---| ------------------------------- | ----------- |
| 0   | **The Te-Tris** |1| C                               | [Click](/src/brick_game/tetris/README.md)   |
| 1   | **The S-Snake**  |1| C++                             | [Click](/src/brick_game/snake/README.md)   |
| 2   | TUI |1| C                               | -   |
| 3   | GUI        |1| C++                             |-   |


### User Interface API

For the games the main game field is a matrix of ten by twenty dimension. Each element of the matrix corresponds to a "pixel" of the game field and can be in one of two states: empty or filled (different colors supported for snake game). In addition to the main field, each game has additional information that is displayed in the sidebar to the right of the game field. If the game does not have these information stubs are provided (for snake game unused fields just won't be present).
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

Due to that libraries include `GameInfo_t updateCurrentState()` function that is intended to get data for rendering in the interface and returns the structure. This function is called by the interface at some intervals to keep the interface up to date.


### User input handling

To be able to let a user effect the game state each game library have a function that accepts user input. 
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

## Tests

Game libraries are covered with unit tests. Test files are located in *tests* folder. Tests can be run from the main Makefile (/src/Makefile) and from root Makefile.