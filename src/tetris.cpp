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
static const int nHeight = 150;
static const int lWeight = 10;
static const int sSize = bWidth / 10;
static const int bStartX = wWidth/2 - bWidth / 2;
static const int bStartY = 50;
static const int fontSize = 25;

//game variables
static int score = 0; //global score variable. stores the current game score
static int lvl = 1; //global lvl variable. stores the current game lvl. lvl increases 1 time for ever 10 lines cleared. 
static int lCleared = 0; //global variable storing total lines cleared. lvl increases 1 time for ever 10 lines cleared.
static int fallingSpeed; //global variable storing the speed in which the tetrominos fall. speed is increased every lvl up.

//------------------------------------------------------------------------------------//
//Create Game objects and structures
Rectangle gameBoard = {bStartX-10, bStartY-10, bWidth+20, bHeight+20};
Rectangle nextWindow = {bStartX - nWidth - 50, 300, nWidth, nHeight};
Rectangle holdWindow = {bStartX - nWidth - 50, 350+nHeight, nWidth, nHeight};
Grid gameGrid;
Tetromino* activePiece = new Tetromino;
Tetromino* ghostPiece = new Tetromino;
Tetromino* nextPiece = new Tetromino;
Tetromino* holdPiece = new Tetromino;
Tetromino* bufferPiece = new Tetromino;
int randValue = GetRandomValue(1, 7);
int frameCtr = 0;
int inputBuffer = 0;
int lockDelay = 0;
bool gameOver = false;
bool pause = false;
bool lockCheck = false;
bool newPiece = true;
bool canHold = true;
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
		case 'G':
			return GRAY;
	}
	return BLACK;
}

void restartGame() {
	gameOver = false;
	gameGrid.clearGrid();
	score = 0;
	lvl = 1;
	lCleared = 0;
	activePiece->clearTetromino();
	nextPiece->clearTetromino();
	holdPiece->clearTetromino();
	newPiece = true;
}

