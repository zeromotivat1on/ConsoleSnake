# C++ Console Snake
Snake game in terminal, created using C++ and STL in Microsoft Visual Studio 2022.

# Table of contents
1. [Useful links](#useful_links)
2. [Project](#project)\
&ensp;2.1. [Structure](#structure)\
&ensp;2.2. [App loop](#app_loop)\
&emsp;2.2.1. [App component](#app_component)\
&ensp;2.3. [Game loop](#game_loop)\
&ensp;2.4. [Menu loop](#menu_loop)\
&ensp;2.5. [Additional project files](#additional_project_files)\
&emsp;2.5.1. [Console edit](#console_edit)\
&emsp;2.5.2. [Console renderer](#console_renderer)\
&emsp;2.5.3. [Macros](#macros)
3. [Remarks](#remarks)\
&ensp;2.1. [Multithreading](#multithreading)\
&ensp;2.1. [Delta time](#delta_time)\
&ensp;2.1. [Perfectionism](#perfectionism)

## Useful links <a name="useful_links"/>
Before we begin, here are some useful links you can check to expand your knowledge:
- [Cpp reference](https://en.cppreference.com/) - no comments.
- [Clang format](https://clang.llvm.org/docs/ClangFormat.html) - useful C++ formatter.
- [Game loop pattern](http://gameprogrammingpatterns.com/game-loop.html) - cool article about game loops.
- [Game loop with multithreading](https://gamedev.stackexchange.com/questions/142504/game-loop-with-multithreading) - 
discussion, do you actually need multithreading in your game?

## Project <a name="project"/>
Section with pretty detailed description of the project.

### Structure <a name="structure"/>
Simply, the project structure looks like this:\
\
📁ConsoleSnake - root\
&ensp;📁Source - all .cpp and .h here\
&emsp;📁App - game core\
&emsp;📁Math - math functions, structs etc.\
&emsp;📁System - console editions, helpers, macros etc.

### App loop <a name="app_loop"/>
`ConsoleSnake\Source\App\App.h(cpp)`\
Basically, the app have a main (app) loop that validates its states and chooses which app component loop to start.\
You may find ```DeltaTime``` field in app or app component classes, but don't await game-engine-like tick system here.\
Presudo-code for app loop:
```
app_loop:
  switch app_state:
    start app_component according to app_state
```

#### App component <a name="app_component"/>
`ConsoleSnake\Source\App\AppComponent.h`\
App component is merely an abstract class that can be started and ticked.\
In addition, it introduces a method for returninig app state that corresponds to app component state.

### Game loop <a name="game_loop"/>
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

### Menu loop <a name="menu_loop"/>
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

### Additional project files <a name="additional_project_files">
In this section, we will describe some project files that are not fully-concerned with game itself.

#### Console edit <a name="console_edit">
`ConsoleSnake\Source\System\ConsoleEdit.h(cpp)`\
This class was introduced to simplify console editing.\
Current logic concerned only with manipulation of terminal cursor position and visibility.

#### Console renderer <a name="console_renderer">
`ConsoleSnake\Source\System\ConsoleRenderer.h(cpp)`\
The class allows to print data to console in a fast and convenient manner.

#### Macros <a name="macros">
`ConsoleSnake\Source\System\Macros.h(cpp)`\
This header defines several macro-statements to either represent sort of option or simplify writing code.

## Remarks <a name="remarks">
Here, we would like to add several answears to possible questions.

### Multithreading <a name="multithreading">
In fact, the project uses multithreading, but, frankly, only in scientific purposes.\
You might find a method in game app component that renders current play time on the console, next to game map.\
Basically, project can be freely run on 1 thread, just remove or comment separate thread specific code in game app component.

### Delta time <a name="delta_time">
You can find ```DeltaTime``` field in app components and app itself, but don't let it confuse you.\
This field is simply used for thread sleep after game tick to make game run a bit slowly and smoothly.\
At least, it helped on our hardware, feel free to modify its value or even rewrite tick logic.

### Perfectionism <a name="perfectionism">
Nothing in this world is perfect, neither this project.\
Through frame by frame debugging we faced several issues that need to be fixed. Here is the list:
- [ ] Move snake head after moving body (i.e reduce edge case bugs).
- [ ] Reconsider game loop execution sequence in order to improve gaming experience.
