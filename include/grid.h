#include "tetromino.h"

#ifndef GRID_H
#define GRID_H

class Grid { 
    public:

    //Default Constructor. Creates the grid and sets all matrix values to empty '0'.
    Grid() { 
        for(int i = 0; i < 20; i++){
            for(int j = 0; j < 10; j++) {
                grid[i][j] = '0';
            }
        }
        numSquares = 0;
        pieces = nullptr;
    }

    int numSquares;
    char grid[20][10];
    Tetromino* pieces;

    //TODO: rewrite function to use piece coordinates to add piece to grid
    void addTetromino(Tetromino* piece) {
        for(int i = 0; i < 2; i++) {
            for(int j = 0; j < 4; j++) {
                if(piece->squares[i+2][j] != '0') grid[i][j+3] = piece->squares[i+2][j];
            }
        }
        numSquares += 4;
    }


    void replaceTetromino(Tetromino* piece) {
        
    }


    void rotateTetromino(Tetromino* piece) {

        for(int i = piece->tYpos; i <= piece->bYpos; i++) {
            for(int j = piece->lXpos; j <= piece->rXpos; j++) {
                if(grid[i][j] != '0') grid[i][j] = '0';
            }
        }

        piece->rotate();

        replaceTetromino(piece);
    }

    //Moves pieces around the grid. direction char is passed as arg to determine direction of movement for piece specified in first arg. 
    void movePiece(Tetromino* piece, char direction) {
        switch (direction) {
            case 'l':
                if(!leftColCheck(piece)){
                    for(int i = piece->tYpos; i <= piece->bYpos; i++) {
                        for(int j = piece->lXpos-1; j <= piece->rXpos; j++) {
                            if(grid[i][j] != '0') {
                                grid[i][j-1] = piece->color;
                                grid[i][j] = '0';
                            }
                        }
                    }
                    piece->lXpos--;
                    piece->rXpos--;
                }
                break;

            case 'r':
                if(!rightColCheck(piece)) {
                    for(int i = piece->tYpos; i <= piece->bYpos; i++) {
                        for(int j = piece->rXpos; j >= piece->lXpos; j--) {
                            if(grid[i][j] != '0') {
                                grid[i][j+1] = piece->color;
                                grid[i][j] = '0';
                            }
                        }
                    }
                    piece->lXpos++;
                    piece->rXpos++;
                }
                break;

            case 'd':
                if(piece->bYpos < 20 && !bottomColCheck(piece)) {
                    for(int i = piece->bYpos; i >= piece->tYpos; i--) {
                        for(int j = piece->lXpos; j <= piece->rXpos; j++) {
                            if(grid[i][j] != '0') {
                                grid[i+1][j] = piece->color;
                                grid[i][j] = '0';
                            }
                        }
                    }
                    piece->tYpos++;
                    piece->bYpos++;
                }
            default:
                break;
        }
    }
    void printGrid() {
        for(int i = 0; i < 20; i++){
            for(int j = 0; j < 10; j++) {
                std::cout << grid[i][j];
            }
            std::cout << std::endl;
        }
    }

    //takes condition from movePiece down function and returns a boolean if the piece can no longer be moved down
    bool finishedFalling(Tetromino* piece) {
        if(piece->bYpos == 19) {
            return true;
        }
        if (bottomColCheck(piece)) {
                return true;
        }
            return false;
    }
    
    //checks if space underneath current piece is occupied by previous piece
    bool bottomColCheck(Tetromino* piece) {
        bool check = false;
        for(int i = piece->lXpos; i <= piece->rXpos; i++) {
            if(grid[piece->bYpos+1][i] != '0' && grid[piece->bYpos][i] != '0') {
                check = true;
                break;
            }
        }
        return check;
    }

    bool leftColCheck(Tetromino* piece) {
        bool check = false;
        if(piece->lXpos == 0) return true;
        for(int i = piece->tYpos; i <= piece->bYpos; i++) {
            if(grid[i][piece->lXpos-1] != '0' && grid[i][piece->lXpos] != '0') {
                check = true;
                break;
            }
        }
        return check;
    }

    bool rightColCheck(Tetromino* piece) {
        bool check = false;
        if(piece->rXpos == 9) return true;
        for(int i = piece->tYpos; i <= piece->bYpos; i++) {
            if(grid[i][piece->rXpos+1] != '0' && grid[i][piece->rXpos] != '0') {
                check = true;
                break;
            }
        }
        return check;
    }


    bool checkFullRow(int row) {
        bool check = true;
        for(int i = 0; i < 10; i++) {
            if(grid[row][i] == '0') check = false;
        }
        return check;
    }

    bool lineFilled(int line) {
        bool filled = true;
        for(int i = 0; i < 9; i++) {
            if(grid[line][i] == '0') filled = false;
        }
        return filled;
    }

    void lineClear(int line) {
        for(int i = 0; i < 10; i++) {
            grid[line][i] = '0';
        }
    }

    void lineShift(int line) {
        for(int i = line; i > 0; i--) {
            for(int j = 0; j < 9; j++) {
                grid[i][j] = grid[i-1][j];
            }
        }
    }

    
    void multiClear(int lines);
    
    //rotates piece CLOCKWISE by 90 degrees
    void rotate(Tetromino* piece) {
        
    } 
};

#endif