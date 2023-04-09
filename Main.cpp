#include <iostream>
#include "Engine/DataStructures/vec.hpp"
#include "Engine/DataStructures/Rect.hpp"
#include "Log.hpp"
#include "Engine/GConsole.hpp"
#include "Engine/Input.hpp"
#include "Engine/Time.hpp"
#include "Game/Tetromino.hpp"
#include "Game/Board.hpp"

Tetromino::Type debugChangeBlock();

int main()
{
	GConsole screen("Tetris", 60, 40, 16, 16);
	Input::SetKeys({ VK_SPACE,VK_UP,VK_DOWN,VK_LEFT,VK_RIGHT,VK_ESCAPE,VK_RETURN,'Q','W','E','R','T','Y','U','Z','X','A','P'});
	Vec2 position(5, 5);
	Clock clock(100);
	Tetromino tetromino(5, 5, Tetromino::Type::I_BLOCK);
	Board board(10,10);

	while (!Input::GetKey(VK_ESCAPE).present)
	{
		tetromino.ChangeBlock(debugChangeBlock());
		if (Input::GetState('Z') == State::Enter)
			tetromino.Rotate(1);
		if (Input::GetState('A') == State::Enter)
			tetromino.Rotate(2);
		if (Input::GetState('X') == State::Enter)
			tetromino.Rotate(3);
		if (Input::GetState(VK_RETURN) == State::Enter)
			board.MoveNextList();
		if (Input::GetState('P') == State::Enter)
			board.PlaceBlock(tetromino);

		if (Input::GetState(VK_UP) == State::Enter)
			tetromino.Move( 0, -1);
		if (Input::GetState(VK_DOWN) == State::Enter)
			tetromino.Move( 0,  1);
		if (Input::GetState(VK_LEFT) == State::Enter)
			tetromino.Move(-1, 0);
		if (Input::GetState(VK_RIGHT) == State::Enter)
			tetromino.Move( 1, 0);
		
		board.DrawBoard(screen, tetromino);
		screen.DrawRectTransparent(tetromino,FG_COLOR_BLACK);
		screen.SetTitle("FPS: " + std::to_string(clock.GetFPS(1000)));
		screen.UpdateScreen();
		screen.ClearBuffer();
		//Clock::Wait(10);
		Input::CheckInput();
	}
	return 0;
}

Tetromino::Type debugChangeBlock()
{
	if(Input::GetState('Q') == State::Enter) return Tetromino::Type::I_BLOCK;
	if(Input::GetState('W') == State::Enter) return Tetromino::Type::O_BLOCK;
	if(Input::GetState('E') == State::Enter) return Tetromino::Type::J_BLOCK;
	if(Input::GetState('R') == State::Enter) return Tetromino::Type::L_BLOCK;
	if(Input::GetState('T') == State::Enter) return Tetromino::Type::Z_BLOCK;
	if(Input::GetState('Y') == State::Enter) return Tetromino::Type::S_BLOCK;
	if(Input::GetState('U') == State::Enter) return Tetromino::Type::T_BLOCK;
	return Tetromino::Type::NULL_BLOCK;
}