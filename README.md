# C++ Console Snake
Snake game in terminal, created using C++ and STL.

## Useful links
Before we begin, here are some useful links you can check to expand your knowledge:
- [Cpp reference](https://en.cppreference.com/) - no comments.
- [Clang format](https://clang.llvm.org/docs/ClangFormat.html) - useful C++ formatter.
- [Game loop pattern](http://gameprogrammingpatterns.com/game-loop.html) - cool article about game loops.
- [Game loop with multithreading](https://gamedev.stackexchange.com/questions/142504/game-loop-with-multithreading) - 
discussion, do you actually need multithreading in you game?

## Project
Section with pretty detailed description of the project.

### Structure
Simply, the project structure looks like this:\
\
📁ConsoleSnake - root\
&ensp;📁Source - all .cpp and .h here\
&emsp;📁App - game core\
&emsp;📁Math - math functions, structs etc.\
&emsp;📁System - console editions, helpers, macros etc.

### App loop
`ConsoleSnake\Source\App\App.h(cpp)`\
Basically, the app have a main (app) loop that validates its states and choose which app component loop to start.\
Presudo-code for app loop:
```
app_loop:
  switch app_state:
    start app_component according to app_state
```

#### App component
`ConsoleSnake\Source\App\AppComponent.h`\
App component is merely an abstract class that can be started and ticked.\
In addition, it introduces a method for returninig app state that corresponds to app component state.

### Game loop
`ConsoleSnake\Source\App\Game\Game.h(cpp)`\
App contains a pointer to game object that can tick as well as app.\
It encapsulates all game logic and can be run independently (in separate game loop).\
Pseudo-code for game loop:
```
game_loop:
  switch game_state:
    consume_player_input
    tick_actors
    check_collision
    check_end_game
    render_game
```
Actually, game tick has 2 different tick-functions, that are called depending on game state, but you can check it yourself.

### Menu loop
`ConsoleSnake\Source\App\Menu\MainMenu.h(cpp)`\
App contains a pointer to main menu object that can tick as well as app.\
It is used to handle pretty trivial menu interaction.\
Pseudo-code for game loop:
```
game_loop:
  switch game_state:
    consume_player_input
    render_menu
```
So, menu allows the player to change the app state that, on its turn, tells if the player should sit in menu or play the game.

### Additional project abstractions
In this section, we will describe some project abstractions that are not fully-concerned with game itself.

#### Console edit
`ConsoleSnake\Source\System\ConsoleEdit.h(cpp)`\
This class was introduced to simplify console editing.\
Current logic concerned only with manipulation of terminal cursor position and visibility.

#### Console renderer
`ConsoleSnake\Source\System\ConsoleRenderer.h(cpp)`\
The class allows to print data to console in a fast and convenient manner.
