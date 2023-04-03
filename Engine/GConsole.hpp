#pragma once

#include <Windows.h>
#include <string>
#include "DataStructures/Rect.hpp"
#include "DataStructures/vec.hpp"
#include "..\Log.hpp"

class GConsole : public Rect
{
private:
	CONSOLE_FONT_INFOEX* consoleFont;
	HANDLE hConsole;
	SMALL_RECT consoleDimensions;
	COORD consoleBufferSzie;

public:
	GConsole(const std::string& title,short screenWidth, short screenHeight, short fontWidth, short fontHeight);
	~GConsole();
	void UpdateScreen();
	void ShowConsoleCursor(bool isVisible);
	void SetTitle(const std::string& title);
	
};
