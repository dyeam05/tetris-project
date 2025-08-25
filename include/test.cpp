#include <iostream>
#include "tetromino.h"
#include "grid.h"

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