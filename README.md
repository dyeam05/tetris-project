# Tetris Clone Project with Raylib

An almost working clone of tetris in C++ with the Raylib Library

This project aims to implement the modern forms of tetris in a (n eventually) lightweight application.


## To Install:
- Clone this repo using `git clone https://github.com/dyeam05/tetris-project-tests` in terminal
- Download [CMake](https://cmake.org/download/)
- Input the following lines in your terminal to build the game:

```bash
cmake -B build
cmake --build build
```

- This should build the game in a newly created build directory
- Once this has been sucessfully completed, run the built game with either `./build/Debug/tetris.exe` on windows, or `./build/tetris` on Linux or macOS


### Important Note:
I have been using the [raylib-quickstart](https://github.com/raylib-extras/raylib-quickstart) template to develop this project, so to make installation easier, I have moved all of those files to the quickstart-dev-env folder. This folder can be ignored.

## To Play:

This project uses controls similar to other, web-based tetris versions:

- Left/Right Arrow Keys: Move piece left and right
- Up Arrow: Rotate Piece
- Down Arrow: Soft Drop Piece
- Space Bar: Hard Drop Piece

- C: Hold Piece
- P: Pause Game
- R: Restart Game (on Game Over)

## Bugs:

This project is still a WIP, so there are plenty of bugs to be fixed.
Some features and mechanics haven't yet been fully implemented, so there are some partially completed functions that might cause game errors
For now, all bugs that I discover can be found in txtfiles/BUGS.txt