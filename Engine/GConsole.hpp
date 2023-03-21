#pragma once

#include <Windows.h>
#include "DataStructures/Rect.hpp"

class GConsole
{
private:
	Rect* consoleRect;
	CONSOLE_FONT_INFOEX* consoleFont;
	HANDLE hConsole;
	SMALL_RECT consoleDimensions;
	COORD consoleBufferSzie;

public:
	GConsole(short screenWidth, short screenHeight, short fontWidth, short fontHeight);
	~GConsole();
	void UpdateScreen();
	void ClearScreen();
	void Draw(int x, int y);
	void Draw(int x, int y, unsigned short character);
	void Draw(int x, int y, unsigned short character, unsigned short color);
};
