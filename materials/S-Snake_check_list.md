# The S-Snake specifications

## Practical check lists for The S-Snake game

### Main part

|Specification|State|Remove for GH|
|---|---|---|
|Implement The S-Snake game|✔️||
|The program is developed in C++ language of C++17 standard.|✔️||
|The program consist of two parts:  <br> - library that implements the logic of The S-Snake game <br> - a desktop interface.|✔️||
|A finite state machine is used to formalize the logic of the game.|✔️||
|The library conform to the specification given in [library-specification](/README.md).|✔️||
|The program library code must be in the `src/brick_game/snake` folder.|✔️|✔️(change "brick_game" folder name)|
|The program interface (GUI) code is in the `src/gui/desktop` folder.|✔️|✔️(gui->ui; desktop->gui)|
|Code follows Google Style.|✔️||
|Classes are implemented within the `s21` namespace.|✔️|✔️(rename namespace)|
|The library that implements the game logic is covered by unit tests: <br> - FMS states are checked; <br>  - transitions are checked <br>- game logic is checked; |✔️||
| The GTest library is used for testing. |✔️||
|The coverage of the library with tests is at least 80 percent.|✔️||
|The program is built using a Makefile with the standard set of targets for GNU programs:  <br> - all,  <br> - install,  <br> - uninstall,  <br> - clean,  <br> - dvi,  <br> - dist,  <br> - tests.|✔️||
|The installation directory can be choosed during installation.|✔️||
|The implementation have a GUI based on the GUI library with an API for C++17:<br> - Qt <br> - GTK+|✔️|✔️|
|The program is implemented using the MVC pattern. <br>  - There is no business logic code in the view code;<br>- There is no interface code in the model, and controller;<br> - Controllers are thin.|✔️||
|The Te-tris game logic library is copied from [The Te-tris project]([link](https://github.com/Georgiy-JO/te-tris_pet)) with minor changes. <br> - The desktop interface supports it.|✔️||
|Console interface from [The Te-tris project]([link](https://github.com/Georgiy-JO/te-tris_pet)) is taken with minor changes. <br> - it supports The S-Snake.|✔️||
|The following mechanics is present in The Snake game (Classic version):<br>- The snake must move on its own, one block ahead, when the game timer runs out.<br>- When the snake hits a "food", its length increases by one.<br>- When the length of the snake reaches 200 units, the game ends and the player wins.<br>- If a snake hits a field boundary or itself, the game ends with the player losing.<br>- The user can change the direction of the snake's movement using the arrows, and the snake can only turn left and right relative to the current direction of movement.<br>- The user can speed up the snake's movement by pressing the action key or forward key.|✔️||
|The initial length of the snake is four "pixels".|✔️||
|The playing field is 10 "pixels" wide and 20 "pixels" high.|✔️||
|Prepare a diagram showing all states and transitions between them for the implemented FMS for project submission.|✔️|✔️|

### Extras

#### 1
|Specification|State|
|---|---|
|Scoring is added to the game|✔️|
|Storing maximum points is added to the game.|✔️|
|The maximum score is stored in a file or an embedded DBMS and saved between program runs.|✔️|
|Both of these are passed and displayed by the user interface in the sidebar.|✔️| 
|The maximum score is changed during the game if the user exceeds the current maximum score.|✔️|
|Points are scored as follows: eating another food adds one or more point depending on the food kind.|✔️|

#### 2
|Specification|State|
|---|---|
|Level mechanics is added to the game. <br> - Each time a player gains 5 points, the level increases by 1. <br> - Increasing the level increases the snake's speed. <br> - The maximum number of levels is 10.|✔️|

#### 3 
|Specification|State|Remove for GH|
|---|---|---|
|Borderless version of snake is made.|❌ (Will be present in Github version)|waiting for tick here|

