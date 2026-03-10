/*
* Tetris Project in C++ with raylib
* Author: Daniel Yeaman
*
* Description: Working on writing a tetris program from scratch to learn more about C++, external libraries, UI creation, and game design. 
* Feel free to read and use code for inspiration and leave feedback.
*
* This code was started from the raylib_quickstart guide by JeffM2401 on github
* https://github.com/raylib-extras/raylib-quickstart
*
*/


//------------------------------------------------------------------------------------------//
#include "raylib.h"
#include "resource_dir.h"	// utility header for SearchAndSetResourceDir
#include "tetromino.h"		// header that defines function of tetromino pieces
#include "grid.h"			// header that defines function of grid

#include <string>
#include <vector>


//-------------------------------------------------------------------------------------------------------------------------------//
//constants
static const int windowWidth = 1280;
static const int windowHeight = 720;
static const int boardWidth = 300;	//arbitrary values for testing, will fix later
static const int boardHeight = 600;
static const int nextWidth = 200;
static const int nextHeight = 250;
static const int lineWeight = 10;
static const int squareSize = boardWidth / 10;
static const int boardStartingX = windowWidth/2 - boardWidth / 2;
static const int boardStartingY = 50;

//game variables
static int score = 0; //global score variable. stores the current game score
static int level = 0; //global level variable. stores the current game level. level increases 1 time for ever 10 lines cleared. 
static int linesCleared; //global variable storing total lines cleared. level increases 1 time for ever 10 lines cleared.
static int fallingSpeed; //global variable storing the speed in which the tetrominos fall. speed is increased every level up.


//------------------------------------------------------------------------------------//
//Create Game objects and structures
Rectangle gameBoard = {boardStartingX-10, boardStartingY-10, boardWidth+20, boardHeight+20};
Rectangle nextWindow = {boardStartingX - nextWidth - 50, 200, nextWidth, nextHeight};
Grid gameGrid;
std::vector<Tetromino*> pieces;
int randValue = GetRandomValue(1, 7);
int framesCounter = 0;
int inputBuffer = 0;
bool gameOver = false;
//--------------------------------------------------------------------------------------------------------------------------------------------//

//----------------------------------------------------------------------------------------//
//Game Functions
Color charToColor(char c) {
		switch(c) {
		case 't':
			return SKYBLUE;
		case 'b':
			return BLUE;
		case 'o':
			return ORANGE;
		case 'y':
			return YELLOW;
		case 'g': 
			return GREEN;
		case 'p':
			return PURPLE;
		case 'r':
			return RED;
	}
}



//----------------------------------------------------------------------------------------//
int main ()
{
	// Tell the window to use vsync and work on high DPI displays
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	// Create the window and OpenGL context
	InitWindow(windowWidth, windowHeight, "Tetris");

	// Utility function from resource_dir.h to find the resources folder and set it as the current working directory so we can load from it
	SearchAndSetResourceDir("resources");
	
	// game loop
	while (!WindowShouldClose())		// run the loop untill the user presses ESCAPE or presses the Close button on the window
	{
		//update frame count
		framesCounter++;

		// drawing
		BeginDrawing();

		// Setup the back buffer for drawing (clear color and depth buffers)
		ClearBackground(WHITE);

		// draw some text using the default font
		DrawText("Tetris", windowWidth/2 - MeasureText("Tetris", 50)/2,0,50,GRAY);

		// draw game board using rectangle
		DrawRectangleLinesEx(gameBoard, lineWeight, GRAY);

		// draw scoreboard and next pieces
		DrawText("Score: ", boardStartingX - nextWidth - 50,100,40, GRAY);
		DrawText("Next:", boardStartingX - nextWidth - 50,150,40, GRAY);
		DrawRectangleLinesEx(nextWindow, 10, GRAY);

		//if game over condition is false, continue to add pieces
		if(!gameOver) {
			//add new piece to matrix when previous piece has finished falling
			if(pieces.size() == 0 || !(pieces.back()->falling)) {
				randValue = GetRandomValue(1, 7);
				if(pieces.size() > 0) {
					if (gameGrid.grid[0][4] != '0' || gameGrid.grid[0][5] != '0') {
						gameOver = true;
					}
					else {
						pieces.erase(pieces.begin());
					}
				}
				pieces.push_back(new Tetromino(randValue));
				pieces.back()->falling = true;
				gameGrid.addTetromino(pieces.back());
			}
			else {
				if(IsKeyPressed(KEY_RIGHT)) {
						gameGrid.movePiece(pieces.back(), 'r');
				}
				if(IsKeyPressed(KEY_LEFT)) {
					gameGrid.movePiece(pieces.back(), 'l');
				}
				if(IsKeyPressed(KEY_DOWN)) {
					gameGrid.movePiece(pieces.back(), 'd');
				}
				if(IsKeyPressed(KEY_UP)) {
					gameGrid.rotateTetromino(pieces.back());
				} 
 				if (((framesCounter/120)%2) == 1) {
					gameGrid.movePiece(pieces.back(), 'd');
					framesCounter = 0;
					if(gameGrid.finishedFalling(pieces.back())) {
						pieces.back()->falling = false;
						if(gameGrid.lineFilled(pieces.back()->bYpos)) {
							gameGrid.lineClear(pieces.back()->bYpos);
							gameGrid.lineShift(pieces.back()->bYpos);
						}
					}
				}
			}

			// add pieces to board
			for(int i = 0; i < 20; i++) {
				for(int j = 0; j < 10; j++) {
					if(gameGrid.grid[i][j] != '0') {
						DrawRectangle(boardStartingX+squareSize*j, boardStartingY+squareSize*i, squareSize, squareSize, charToColor(gameGrid.grid[i][j]));
					}
				}
			}
		}
		//if game over condition is true, stop the gameplay and display game over message.
		else {
			DrawText("Game Over", boardStartingX+50,100,100, GRAY);
		}

		// draw horizontal lines
		for(int i = 1; i <= 20; i++) {
			DrawLine(boardStartingX, 50+squareSize*i, boardStartingX + boardWidth, 50+squareSize*i, GRAY);
		}

		// draw vertical lines
		for(int i = 1; i <= 10; i++) {
			DrawLine(boardStartingX + squareSize*i, 50, boardStartingX + squareSize*i, 50+boardHeight, GRAY);
		}

		// end the frame and get ready for the next one  (display frame, poll input, etc...)
		EndDrawing();
	}

	// cleanup

	// destroy the window and cleanup the OpenGL context
	CloseWindow();
	return 0;
}
