#include "tetromino.h"

class Grid { 
    public:

    //Default Constructor. Creates the grid and sets all matrix values to empty '0'.
    Grid() { 
        for(int i = 0; i < 20; i++){
            for(int j = 0; j < 10; j++) {
                grid[i][j] = 0;
            }
        }
        numSquares = 0;
        pieces = nullptr;
    }

    int numSquares;
    int grid[20][10];
    Tetromino* pieces;

    void addTetromino(Tetromino* piece) {
        for(int i = 0; i < 2; i++) {
            for(int j = 0; j < 4; j++) {
                if(piece->squares[i+2][j] == 1) grid[i][j+3] = piece->squares[i+2][j];
            }
        }
        numSquares += 4;
    }

    //Moves pieces around the grid. direction char is passed as arg to determine direction of movement for piece specified in first arg. 
    void movePiece(Tetromino* piece, char direction) {
        switch (direction) {
            case 'l':
                if(piece->lXpos > 0 
                    && grid[piece->tYpos][piece->lXpos-1] != 1 
                    && grid[piece->bYpos][piece->lXpos-1] != 1) {
                    for(int i = piece->tYpos; i <= piece->bYpos; i++) {
                        for(int j = piece->lXpos-1; j <= piece->rXpos; j++) {
                            if(grid[i][j] == 1) {
                                grid[i][j-1] = 1;
                                grid[i][j] = 0;
                            }
                        }
                    }
                    piece->lXpos--;
                    piece->rXpos--;
                }
                break;

            case 'r':
                if(piece->rXpos < 9 
                    && grid[piece->tYpos][piece->rXpos+1] != 1 
                    && grid[piece->bYpos][piece->rXpos+1] != 1) {
                    for(int i = piece->tYpos; i <= piece->bYpos; i++) {
                        for(int j = piece->rXpos; j >= piece->lXpos; j--) {
                            if(grid[i][j] == 1) {
                                grid[i][j+1] = 1;
                                grid[i][j] = 0;
                            }
                        }
                    }
                    piece->lXpos++;
                    piece->rXpos++;
                }
                break;

            case 'd':
                break;
            default:
                break;
        }
    }
    void printgrid() {
        for(int i = 0; i < 20; i++){
            for(int j = 0; j < 10; j++) {
                std::cout << grid[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }
    
    //Ensures that the given tetromino will not overlap with another piece on the board.
    //This looks really inefficient. Work on fixing later.
    //Write an algorithm to speed this up.
    bool overlapCheck(Tetromino* piece) {
        if(piece->lXpos > 0 
            && piece->rXpos < 10 
            && piece->tYpos > 0 
            && piece->bYpos < 20
            && grid[piece->tYpos][piece->lXpos - 1] == 0 
            && grid[piece->bYpos][piece->lXpos - 1] == 0
            && grid[piece->tYpos][piece->lXpos + 1] == 0 
            && grid[piece->bYpos][piece->lXpos + 1] == 0
            && grid[piece->tYpos][piece->rXpos - 1] == 0 
            && grid[piece->bYpos][piece->rXpos - 1] == 0
            && grid[piece->tYpos][piece->rXpos + 1] == 0 
            && grid[piece->bYpos][piece->rXpos + 1] == 0) {
                return true;
            }
        
        return false;
    }
    void lineClear(int line) {
        for(int i = 0; i < 10; i++) {
            grid[line][i] = 0;
        }
    }
    void lineShift(int line);
    void multiClear(int lines);
};