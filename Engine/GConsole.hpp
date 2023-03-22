#pragma once

#include <Windows.h>
#include "DataStructures/Rect.hpp"

class GConsole : public Rect
{
private:
	CONSOLE_FONT_INFOEX* consoleFont;
	HANDLE hConsole;
	SMALL_RECT consoleDimensions;
	COORD consoleBufferSzie;

public:
	GConsole(short screenWidth, short screenHeight, short fontWidth, short fontHeight);
	~GConsole();
	void UpdateScreen();
};
