#pragma once
#include "../Engine/DataStructures/Rect.hpp"
#include "../Engine/GConsole.hpp"

class Board : public Rect
{
private:

public:
	Board(int x,int y);
	void DrawBoard(GConsole& screen);
};