#include "tetromino.h"
#include "grid.h"
#include <iostream>
#include <vector>


int main() {
    Grid testGrid;
    std::vector<Tetromino*> testPieces;
    testPieces.push_back(new Tetromino(2));
    testGrid.addTetromino(testPieces.back());
    for(int i = 0; i < 4; i++) testGrid.movePiece(testPieces.back(), 'd');
    for(int i = 0; i < 3; i++) testGrid.rotateTetromino(testPieces.back());



    std::cout << std::endl;

    //testGrid.grid[5][4] = 'b';
    //testGrid.grid[6][4] = 'b';
    testGrid.grid[7][5] = 'g';

    testGrid.printGrid();
    std::cout << "bottom collision = " << testGrid.bottomColCheck(testPieces.back()) << std::endl;

    std::cout << "lXpos: " << testPieces.back()->lXpos 
    << " rXpos: " << testPieces.back()->rXpos << " tYpos: "  
    << testPieces.back()->tYpos << " bYpos: " << testPieces.back()->bYpos << std::endl;

    testPieces.back()->printTetromino();
    std::cout << testPieces.back()->squares[3][0] << std::endl;
    int k = 1;
    int l = 0;

    /*
    std::cout << std::endl;
    for(int i = 0; i < 19; i++) testGrid.movePiece(testPieces.back(), 'd');
    testGrid.rotateTetromino(testPieces.back());

    std::cout << std::endl; 

    testGrid.printGrid();

    std::cout << std::endl;

    testPieces.back()->printTetromino();
    std::cout << std::endl;

    testPieces.push_back(new Tetromino(2));
    testGrid.addTetromino(testPieces.back());
    for(int i = 0; i < 10; i++) testGrid.movePiece(testPieces.back(), 'd');
    testGrid.movePiece(testPieces.back(), 'l');
    testGrid.rotateTetromino(testPieces.back());
    std::cout << std::endl;
    testGrid.printGrid();
    std::cout << std::endl;
    for(int i = 0; i < 5; i++) testGrid.movePiece(testPieces.back(), 'd');
    testGrid.printGrid();
    std::cout << std::endl;
    std::cout << testGrid.bottomColCheck(testPieces.back()) << std::endl;

    */
}