#include "GConsole.hpp"
#include "DataStructures/Rect.hpp"
#include "DataStructures/vec.hpp"
#include "..\Log.hpp"

//TO DO: fix - console fails to change font size;

GConsole::GConsole(short screenWidth, short screenHeight, short fontWidth, short fontHeight)
{
	Log log("ConsoleLog.txt");

	consoleRect = new Rect(0, 0, screenWidth, screenHeight);

	consoleFont = new CONSOLE_FONT_INFOEX;
	consoleFont->cbSize = sizeof(consoleFont);
	consoleFont->nFont = 0;
	consoleFont->dwFontSize.X = fontWidth;
	consoleFont->dwFontSize.Y = fontHeight;
	consoleFont->FontFamily = FW_DONTCARE;
	consoleFont->FontWeight = FW_NORMAL;

	//Get console Handle
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	consoleDimensions = { 0, 0, 1, 1 };
	if (!SetConsoleWindowInfo(hConsole, TRUE, &consoleDimensions)){
		log.Error("ERROR: failed to set Console Window Info 1");
		//LOG ERROR "ERROR: failed to set Console Window Info 1";
	}

	consoleBufferSzie = { screenWidth,screenHeight };
	if (!SetConsoleScreenBufferSize(hConsole, consoleBufferSzie)){
		log.Error("ERROR: failed to set Console Screen Buffer Size");
	}

	if (!SetConsoleActiveScreenBuffer(hConsole)){
		log.Error("ERROR: failed to set Console Active Screen Buffer");
	}

	// Change font size
	if (!SetCurrentConsoleFontEx(hConsole, TRUE, consoleFont)){
		log.Error("ERROR: failed to set font size");
	}

	consoleDimensions = { 0, 0, short(screenWidth - 1), short(screenHeight - 1) };
	if (!SetConsoleWindowInfo(hConsole, TRUE, &consoleDimensions)){
		log.Error("ERROR: failed to set Console Window Info 2 (console size)");
	}
}

GConsole::~GConsole()
{
	delete consoleRect;
	delete consoleFont;
}

void GConsole::Update()
{
	WriteConsoleOutput(hConsole,
					   consoleRect->GetBuffer(),
					   { short(consoleRect->GetDimension().x),short(consoleRect->GetDimension().y) },
					   { 0,0 },
						&consoleDimensions);
}

void GConsole::Draw(int x, int y)
{
	if (x < consoleRect->GetDimension().x && x >= 0 && y < consoleRect->GetDimension().y && y >= 0)
	{
		consoleRect->GetBuffer()[y * consoleRect->GetDimension().x + x].Char.UnicodeChar = 0x2588;
		consoleRect->GetBuffer()[y * consoleRect->GetDimension().y + x].Attributes = 0xF0;
	}
}
