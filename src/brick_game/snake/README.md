# Dodecahedron games: The S-Snake 0.1
This part of the project, is an implementation of the Snake game in the C++ programming language in the object-oriented programming paradigm.

# Contents
- [Dodecahedron games: The S-Snake 0.1](#dodecahedron-games-the-s-snake-01)
- [Contents](#contents)
  - [General](#general)
  - [Theory](#theory)
    - [Finite-state machines](#finite-state-machines)
    - [The Snake](#the-snake)
      - [Classic Snake](#classic-snake)
      - [Borderless Snake](#borderless-snake)
      - [History](#history)
- [MVC Pattern](#mvc-pattern)
  - [Main idea](#main-idea)
  - [The model](#the-model)
    - [MVP Pattern](#mvp-pattern)
    - [MVVM Pattern](#mvvm-pattern)
  - [The S-Snake specifications](#the-s-snake-specifications)

## General

This part of the project in this folder is a library responsible for implementing the game logic. The GUI implementations (terminal and windowed) are located at: */src/gui*(!!!!!).

The developed game library also can be connected to the console interface (similar to one, that is used in the separate **The Te-tris** project [link](https://github.com/Georgiy-JO/te-tris_pet)), realization of which can be found at: /src/brick_game/tetris (!!!!!) The console interface fully support the game. At the same time project files include [**"The Te-tris"** game](https://github.com/Georgiy-JO/te-tris_pet) too, due to the fact that the GUE interface fully supports it.  
 
## Theory 
### [Finite-state machines](/materials/Finite-state_machine.md)
### [MVC & MVP & MVVM](/materials/MVC_MVP_MVVM.md)

Logic of the game is formalized using finite-state machine and has the following structure:

#### Classic snake FSM
![The_classic_s-nake_FSM](/misc/images/FSM_classic_snake.png " finite-state machine of The S-Snake: Classic")

#### Borderless snake FSM
![The_borderless_s-nake_FSM](/misc/images/FSM_borderless_snake.png " finite-state machine of The S-Snake: Borderless")

### The Snake

![Snake](/misc/images/snake-game.png)

#### Classic Snake
The player controls a snake that moves forward continuously. The player changes the direction of the snake by using the arrows. The goal of the game is to collect "apples" that appear on the playing field. The player must avoid hitting the walls of the playing field. After "eating" the next "apple", the length of the snake increases by one. The player wins when the snake reaches the maximum size (originally 200 "pixels"). If the snake hits a boundary of the playing field or itself, the player loses.

#### Borderless Snake
Has the same set of rules as the classical one, but with the mageor difference - lack of borders. In this version if the snake touches left edge of the playing field it appears at the right, if touches top edge - appers at the down one, and the same works backwards.

#### History
The game was based on another game called Blockage. It had two players controlling characters that left a trail that you couldn't run into. The player who lasted the longest won. In 1977, Atari released Worm, which was now a single player game. The most popular version of the game is probably the 1997 version released by the Swedish company Nokia for their Nokia 6110 phone, developed by Taneli Armanto.

## [The S-Snake specifications](/materials/S-Snake_check_list.md)


## Notes for future
- moving food sounds interesting...
- Check if the name will be written to record list if the user make a record, but this record is lower than theirs highest.