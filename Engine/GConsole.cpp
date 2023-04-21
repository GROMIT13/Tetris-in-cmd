#include "GConsole.hpp"

//TO DO: fix - Draw function does not work;

GConsole::GConsole(const std::string& title, short screenWidth, short screenHeight, short fontWidth, short fontHeight)
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
		log.Error("failed to set Console Window Info (console size) to 1 width ,1 height");
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
	while (!SetConsoleWindowInfo(hConsole, TRUE, &consoleDimensions)){
		log.Error("failed to set Console Window Info (console size)");
		log.Warn("Downscaling font width and height by 1");
		if (consoleFont->dwFontSize.X > 2 && consoleFont->dwFontSize.Y > 2){
			consoleFont->dwFontSize.X--;
			consoleFont->dwFontSize.Y--;
		}
		else {
			log.Error("Failed to downscale font");
			break;
		}

		if (!SetCurrentConsoleFontEx(hConsole, TRUE, consoleFont)) {
			log.Error("failed to set font size");
		}
	}

	ShowConsoleCursor(false);
	SetTitle(title);
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

void GConsole::ShowConsoleCursor(bool isVisible)
{
	CONSOLE_CURSOR_INFO consoleCursorInfo;
	GetConsoleCursorInfo(hConsole, &consoleCursorInfo);
	consoleCursorInfo.bVisible = isVisible;
	SetConsoleCursorInfo(hConsole, &consoleCursorInfo);
}

void GConsole::SetTitle(const std::string& title)
{
	SetConsoleTitleA(title.c_str());
}
