#include <iostream>
#include "Engine/DataStructures/vec.hpp"
#include "Engine/DataStructures/Rect.hpp"
#include "Log.hpp"
#include "Engine/GConsole.hpp"
#include "Engine/Input.hpp"

#define LOG(x) std::cout << x << std::endl;

int main()
{
	GConsole screen("Tetris", 60, 40, 16, 16);
	Input::SetKeys({ VK_SPACE,VK_UP,VK_DOWN,VK_LEFT,VK_RIGHT,VK_ESCAPE });
	Rect rect(0, 0, 4, 6);
	Vec2 position(0, 0);
	rect.Fill('P',FG_COLOR_LIGHT_YELLOW);

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
		rect.SetPosition(position);

		screen.DrawRect(rect);
		//screen.DrawRect(rect.GetPosition().x, rect.GetPosition().y, rect.GetBuffer(), rect.GetDimension().x, rect.GetDimension().y);
		screen.UpdateScreen();
		screen.ClearBuffer();
		Input::CheckInput();
	}
	return 0;
}
