#include "tetromino.h"
#include "grid.h"
#include <iostream>
#include <vector>


int main() {
    Grid testGrid;
    std::vector<Tetromino*> testPieces;
    Tetromino* ghostPiece = new Tetromino();
    for(int i = 2; i < 3; i++) {
        testPieces.push_back(new Tetromino(i));
        testGrid.addTetromino(testPieces.back());
        testGrid.addGhost(testPieces.back(), ghostPiece);
        ghostPiece->printTetromino();
        for(int i = 0; i < 4; i++) testGrid.movePiece(testPieces.back(), 'd');
        testGrid.rotateTetromino(testPieces.back());
        testGrid.removeTetromino(ghostPiece);
        std::cout << ghostPiece->orientation << std::endl;
        ghostPiece->rotate();
        ghostPiece->printTetromino();
        std::cout << ghostPiece->orientation << std::endl;
        testGrid.addGhost(testPieces.back(), ghostPiece);
        
        
        //std::cout << std::endl << "piece coords: tY=" << testPieces.back()->tYpos << ", bY=" << testPieces.back()->bYpos << ", lX=" << testPieces.back()->lXpos << ", rX=" << testPieces.back()->rXpos << std::endl; 
        //std::cout << std::endl << "ghost coords: tY=" << ghostPiece->tYpos << ", bY=" << ghostPiece->bYpos << ", lX=" << ghostPiece->lXpos << ", rX=" << ghostPiece->rXpos << std::endl; 
        testGrid.printGrid();

        testGrid.clearGrid();
        std::cout << std::endl;
    }



}

