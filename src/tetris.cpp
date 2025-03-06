#include <iostream>

using namespace std;

int score = 0; //global score variable. stores the current game score
int level = 0; //global level variable. stores the current game level. level increases 1 time for ever 10 lines cleared. 
int linesCleared; //global variable storing total lines cleared. level increases 1 time for ever 10 lines cleared.
int fallingSpeed; //global variable storing the speed in which the tetrominos fall. speed is increased every level up.


/**
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
class Tetronimo { 
    public:
    Tetronimo() { //Default Constructor. sets all int values to 0, color value to empty char and falling to false.
        id = 0;
        color = ' ';
        xpos = 0;
        ypos = 0;
        falling = false;
    }

    Tetronimo(int id, char color) {
        this->id = id;
        this->color = color;
        xpos = 0;
        ypos = 0;
        falling = true;

        for(int i = 0; i < 4; i++){
            for(int j = 0; j < 4; j++) {
                squares[i][j] = 0;
            }
        }

        buildTetronimo();
    }

    void buildTetronimo() {
        switch (id) {
            case 1: //straight line piece
                squares[3][0] = 1;
                squares[3][1] = 1;
                squares[3][2] = 1;
                squares[3][3] = 1;
                break;
            
            case 2: //reverse l piece
                squares[2][0] = 1;
                squares[3][0] = 1;
                squares[3][1] = 1;
                squares[3][2] = 1;
                break;
            
            case 3: //l piece
                squares[2][2] = 1;
                squares[3][0] = 1;
                squares[3][1] = 1;
                squares[3][2] = 1;
                break;
            
            case 4: //square piece
                squares[2][1] = 1;
                squares[2][2] = 1;
                squares[3][1] = 1;
                squares[3][2] = 1;
                break;

            case 5: //z piece
                squares[2][0] = 1;
                squares[2][1] = 1;
                squares[3][1] = 1;
                squares[3][2] = 1;
                break;

            case 6: //reverse z piece
                squares[2][1] = 1;
                squares[2][2] = 1;
                squares[3][0] = 1;
                squares[3][1] = 1;
                break;

            case 7: //t piece
                squares[2][1] = 1;
                squares[3][0] = 1;
                squares[3][1] = 1;
                squares[3][2] = 1;
            default:
                break;
        }
    }

    int squares[4][4]; //4x4 matrix that stores the shape of the tetromino
    int xpos; //stores the x position of the tetromino relative to the game board grid
    int ypos; //stores the y position of the tetromino relative to the game board grid
    int id; //stores the value (1-7) of the tetromino shape
    char color; //color value represented by single character: 't' = teal, 'b' = blue, 'o' = orange, 'y' = yellow, 'g' = green, 'p' = purple, 'r' = red
    bool falling; //determines if the tetromino is still in play, or that it is still falling down the game board.
    void rotate();
    void changeX(int x);
    void changeY(int y);
    void changePos(int newx, int newy);
};

class Grid { 
    public:

    Grid() { //Default Constructor. Creates the grid and sets all matrix values to empty '0'.
        for(int i = 0; i < 20; i++){
            for(int j = 0; j < 10; j++) {
                grid[i][j] = 0;
            }
        }

        numSquares = 0;
    }

    int numSquares;
    int grid[10][20];
    void lineClear(int line);
    void shiftDown(int line);
    void multiClear(int lines);
};

int main() {
    Tetronimo* lineTest = new Tetronimo(1, 'r');
    Tetronimo* reverseLTest = new Tetronimo(2, 'r');
    Tetronimo* lTest = new Tetronimo(3, 'r');
    Tetronimo* squareTest = new Tetronimo(4, 'r');
    Tetronimo* zTest = new Tetronimo(5, 'r');
    Tetronimo* reverseZTest = new Tetronimo(6, 'r');
    Tetronimo* tTest = new Tetronimo(7, 'r');

    Grid* gridTest = new Grid();

    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++) {
            cout << lineTest->squares[i][j] << " ";
        }
        cout << endl;
    }

    cout << endl;

    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++) {
            cout << reverseLTest->squares[i][j] << " ";
        }
        cout << endl;
    }

    cout << endl;

    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++) {
            cout << lTest->squares[i][j] << " ";
        }
        cout << endl;
    }

    cout << endl;

    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++) {
            cout << squareTest->squares[i][j] << " ";
        }
        cout << endl;
    }

    cout << endl;

    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++) {
            cout << zTest->squares[i][j] << " ";
        }
        cout << endl;
    }

    cout << endl;

    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++) {
            cout << reverseZTest->squares[i][j] << " ";
        }
        cout << endl;
    }

    cout << endl;

    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++) {
            cout << tTest->squares[i][j] << " ";
        }
        cout << endl;
    }

    cout << endl;

    for(int i = 0; i < 20; i++){
        for(int j = 0; j < 10; j++) {
            cout << gridTest->grid[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}