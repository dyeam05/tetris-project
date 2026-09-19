#include "tetromino.h"
#include "grid.h"
#include <string>
#include <vector>
#include <cstring>


int main() {
    Tetromino* testT = new Tetromino(7);
    testT->printTetromino();
    
    for(int i = 0; i < 4; i++) {
        testT->new_rotate_test();
        //testT->rotate();
        std::cout << std::endl;
        testT->printTetromino();
    }
}