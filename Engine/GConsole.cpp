#include "GConsole.hpp"
#include "DataStructures/Rect.hpp"
#include "DataStructures/vec.hpp"
#include "..\Log.hpp"

//TO DO: fix - Draw function does not work;

GConsole::GConsole(short screenWidth, short screenHeight, short fontWidth, short fontHeight)
	:Rect(0, 0, screenWidth, screenHeight)
{
	Log log("ConsoleLog.txt");
	log.ClearFile();

	consoleFont = new CONSOLE_FONT_INFOEX;
	consoleFont->cbSize = sizeof(*consoleFont);
	consoleFont->nFont = 0;
	consoleFont->dwFontSize.X = fontWidth;
	consoleFont->dwFontSize.Y = fontHeight;
	consoleFont->FontFamily = FW_DONTCARE;
	consoleFont->FontWeight = FW_NORMAL;
	wcscpy_s(consoleFont->FaceName, L"Consolas");

	//Get console Handle
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	consoleDimensions = { 0, 0, 1, 1 };
	if (!SetConsoleWindowInfo(hConsole, TRUE, &consoleDimensions)){
		log.Error("failed to set Console Window Info 1");
	}

	consoleBufferSzie = { screenWidth,screenHeight };
	if (!SetConsoleScreenBufferSize(hConsole, consoleBufferSzie)){
		log.Error("failed to set Console Screen Buffer Size");
	}

	if (!SetConsoleActiveScreenBuffer(hConsole)){
		log.Error("failed to set Console Active Screen Buffer");
	}

	// Change font size
	if (!SetCurrentConsoleFontEx(hConsole, TRUE, consoleFont)){
		log.Error("failed to set font size");
	}

	consoleDimensions = { 0, 0, short(screenWidth - 1), short(screenHeight - 1) };
	if (!SetConsoleWindowInfo(hConsole, TRUE, &consoleDimensions)){
		log.Error("failed to set Console Window Info 2 (console size)");
	}
}

GConsole::~GConsole()
{
	delete consoleFont;
}

void GConsole::UpdateScreen()
{
	WriteConsoleOutput(hConsole,
					   GetBuffer(),
					   { short(GetDimension().x),short(GetDimension().y) },
					   { 0,0 },
						&consoleDimensions);
}
