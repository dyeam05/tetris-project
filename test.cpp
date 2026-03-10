#include "tetromino.h"
#include "grid.h"
#include <iostream>



int main() {
    Grid testGrid;
    Tetromino* testPiece = new Tetromino(7);
    testGrid.addTetromino(testPiece);
    testGrid.printGrid();

    std::cout << std::endl;
    for(int i = 0; i < 4; i++) testGrid.movePiece(testPiece, 'd');
    testGrid.printGrid();

    std::cout << std::endl;

    testPiece->printTetromino();
    std::cout << std::endl;

    for(int i = 0; i < 4; i++) {
        std::cout << "Grid w/ rotated piece:" << std::endl;
        testGrid.rotateTetromino(testPiece);
        std::cout << "rotated piece" << std::endl;
        testPiece->printTetromino();
        //testGrid.printGrid();
        std::cout << std::endl;
    }
}