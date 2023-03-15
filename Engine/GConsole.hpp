#pragma once

#include <Windows.h>

class GConsole
{
private:
	short m_screenWidth;
	short m_screenHeight;
	short m_fontWidth;
	short m_fontHeight;
	HANDLE m_hConsole;
	SMALL_RECT m_consoleRect;
	COORD m_consoleBufferSzie;
	CHAR_INFO* m_screenBuffer;

public:
	GConsole(short screenWidth, short screenHeight, short fontWidth, short fontHeight);
	~GConsole();
};