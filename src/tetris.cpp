#include <iostream>

using namespace std;

int score = 0;
int level = 0;
int linesCleared;
int fallingSpeed;

/* 
Building block for tetronimo objects. Each square object stores color information, as well as pointers to adjacent square objects stored in tetronimo and grid objecs. 
*/
class Square {
    public:
    Square() { //default constructor. sets color value to blank char and directional pointers to nullptr.
        this->color = ' ';
        top = nullptr;
        left = nullptr;
        bottom = nullptr;
        right = nullptr;
    }
    Square(char color){ //parameterized constructor (color). sets color char to the given char and directional pointers to nullptr.
        this->color = color;
        top = nullptr;
        left = nullptr;
        bottom = nullptr;
        right = nullptr;
    }
    Square* top; //pointer to above square
    Square* left; //pointer to left square
    Square* bottom; //pointer to below square
    Square* right; //pointer to right square
    char color; //color value represented by single character: 't' = teal, 'b' = blue, 'o' = orange, 'y' = yellow, 'g' = green, 'p' = purple, 'r' = red
};

class Tetronimo {
    public:
    Tetronimo() {
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

    int squares[4][4];
    int xpos;
    int ypos;
    int id;
    char color;
    bool falling;
    void rotate();
    void changeX(int x);
    void changeY(int y);
    void changePos(int newx, int newy);
};

class grid { 
    public:
    int* grid [10][20];
    void lineClear();
    void shiftDown();
    void doubleClear();
    void tripleClear();
    void tetrisClear();
};

int main() {
    Tetronimo* lineTest = new Tetronimo(1, 'r');
    Tetronimo* reverseLTest = new Tetronimo(2, 'r');
    Tetronimo* lTest = new Tetronimo(3, 'r');
    Tetronimo* squareTest = new Tetronimo(4, 'r');
    Tetronimo* zTest = new Tetronimo(5, 'r');
    Tetronimo* reverseZTest = new Tetronimo(6, 'r');
    Tetronimo* tTest = new Tetronimo(7, 'r');

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

    return 0;
}