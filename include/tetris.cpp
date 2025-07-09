/*
* Tetris Project in C++ with raylib
* Author: Daniel Yeaman
*
* Description: Working on writing a tetris program from scratch to learn more about C++, external libraries, UI creation, and game design. 
* Feel free to read and use code for inspiration and leave feedback.
*/


#include <iostream>
#include "tetromino.h"
#include "grid.h"

int score = 0; //global score variable. stores the current game score
int level = 0; //global level variable. stores the current game level. level increases 1 time for ever 10 lines cleared. 
int linesCleared; //global variable storing total lines cleared. level increases 1 time for ever 10 lines cleared.
int fallingSpeed; //global variable storing the speed in which the tetrominos fall. speed is increased every level up.

int main() {
    Tetromino* lineTest = new Tetromino(1, 'r');
    Tetromino* reverseLTest = new Tetromino(2, 'r');
    Tetromino* lTest = new Tetromino(3, 'r');
    Tetromino* squareTest = new Tetromino(4, 'r');
    Tetromino* zTest = new Tetromino(5, 'r');
    Tetromino* reverseZTest = new Tetromino(6, 'r');
    Tetromino* tTest = new Tetromino(7, 'r');

    tTest->printTetromino();

    Grid* gridTest = new Grid();
    gridTest->addTetromino(tTest);
    gridTest->printgrid();
    std::cout << std::endl;
    gridTest->movePiece(reverseLTest, 'r');
    gridTest->movePiece(reverseLTest, 'r');
    gridTest->movePiece(reverseLTest, 'r');
    gridTest-> printgrid();
    std::cout << std::endl;

    gridTest->addTetromino(squareTest);
    gridTest->printgrid();


    delete lineTest;
    delete reverseLTest;
    delete lTest;
    delete squareTest;
    delete zTest;
    delete reverseZTest;
    delete tTest;
    delete gridTest;

    return 0;
};