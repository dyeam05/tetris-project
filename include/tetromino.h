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

#ifndef TETROMINO_H
#define TETROMINO_H

#include <iostream>

class Tetromino { 
    public:
    // Default Constructor. sets all int values to 0, color value to empty char and falling to false.
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
                std::cout << squares[i][j];
            }
            std::cout << std::endl;
        }
    }

    int squares[4][4]; //4x4 matrix that stores the shape of the tetromino
    int lXpos; //stores the x position of the left-most square in the tetromino relative to the game board grid.
    int rXpos; //stores the x position of the right-most square in the tetromino relative to the game board grid.
    int tYpos; //stores the y position of the top-most square tetromino relative to the game board grid.
    int bYpos; //stores the y position of the bottom-most square in the tetromino relative to the game board grid.
    int id; //stores the value (1-7) of the tetromino shape
    char color; //color value represented by single character: 't' = teal, 'b' = blue, 'o' = orange, 'y' = yellow, 'g' = green, 'p' = purple, 'r' = red
    bool falling; //determines if the tetromino is still in play, or that it is still falling down the game board.
    int numSquares; //number of squares 
    void rotate();
    void changeX(int x);
    void changeY(int y);
    void changePos(int newx, int newy);
};

#endif