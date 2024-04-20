# Maze and Snake Game

## Overview
This repository contains two console-based games implemented in C++: Maze and Snake. 

### Maze Game
In the Maze game, players navigate a maze represented in the console environment. The goal is to guide the player piece from the starting position (top-left corner) to the finish line (bottom-right corner) by using the arrow keys to move up, down, left, or right. The maze contains empty cells, walls, and bombs. Players cannot move through walls, and if the player piece encounters a bomb, the game ends. Winning occurs when the player reaches the finish line.

### Snake Game
In the Snake game, players control a snake moving around the console environment. The snake grows in length each time it eats food (represented by a blinking cell). The objective is to guide the snake to eat food and grow to a length of 60 units without colliding with the walls or itself. Collisions result in the end of the game.

## Implementation Details
Both games are implemented using classes to encapsulate functionality. The necessary classes include `Cell` for each cell in the game grid and `Maze` for the Maze game, and `Unit` for each unit of the snake's body and `Snake` for the Snake game. Additional classes can be added as needed.

All operations are implemented as member functions of the respective classes. Each function performs a single task, and functions are kept as small as possible to enhance code readability and maintainability.

### Maze Game Functions
- `printWalls`: Print the walls of the maze.
- `printField`: Print the entire maze field including walls and bombs.
- `movePlayer`: Move the player piece within the maze.
- `winCheck`: Check if the player has reached the finish line.
- `bombCheck`: Check if the player has encountered a bomb.

### Snake Game Functions
- `movePlayer`: Move the snake within the game grid.
- `showOrHideFood`: Display the food cell with blinking animation.
- `newFood`: Generate a new food cell after the snake eats the current one.
- `increaseSnakeLength`: Increase the length of the snake after eating food.
- `validPress`: Validate the direction change for the snake.

## Getting Started
- For the Maze game, compile and run `Maze Game.cpp`.
- For the Snake game, compile and run `Snake Game.cpp`.

## Contributions
Contributions and feedback are welcome. Feel free to enhance the existing games, add new features, or suggest improvements.
