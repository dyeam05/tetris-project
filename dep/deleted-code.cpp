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