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
static const int wWidth = 1280;
static const int wHeight = 720;
static const int bWidth = 300;	//arbitrary values for testing, will fix later
static const int bHeight = 600;
static const int nWidth = 200;
static const int nHeight = 250;
static const int lWeight = 10;
static const int sSize = bWidth / 10;
static const int bStartX = wWidth/2 - bWidth / 2;
static const int bStartY = 50;

//game variables
static int score = 0; //global score variable. stores the current game score
static int lvl = 1; //global lvl variable. stores the current game lvl. lvl increases 1 time for ever 10 lines cleared. 
static int lCleared = 0; //global variable storing total lines cleared. lvl increases 1 time for ever 10 lines cleared.
static int fallingSpeed; //global variable storing the speed in which the tetrominos fall. speed is increased every lvl up.

//------------------------------------------------------------------------------------//
//Create Game objects and structures
Rectangle gameBoard = {bStartX-10, bStartY-10, bWidth+20, bHeight+20};
Rectangle nextWindow = {bStartX - nWidth - 50, 250, nWidth, nHeight};
Grid gameGrid;
std::vector<Tetromino*> pieces;
int randValue = GetRandomValue(1, 7);
int frameCtr = 0;
int inputBuffer = 0;
int lockDelay = 0;
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
	return BLACK;
}

void restartGame() {
	gameOver = false;
	gameGrid.clearGrid();
	pieces.clear();
	score = 0;
	lvl = 1;
	lCleared = 0;
}

void lockPiece() {
	pieces.back()->falling = false;
	int numLines = gameGrid.multiClear(pieces.back());
	lCleared += numLines;
	if((((lCleared - (lCleared % 10)) / 10)) > lvl-1) lvl++;
	int lineScore = 0;
	//replace this with math to calculate score instead of hardcoded numbers
	if(numLines != 0) score += (numLines*100 + (numLines-1)*100) * lvl;
}


//----------------------------------------------------------------------------------------//
int main ()
{
	// Tell the window to use vsync and work on high DPI displays
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	// Create the window and OpenGL context
	InitWindow(wWidth, wHeight, "Tetris");

	//Sets target FPS to 60
	SetTargetFPS(60);

	// Utility function from resource_dir.h to find the resources folder and set it as the current working directory so we can load from it
	SearchAndSetResourceDir("resources");
	
	// game loop
	while (!WindowShouldClose())		// run the loop untill the user presses ESCAPE or presses the Close button on the window
	{
		//update frame counts
		frameCtr++;
		inputBuffer++;

		// drawing
		BeginDrawing();

		// Setup the back buffer for drawing (clear color and depth buffers)
		ClearBackground(WHITE);

		// draw some text using the default font
		DrawText("Tetris", wWidth/2 - MeasureText("Tetris", 50)/2,0,50,GRAY);

		// draw game board using rectangle struct
		DrawRectangleLinesEx(gameBoard, lWeight, GRAY);

		//displays FPS in top-left corner of screen. For debugging and optimization
		DrawFPS(10, 10);
		
		//uses std::string objects to store and display line count string
		std::string lcString = "Lines: " + std::to_string(lCleared);
		char lcStoC[1024];
		//converts line count string to standard C string, then to char array
		strcpy(lcStoC, lcString.c_str());

		//same thing, but for score
		std::string scoreString = "Score: " + std::to_string(score);
		char scoreSToC[1024];
		strcpy(scoreSToC, scoreString.c_str());

		//same thing again, but for game level
		std::string lvlString = "lvl: " + std::to_string(lvl);
		char lToC[1024];
		strcpy(lToC, lvlString.c_str());
		
		//-----FOR DEBUGGING PURPOSES-----//
		//Does the same as the above, but displays the frame counter variable.
		//Also displays the logic for dropping pieces
		//When the frame counter matches the piece drop timing logic, the text is green
		std::string frames = "framectr: " + std::to_string(frameCtr);
		char fToC[1024];
		strcpy(fToC, frames.c_str());
		int fallFrame;
		if((frameCtr/(60 - (59/24)*(lvl-1))) % 2 == 1) {
			DrawText(fToC, 10, 50, 20, GREEN);
			fallFrame = frameCtr; //(frameCtr/(60 - (59/24)*(lvl-1))) % 2;
		}
		else DrawText(fToC, 10, 50, 20, GRAY);
		std::string fall = "final frame before fall: " + std::to_string(fallFrame) + " fall formula: " + std::to_string(((60 - (59*(lvl-1)/24))));
		char fallC[1024];
		strcpy(fallC, fall.c_str());
		DrawText(fallC, 10, 70, 20, GRAY);
		//---------//

		// draw scoreboard and next pieces
		DrawText(lcStoC, bStartX - nWidth - 50, 100, 40, GRAY);
		DrawText(scoreSToC, bStartX - nWidth - 50,150,40, GRAY);
		DrawText(lToC, bStartX - nWidth - 50,200,40, GRAY);
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
				if(IsKeyDown(KEY_RIGHT)) {
					if(((inputBuffer/6)%2) == 1) {
						gameGrid.movePiece(pieces.back(), 'r');
						inputBuffer = 0;
					}
				}
				if(IsKeyDown(KEY_LEFT)) {
					if(((inputBuffer/6)%2) == 1) {
						gameGrid.movePiece(pieces.back(), 'l');
						inputBuffer = 0;
					}
				}
				if(IsKeyDown(KEY_DOWN)) {
					if(((inputBuffer/6)%2) == 1) {
						gameGrid.movePiece(pieces.back(), 'd');
						if(!gameGrid.finishedFalling(pieces.back())) { 
							score++;
						}
						else {
							pieces.back()->falling = false;
						}
						inputBuffer = 0;
					}
				}
				if(IsKeyPressed(KEY_UP)) {
					gameGrid.rotateTetromino(pieces.back());
				}
				if(IsKeyPressed(KEY_SPACE)) {
					score += gameGrid.hardDrop(pieces.back());
					lockPiece();
				} 

 				if ((frameCtr / (60 - (59*(lvl-1)/24)) ) % 2 == 1) {
					gameGrid.movePiece(pieces.back(), 'd');
					if(gameGrid.finishedFalling(pieces.back())) {
						lockPiece();
					}
					frameCtr = 0;
				}
			}

			// add pieces to board
			for(int i = 0; i < 20; i++) {
				for(int j = 0; j < 10; j++) {
					if(gameGrid.grid[i][j] != '0') {
						DrawRectangle(bStartX+sSize*j, bStartY+sSize*i, sSize, sSize, charToColor(gameGrid.grid[i][j]));
					}
				}
			}
		}
		//if game over condition is true, stop the gameplay and display game over message.
		else {
			DrawText("Game Over", bStartX+50,100,100, GRAY);
			if(IsKeyPressed(KEY_R)) restartGame();
		}

		// draw horizontal lines
		for(int i = 1; i <= 20; i++) {
			DrawLine(bStartX, 50+sSize*i, bStartX + bWidth, 50+sSize*i, GRAY);
		}

		// draw vertical lines
		for(int i = 1; i <= 10; i++) {
			DrawLine(bStartX + sSize*i, 50, bStartX + sSize*i, 50+bHeight, GRAY);
		}

		// end the frame and get ready for the next one  (display frame, poll input, etc...)
		EndDrawing();
	}

	// cleanup

	// destroy the window and cleanup the OpenGL context
	CloseWindow();
	return 0;
}
