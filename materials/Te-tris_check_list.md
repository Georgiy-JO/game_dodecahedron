
# The Te-Tris specifications

|Check/Note|Info|Change for GH|
|---|---|---|
||Implementation the BrickGame v1.0 aka Tetris program aka The Te-Tris 1.0| |
||The program is developed in C language of C11 standard using gcc compiler.||
||The program consists of two parts: a library implementing the logic of the tetris game, and a terminal interface (GUI) (done with `ncurses` library).||
||A finite-state machine is used to formalize the logic of the game.||
|:<br> <br>  |The library has a function that accepts user input and a function that outputs a matrix that describes the current state of the playing field:<br> - void userInput(...)<br>- GameInfo_t updateCurrentState()||
||The program library code is located in the `src/brick_game/tetris` folder.|✔️(change "brick_game" folder name)|
||The program interface code is located in the `src/gui/cli` folder.|✔️️(gui->ui; cli ->tui) |
||The program can be built using a Makefile with the standard set of targets for GNU-programs: *all*, *install*, *uninstall*, *clean*, *dvi*, *dist*, *test*, *gcov_report (and other). Installation directory can be arbitrary.||
||Code is written in Google Style.||
||Full coverage of the library with unit tests, using the `check` library is prepared (inc tests can be run on Darwin/Ubuntu OS). The coverage of the library with game logic with tests is 80+ percent.||
|:<br><br><br><br><br><br><br><br>|The following mechanics are in the game:<br>  - Rotation of pieces;<br>  - Moving pieces horizontally;<br>   - Acceleration of the piece's fall (when the button is pressed, the figure moves all the way down);<br>  - Display of the next piece;<br>  - Destruction of filled raws;<br>  - End of the game when the top border of the playing field is reached;<br>   - Include [all sorts of pieces]( /misc/images/Tetrinos.png) from the original game.<br> - After reaching the lower boundary of the field or contacting another figure, the figure stops. After that, the next piece, shown in the preview, is generated.||
|:<br><br><br><br><br><br><br><br>|Support for all the buttons provided on the physical console for control:<br>  - Start game,<br>  - Pause,<br>  - End game,<br>   - Left arrow - movement of the piece to the left,<br>  - Right arrow - movement of the piece to the right,<br>   - Down arrow - piece falls,<br>   - Up arrow is not used in this game,<br>   - Action (piece rotation).||
||The playing field of game match the dimensions of the console's playing field - ten "pixels" wide and twenty "pixels" high. GUI interface is wider to support square pixies.||
||The library interface correspond to the description and idea from the [Project structure explanation](#project-structure-explanation).|
||The UI supports rendering of the playing field and additional information.||
||[Diagram describing the used FSM](/misc/images/FSM_te-tris.png) (its states and all possible transitions) is included.||
|:<br><br><br><br>|Scoring and game record are implemented:<br>  - scoring;<br>  - storing maximum points.<br>  - The maximum number of points is stored in a file.<br>  - The maximum number of points changes during the game, if the user exceeds the current maximum score.|
||Points are accrued as follows:<br>  - 1 row is 100 points;<br>  - 2 rows is 300 points;<br>  - 3 rows is 700 points;<br>  - 4 rows is 1500 points;||
|:<br><br><br>|Level mechanic is implemented:<br>   - Each time a player gains 600 points, the level increases by 1.<br> - Increasing the level boosts the speed at which the pieces move. <br> - The maximum number of levels is 10.||


