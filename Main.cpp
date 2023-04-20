#include <iostream>
#include "Engine/DataStructures/vec.hpp"
#include "Engine/DataStructures/Rect.hpp"
#include "Log.hpp"
#include "Engine/GConsole.hpp"
#include "Engine/Input.hpp"
#include "Engine/Time.hpp"
#include "Game/Tetromino.hpp"
#include "Game/Board.hpp"
#include "FileLoader.hpp"


int main()
{
	ScreenProperties sp = { "Tetris",49,35,16,16 }; //Default properties
	LoadScreenProperties("Screen.ini", sp);
	GConsole screen(sp.title, sp.width, sp.height, sp.textWidth, sp.textHeight);
	Input::SetKeys({ VK_SPACE,VK_UP,VK_DOWN,VK_LEFT,VK_RIGHT,VK_ESCAPE,'Z','X','A','C','R'});
	Clock clock(1000);
	Board board(14,3);
	Tetromino tetromino(5, 5, board);
	int count = 0;

	while (!Input::GetKey(VK_ESCAPE).present)
	{
		// LOGIC ----------------------------------------------------------------------------------
		tetromino.Update();
		board.Update(tetromino);
		
		// DRAWING --------------------------------------------------------------------------------
		board.DrawBoard(screen, tetromino);
		tetromino.DrawTetromino(screen);

		screen.SetTitle("TETRIS, FPS: " + std::to_string(clock.GetFPS(1000)));
		screen.UpdateScreen();
		screen.ClearBuffer();
		// INPUT ----------------------------------------------------------------------------------
		Input::CheckInput();
	}

	return 0;
}




