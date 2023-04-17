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
	Input::SetKeys({ VK_SPACE,VK_UP,VK_DOWN,VK_LEFT,VK_RIGHT,VK_ESCAPE,VK_RETURN,'1','2','3','4','5','6','7','Z','X','A','C','P','R'});
	Vec2 position(5, 5);
	Clock clock(100);
	Board board(10,10);
	Tetromino tetromino(5, 5, 800, board);
	int count = 0;

	while (!Input::GetKey(VK_ESCAPE).present)
	{
		tetromino.ChangeBlock(debugChangeBlock());
		if (Input::GetState('Z') == State::Enter)
			tetromino.Rotate(3);
		if (Input::GetState('X') == State::Enter)
			tetromino.Rotate(1);
		if (Input::GetState('A') == State::Enter)
			tetromino.Rotate(2);
		if (Input::GetState('P') == State::Enter)
			board.PlaceBlock(tetromino);

		if (Input::GetState(VK_UP) == State::Enter)
			tetromino.Move(0, -1);
		
		if (tetromino.DoesFit(tetromino,tetromino.GetPosition().x, tetromino.GetPosition().y + 1))
			screen.Draw(0, 0, CHARACTER_FULL, FG_COLOR_GREEN);
		else
			screen.Draw(0, 0, CHARACTER_FULL, FG_COLOR_RED);

		// LOGIC ----------------------------------------------------------------------------------
		tetromino.Update();
		board.Update(tetromino);
		
		// DRAWING --------------------------------------------------------------------------------
		board.DrawBoard(screen, tetromino);
		tetromino.DrawTetromino(screen);

		screen.SetTitle("FPS: " + std::to_string(clock.GetFPS(1000)));
		screen.UpdateScreen();
		screen.ClearBuffer();
		// INPUT ----------------------------------------------------------------------------------
		Input::CheckInput();
	}

	return 0;
}

Tetromino::Type debugChangeBlock()
{
	if(Input::GetState('1') == State::Enter) return Tetromino::Type::I_BLOCK;
	if(Input::GetState('2') == State::Enter) return Tetromino::Type::O_BLOCK;
	if(Input::GetState('3') == State::Enter) return Tetromino::Type::J_BLOCK;
	if(Input::GetState('4') == State::Enter) return Tetromino::Type::L_BLOCK;
	if(Input::GetState('5') == State::Enter) return Tetromino::Type::Z_BLOCK;
	if(Input::GetState('6') == State::Enter) return Tetromino::Type::S_BLOCK;
	if(Input::GetState('7') == State::Enter) return Tetromino::Type::T_BLOCK;
	return Tetromino::Type::NULL_BLOCK;
}
