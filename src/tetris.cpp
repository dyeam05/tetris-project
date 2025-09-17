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


//-------------------------------------------------------------------------------------------------------------------------------//
static const int windowWidth = 1280;
static const int windowHeight = 720;
static const int boardWidth = 500;
static const int boardHeight = windowHeight - 100;
static const int nextWidth = 200;
static const int nextHeight = 250;

static int score = 0; //global score variable. stores the current game score
static int level = 0; //global level variable. stores the current game level. level increases 1 time for ever 10 lines cleared. 
static int linesCleared; //global variable storing total lines cleared. level increases 1 time for ever 10 lines cleared.
static int fallingSpeed; //global variable storing the speed in which the tetrominos fall. speed is increased every level up.


//------------------------------------------------------------------------------------//
Rectangle gameBoard = { windowWidth/2 - boardWidth / 2, 50, boardWidth, boardHeight};
Rectangle nextWindow = {windowWidth/2 - boardWidth / 2 - nextWidth - 50, 200, nextWidth, nextHeight};

//--------------------------------------------------------------------------------------------------------------------------------------------//
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
		// drawing
		BeginDrawing();

		// Setup the back buffer for drawing (clear color and depth buffers)
		ClearBackground(WHITE);

		// draw some text using the default font
		DrawText("Tetris", windowWidth/2 - MeasureText("Tetris", 50)/2,0,50,GRAY);

		// draw game board using rectangle
		DrawRectangleLinesEx(gameBoard, 10, GRAY);

		// draw scoreboard and next pieces
		DrawText("Score: ", windowWidth/2 - boardWidth / 2 - nextWidth - 50,100,40, GRAY);
		DrawText("Next:", windowWidth/2 - boardWidth / 2 - nextWidth - 50,150,40, GRAY);
		DrawRectangleLinesEx(nextWindow, 10, GRAY);

		// end the frame and get ready for the next one  (display frame, poll input, etc...)
		EndDrawing();
	}

	// cleanup

	// destroy the window and cleanup the OpenGL context
	CloseWindow();
	return 0;
}