void lockPiece() {
	activePiece->falling = false;
	int numLines = gameGrid.multiClear(activePiece);
	lCleared += numLines;
	if((((lCleared - (lCleared % 10)) / 10)) > lvl-1) lvl++;
	int lineScore = 0;
	//replace this with math to calculate score instead of hardcoded numbers
	if(numLines != 0) score += (numLines*100 + (numLines-1)*100) * lvl;
	lockDelay = 0;
	lockCheck = false;
	newPiece = true;
	activePiece->clearTetromino();
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
		if(lockCheck) lockDelay++;

		// drawing
		BeginDrawing();

		// Setup the back buffer for drawing (clear color and depth buffers)
		ClearBackground(LIGHTGRAY);

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

		std::string pieceStatus = "lX: " + std::to_string(activePiece->lXpos) + " rX: " 
				+ std::to_string(activePiece->rXpos) + " tY:  " + std::to_string(activePiece->tYpos) + " bY: " +
				std::to_string(activePiece->bYpos);
		char psToC[1024];
		strcpy(psToC, pieceStatus.c_str());

		DrawText(psToC, 50, 50, 20, GRAY);
		

		//draw scoreboard and next pieces
		DrawText(lcStoC, bStartX - nWidth - 50, 100, fontSize, GRAY);
		DrawText(scoreSToC, bStartX - nWidth - 50,150,fontSize, GRAY);
		DrawText(lToC, bStartX - nWidth - 50,200,fontSize, GRAY);
		DrawText("Next:", bStartX - nWidth - 50, 250, fontSize, GRAY);
		DrawRectangleLinesEx(nextWindow, 10, GRAY);
		DrawRectangleLinesEx(holdWindow, 10, GRAY);


		//if game over condition is false, continue to add pieces
		if(!gameOver) {
			//pauses game if condition is true
			if(!pause) {
				//add new piece to matrix when previous piece has finished falling
				if(newPiece) {
					randValue = GetRandomValue(1, 7);
					if(nextPiece->color == 'G') {
						activePiece->id = randValue;
						activePiece->buildTetromino();
						activePiece->falling = true;
						randValue = GetRandomValue(1, 7);
						nextPiece->id = randValue;
						nextPiece->buildTetromino();

					}
					else {
						activePiece->copyPiece(nextPiece);
						nextPiece->clearTetromino();
						randValue = GetRandomValue(1, 7);
						nextPiece->id = randValue;
						nextPiece->buildTetromino();
						canHold = true;
					}


					if (gameGrid.grid[0][4] != '0' || gameGrid.grid[0][5] != '0') {
						gameOver = true;
					}

					gameGrid.addTetromino(activePiece);
					if(!gameGrid.bottomColCheck(activePiece)) {
						//gameGrid.addGhost(activePiece, ghostPiece);
					}
					newPiece = false;
				}
				//controls the movement of the active piece. Keyboard input is read to move pieces.
				else {
					if(IsKeyDown(KEY_RIGHT)) {
						if(((inputBuffer/6)%2) == 1) {
							gameGrid.movePiece(activePiece, 'r');
							//gameGrid.removeTetromino(ghostPiece);
							//gameGrid.addGhost(activePiece, ghostPiece);
							inputBuffer = 0;
						}
					}
					if(IsKeyDown(KEY_LEFT)) {
						if(((inputBuffer/6)%2) == 1) {
							gameGrid.movePiece(activePiece, 'l');
							//gameGrid.removeTetromino(ghostPiece);
							//gameGrid.addGhost(activePiece, ghostPiece);
							inputBuffer = 0;
						}
					}
					//moves active piece down and increase score each grid spot
					if(IsKeyDown(KEY_DOWN)) {
						if(((inputBuffer/6)%2) == 1) {
							gameGrid.movePiece(activePiece, 'd');
							if(!gameGrid.finishedFalling(activePiece)) { 
								score++;
							}
							else {
								if(!lockCheck) lockCheck = true;
								if((lockDelay/60) % 2 == 1) lockPiece();
							}
							inputBuffer = 0;
						}
					}
					if(IsKeyPressed(KEY_UP)) {
						gameGrid.rotateTetromino(activePiece);
						//gameGrid.ghostRotate(activePiece, ghostPiece);
					}
					if(IsKeyPressed(KEY_SPACE)) {
						//gameGrid.removeTetromino(ghostPiece);
						score += gameGrid.hardDrop(activePiece);
						lockPiece();
					}
					if(IsKeyPressed(KEY_C)) {
						if(holdPiece->color == 'G') {
							holdPiece->copyPiece(activePiece);
							gameGrid.removeTetromino(activePiece);
							activePiece->clearTetromino();
							activePiece->copyPiece(nextPiece);
							nextPiece->clearTetromino();
							randValue = GetRandomValue(1, 7);
							nextPiece->id = randValue;
							nextPiece->buildTetromino();
							gameGrid.addTetromino(activePiece);
							canHold = false;
						}
						else {
							if(canHold) {
								gameGrid.removeTetromino(activePiece);
								bufferPiece->copyPiece(activePiece);
								activePiece->clearTetromino();
								activePiece->copyPiece(holdPiece);
								holdPiece->clearTetromino();
								holdPiece->copyPiece(bufferPiece);
								bufferPiece->clearTetromino();
								gameGrid.addTetromino(activePiece);
								canHold = false;
							}
						}
					}
					
					//Active piece automatically moves down when a certain amount of time has passed
					if ((frameCtr / (60 - (59*(lvl-1)/24)) ) % 2 == 1) {
						gameGrid.movePiece(activePiece, 'd');
						if(gameGrid.finishedFalling(activePiece)) {
							if(!lockCheck) lockCheck = true;
							if((lockDelay/60) % 2 == 1) lockPiece();
						}
						frameCtr = 0;
					}
				}
			}
			if(IsKeyPressed(KEY_P)) {
				pause = !pause;
			}
			// add pieces to board from grid object
			for(int i = 0; i < 20; i++) {
				for(int j = 0; j < 10; j++) {
					if(gameGrid.grid[i][j] != '0') {
						DrawRectangle(bStartX+sSize*j, bStartY+sSize*i, sSize, sSize, charToColor(gameGrid.grid[i][j]));
					}
				}
			}

			// draw next piece
			//(bStartX - nWidth - 50)
			//300
			for(int i = 0; i < 4; i++) {
				for(int j = 0; j < 4; j++) {
					if(nextPiece->squares[i][j] != '0') {
						DrawRectangle(	(bStartX - nWidth - 50)+sSize*j+(nWidth/4), 
										300+sSize*i, 
										sSize, 
										sSize, 
										charToColor(nextPiece->squares[i][j]));
					}
				}
			}

			// draw hold piece
			for(int i = 0; i < 4; i++) {
				for(int j = 0; j < 4; j++) {
					if(holdPiece->squares[i][j] != '0') {
						DrawRectangle(	(bStartX - nWidth - 50)+sSize*j+(nWidth/4), 
										500+sSize*i, 
										sSize, 
										sSize, 
										charToColor(holdPiece->squares[i][j]));
					}
				}
			}

			// draw horizontal lines
			for(int i = 1; i <= 20; i++) {
				DrawLine(bStartX, 50+sSize*i, bStartX + bWidth, 50+sSize*i, GRAY);
			}

			// draw vertical lines
			for(int i = 1; i <= 10; i++) {
				DrawLine(bStartX + sSize*i, 50, bStartX + sSize*i, 50+bHeight, GRAY);
			}
		}
		//if game over condition is true, stop the gameplay and display game over message.
		//Game can be restarted from here by pressing R key
		else {
			DrawText("Game Over", bStartX,100,50, GRAY);
			if(IsKeyPressed(KEY_R)) restartGame();
		}


		// end the frame and get ready for the next one  (display frame, poll input, etc...)
		EndDrawing();
	}

	// cleanup

	// destroy the window and cleanup the OpenGL context
	CloseWindow();
	return 0;
}
