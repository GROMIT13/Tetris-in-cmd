#include "GConsole.hpp"
#include "DataStructures/Rect.hpp"
#include "DataStructures/vec.hpp"
#include "..\Log.hpp"

//TO DO: fix - Draw function does not work;

GConsole::GConsole(short screenWidth, short screenHeight, short fontWidth, short fontHeight)
{
	Log log("ConsoleLog.txt");
	log.ClearFile();

	consoleRect = new Rect(0, 0, screenWidth - 1, screenHeight - 1);

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
	delete consoleRect;
	delete consoleFont;
}

void GConsole::UpdateScreen()
{
	WriteConsoleOutput(hConsole,
					   consoleRect->GetBuffer(),
					   { short(consoleRect->GetDimension().x),short(consoleRect->GetDimension().y) },
					   { 0,0 },
						&consoleDimensions);
}

void GConsole::ClearScreen()
{
	consoleRect->ClearBuffer();
}

void GConsole::Draw(int x, int y)
{
	consoleRect->Draw(x, y);
}

void GConsole::Draw(int x, int y, unsigned short character)
{
	consoleRect->Draw(x, y, character);
}

void GConsole::Draw(int x, int y, unsigned short character, unsigned short color)
{
	consoleRect->Draw(x, y, character, color);
}
