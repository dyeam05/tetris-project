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

    Tetromino(int id) {
        this->id = id;
        color = '0';
        falling = true;

        for(int i = 0; i < 4; i++){
            for(int j = 0; j < 4; j++) {
                squares[i][j] = '0';
            }
        }

        buildTetromino();
    }
 
    void buildTetromino() {
        switch (id) {
            case 1: //straight line piece
                color = 't';
                squares[2][0] = 't';
                squares[2][1] = 't';
                squares[2][2] = 't';
                squares[2][3] = 't';
                lXpos = 3;
                rXpos = 6;
                tYpos = 0;
                bYpos = 0;
                break;
            
            case 2: //reverse l piece
                color = 'b';
                squares[2][0] = 'b';
                squares[3][0] = 'b';
                squares[3][1] = 'b';
                squares[3][2] = 'b';
                lXpos = 3;
                rXpos = 5;
                tYpos = 0;
                bYpos = 1;
                break;
            
            case 3: //l piece
                color = 'o';
                squares[2][2] = 'o';
                squares[3][0] = 'o';
                squares[3][1] = 'o';
                squares[3][2] = 'o';
                lXpos = 3;
                rXpos = 5;
                tYpos = 0;
                bYpos = 1;
                break;
            
            case 4: //square piece
                color = 'y';
                squares[2][1] = 'y';
                squares[2][2] = 'y';
                squares[3][1] = 'y';
                squares[3][2] = 'y';
                lXpos = 4;
                rXpos = 5;
                tYpos = 0;
                bYpos = 1;
                break;

            case 5: //z piece
                color = 'g';
                squares[2][0] = 'g';
                squares[2][1] = 'g';
                squares[3][1] = 'g';
                squares[3][2] = 'g';
                lXpos = 3;
                rXpos = 5;
                tYpos = 0;
                bYpos = 1;
                break;

            case 6: //reverse z piece
                color = 'p';
                squares[2][1] = 'p';
                squares[2][2] = 'p';
                squares[3][0] = 'p';
                squares[3][1] = 'p';
                lXpos = 3;
                rXpos = 5;
                tYpos = 0;
                bYpos = 1;
                break;

            case 7: //t piece
                color = 'r';
                squares[2][1] = 'r';
                squares[3][0] = 'r';
                squares[3][1] = 'r';
                squares[3][2] = 'r';
                lXpos = 3;
                rXpos = 5;
                tYpos = 0;
                bYpos = 1;
            default:
                break;
        }
    }

    void clear() {
        for(int i = 0; i < 4; i++) {
            for(int j = 0; j < 4; j++) {
                squares[i][j] = '0';
            } 
        }
    }

    void rotate() {
        clear();
        orientation++;
        if(orientation == 4) orientation = 0;
        switch (id) {
            case 1: //straight line piece
                if(orientation == 0){
                    squares[2][0] = color;
                    squares[2][1] = color;
                    squares[2][2] = color;
                    squares[2][3] = color;
                    lXpos -= 1;
                    rXpos += 2;
                    tYpos += 2;
                    bYpos -= 1;
                }
                else if(orientation == 1) {
                    squares[0][0] = color;
                    squares[1][0] = color;
                    squares[2][0] = color;
                    squares[3][0] = color;
                    rXpos -= 3;
                    tYpos -= 2;
                    bYpos += 1;
                }
                else if(orientation == 2) {
                    squares[1][0] = color;
                    squares[1][1] = color;
                    squares[1][2] = color;
                    squares[1][3] = color;
                    rXpos += 3;
                    tYpos += 1;
                    bYpos -= 2;
                }
                else {
                    squares[0][1] = color;
                    squares[1][1] = color;
                    squares[2][1] = color;
                    squares[3][1] = color;
                    lXpos += 1;
                    rXpos -= 2;
                    tYpos -= 1;
                    bYpos += 2;
                }   
                break;
            
            case 2: //reverse l piece
                if(orientation == 0){
                    squares[2][0] = color;
                    squares[3][0] = color;
                    squares[3][1] = color;
                    squares[3][2] = color;
                    lXpos -= 1;
                    tYpos += 1;
                }
                else if(orientation == 1) {
                    squares[1][1] = color;
                    squares[1][0] = color;
                    squares[2][0] = color;
                    squares[3][0] = color;
                    rXpos -= 1;
                    tYpos -= 1;
                    bYpos += 1;
                }
                else if(orientation == 2) {
                    squares[2][2] = color;
                    squares[1][0] = color;
                    squares[1][1] = color;
                    squares[1][2] = color;
                    rXpos += 1;
                    bYpos += 1;
                }
                else {
                    squares[3][1] = color;
                    squares[3][2] = color;
                    squares[2][2] = color;
                    squares[1][2] = color;
                    lXpos += 1;
                    bYpos += 1;
                }
                break;
            
            case 3: //l piece
                if(orientation == 0){
                    squares[2][2] = color;
                    squares[3][0] = color;
                    squares[3][1] = color;
                    squares[3][2] = color;
                    lXpos += 1;
                    tYpos += 1;
                }
                else if(orientation == 1) {
                    squares[3][1] = color;
                    squares[1][0] = color;
                    squares[2][0] = color;
                    squares[3][0] = color;
                    rXpos -= 1;
                    tYpos -= 1;
                }
                else if(orientation == 2) {
                    squares[2][0] = color;
                    squares[1][0] = color;
                    squares[1][1] = color;
                    squares[1][2] = color;
                    rXpos += 1;
                    bYpos += 1;
                }
                else {
                    squares[1][1] = color;
                    squares[3][2] = color;
                    squares[2][2] = color;
                    squares[1][2] = color;
                    lXpos += 1;
                    bYpos += 1;
                }

                break;
            
            case 4: //square piece. does nothing lol
                break;

            case 5: //z piece
                if(orientation == 0 || orientation == 2){
                    squares[2][0] = color;
                    squares[2][1] = color;
                    squares[3][1] = color;
                    squares[3][2] = color;
                    rXpos += 1;
                    tYpos += 1;
                }
                else if(orientation == 1 || orientation == 3) {
                    squares[3][0] = color;
                    squares[2][0] = color;
                    squares[2][1] = color;
                    squares[1][1] = color;
                    rXpos -= 1;
                    tYpos -= 1;
                }
                break;

            case 6: //reverse z piece
                if(orientation == 0 || orientation == 2){
                    squares[2][1] = color;
                    squares[2][2] = color;
                    squares[3][0] = color;
                    squares[3][1] = color;
                    rXpos += 1;
                    tYpos += 1;
                }
                else if(orientation == 1 || orientation == 3) {
                    squares[3][1] = color;
                    squares[2][1] = color;
                    squares[2][0] = color;
                    squares[1][0] = color;
                    rXpos -= 1;
                    tYpos -= 1;
                }

                break;

            case 7: //t piece
                if(orientation == 0){
                    squares[2][1] = color;
                    squares[3][0] = color;
                    squares[3][1] = color;
                    squares[3][2] = color;
                    lXpos += 1;
                    tYpos += 1;
                }
                else if(orientation == 1) {
                    squares[2][1] = color;
                    squares[1][0] = color;
                    squares[2][0] = color;
                    squares[3][0] = color;
                    rXpos -= 1;
                    tYpos -= 1;
                }
                else if(orientation == 2) {
                    squares[2][1] = color;
                    squares[1][0] = color;
                    squares[1][1] = color;
                    squares[1][2] = color;
                    rXpos += 1;
                    bYpos += 1;
                }
                else {
                    squares[2][1] = color;
                    squares[3][2] = color;
                    squares[2][2] = color;
                    squares[1][2] = color;
                    lXpos += 1;
                    bYpos += 1;
                }


                break;

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

    char squares[4][4]; //4x4 matrix that stores the shape of the tetromino
    int lXpos; //stores the x position of the left-most square in the tetromino relative to the game board grid.
    int rXpos; //stores the x position of the right-most square in the tetromino relative to the game board grid.
    int tYpos; //stores the y position of the top-most square tetromino relative to the game board grid.
    int bYpos; //stores the y position of the bottom-most square in the tetromino relative to the game board grid.
    int id; //stores the value (1-7) of the tetromino shape
    int orientation = 0; //stores the orientation of the piece.
    char color; //color value represented by single character: 't' = teal, 'b' = blue, 'o' = orange, 'y' = yellow, 'g' = green, 'p' = purple, 'r' = red
    bool falling; //determines if the tetromino is still in play, or that it is still falling down the game board.
    void changeX(int x);
    void changeY(int y);
    void changePos(int newx, int newy);
};

#endif