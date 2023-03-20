#include <iostream>
#include "Engine/DataStructures/vec.hpp"
#include "Engine/DataStructures/Rect.hpp"
#include "Log.hpp"
#include "Engine/GConsole.hpp"

#define LOG(x) std::cout << x << std::endl;

int main()
{
	bool windowRunning = true;
	GConsole screen(40, 20, 4, 4);

	while (windowRunning)
	{
		screen.Draw(0, 0);
		screen.Update();
	}
	return 0;
}
