/*
* Tetris Project in C++ with raylib
* Author: Daniel Yeaman
*
* Description: Working on writing a tetris program from scratch to learn more about C++, external libraries, UI creation, and game design. 
* Feel free to read and use code for inspiration and leave feedback.
*/


#include <iostream>

using namespace std;

int score = 0; //global score variable. stores the current game score
int level = 0; //global level variable. stores the current game level. level increases 1 time for ever 10 lines cleared. 
int linesCleared; //global variable storing total lines cleared. level increases 1 time for ever 10 lines cleared.
int fallingSpeed; //global variable storing the speed in which the tetrominos fall. speed is increased every level up.


/*
*   Tetromino object. 
*   Each tetromino block on the board is created with this class. the tetromino shapes is stored in an int matrix 'squares'. 
*   This 4x4 matrix is populated with zeros until the buildTetromino() method is called. this method uses the 'id' variable in a switch to determine which shape is to be built.
*   Each shape is stored within the matrix, with arbitrary value determining its position. 
*   
*   Variables are as follows:
*   int squares -> 4x4 matrix that stores the shape of the tetromino
*   int id -> stores the value (1-7) of the tetromino shape
*   char color -> color value represented by single character: 't' = teal, 'b' = blue, 'o' = orange, 'y' = yellow, 'g' = green, 'p' = purple, 'r' = red
*   int xpos -> stores the x position of the tetromino relative to the game board grid
*   int ypos -> stores the y position of the tetromino relative to the game board grid
*   bool falling -> determines if the tetromino is still in play, or that it is still falling down the game board.
*   
*/
class Tetromino { 
    public:
    /* Default Constructor. sets all int values to 0, color value to empty char and falling to false. */
    Tetromino() { 
        id = 0;
        color = ' ';
        lXpos = 0;
        rXpos = 0;
        tYpos = 0;
        bYpos = 0;
        falling = false;
    }

    Tetromino(int id, char color) {
        this->id = id;
        this->color = color;
        falling = true;

        for(int i = 0; i < 4; i++){
            for(int j = 0; j < 4; j++) {
                squares[i][j] = 0;
            }
        }

        buildTetromino();
    }

    void buildTetromino() {
        switch (id) {
            case 1: //straight line piece
                squares[2][0] = 1;
                squares[2][1] = 1;
                squares[2][2] = 1;
                squares[2][3] = 1;
                lXpos = 3;
                rXpos = 6;
                tYpos = 0;
                bYpos = 0;
                break;
            
            case 2: //reverse l piece
                squares[2][0] = 1;
                squares[3][0] = 1;
                squares[3][1] = 1;
                squares[3][2] = 1;
                lXpos = 3;
                rXpos = 5;
                tYpos = 0;
                bYpos = 1;
                break;
            
            case 3: //l piece
                squares[2][2] = 1;
                squares[3][0] = 1;
                squares[3][1] = 1;
                squares[3][2] = 1;
                lXpos = 3;
                rXpos = 5;
                tYpos = 0;
                bYpos = 1;
                break;
            
            case 4: //square piece
                squares[2][1] = 1;
                squares[2][2] = 1;
                squares[3][1] = 1;
                squares[3][2] = 1;
                lXpos = 4;
                rXpos = 5;
                tYpos = 0;
                bYpos = 1;
                break;

            case 5: //z piece
                squares[2][0] = 1;
                squares[2][1] = 1;
                squares[3][1] = 1;
                squares[3][2] = 1;
                lXpos = 3;
                rXpos = 5;
                tYpos = 0;
                bYpos = 1;
                break;

            case 6: //reverse z piece
                squares[2][1] = 1;
                squares[2][2] = 1;
                squares[3][0] = 1;
                squares[3][1] = 1;
                lXpos = 0;
                rXpos = 3;
                tYpos = 0;
                bYpos = 1;
                break;

            case 7: //t piece
                squares[2][1] = 1;
                squares[3][0] = 1;
                squares[3][1] = 1;
                squares[3][2] = 1;
                lXpos = 3;
                rXpos = 5;
                tYpos = 0;
                bYpos = 1;
            default:
                break;
        }
    }

    void printTetromino() {
        for(int i = 0; i < 4; i++) {
            for(int j = 0; j < 4; j++) {
                cout << squares[i][j];
            }
            cout << endl;
        }
    }

    int squares[4][4]; //4x4 matrix that stores the shape of the tetromino
    int lXpos; //stores the x position of the left-most square in the tetromino relative to the game board grid.
    int rXpos; //stores the x position of the right-most square in the tetromino relative to the game board grid.
    int tYpos; //stores the y position of the tetromino relative to the game board grid
    int bYpos;
    int id; //stores the value (1-7) of the tetromino shape
    char color; //color value represented by single character: 't' = teal, 'b' = blue, 'o' = orange, 'y' = yellow, 'g' = green, 'p' = purple, 'r' = red
    bool falling; //determines if the tetromino is still in play, or that it is still falling down the game board.
    int numSquares; //number of squares 
    void rotate();
    void changeX(int x);
    void changeY(int y);
    void changePos(int newx, int newy);
};

class Grid { 
    public:

    /*Default Constructor. Creates the grid and sets all matrix values to empty '0'.*/
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
                grid[i][j+3] = piece->squares[i+2][j];
            }
        }
        numSquares += 4;
    }

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
                cout << grid[i][j] << " ";
            }
            cout << endl;
        }
    }

    bool overlapCheck(Tetromino* piece) {
        return false;
    }
    void lineClear(int line);
    void lineShift(int line);
    void multiClear(int lines);
};


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
    cout << endl;
    gridTest->movePiece(reverseLTest, 'r');

    gridTest-> printgrid();

    delete lineTest;
    delete reverseLTest;
    delete lTest;
    delete squareTest;
    delete zTest;
    delete reverseZTest;
    delete tTest;

    return 0;
};