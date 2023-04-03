#include <iostream>
#include "Engine/DataStructures/vec.hpp"
#include "Engine/DataStructures/Rect.hpp"
#include "Log.hpp"
#include "Engine/GConsole.hpp"
#include "Engine/Input.hpp"
#include "Engine/Time.hpp"
#include "Game/Tetromino.hpp"

int main()
{
	GConsole screen("Tetris", 60, 40, 16, 16);
	Input::SetKeys({ VK_SPACE,VK_UP,VK_DOWN,VK_LEFT,VK_RIGHT,VK_ESCAPE });
	Rect rect(5,5, 4, 7);
	rect.FillWithText("TEXT",FG_COLOR_AQUA);
	//rect.SetDimension(3, 4);
	Vec2 position(5, 5);
	Clock clock(100);
	Tetromino tetromino(5, 5, Tetromino::Type::T_BLOCK);

	while (!Input::GetKey(VK_ESCAPE).present)
	{
		if (Input::GetState(VK_UP) == State::Enter)
			position.y--;
		if (Input::GetState(VK_DOWN) == State::Enter)
			position.y++;
		if (Input::GetState(VK_LEFT) == State::Enter)
			position.x--;
		if (Input::GetState(VK_RIGHT) == State::Enter)
			position.x++;

		screen.SetTitle("FPS: " + std::to_string(clock.GetFPS(1000)));
		screen.UpdateScreen();
		screen.ClearBuffer();
		Clock::Wait(10);
		Input::CheckInput();
	}
	return 0;
}
