#pragma once
#include "../Engine/DataStructures/Rect.hpp"
#include "../Engine/GConsole.hpp"
#include "Tetromino.hpp"
#include <algorithm>
#include <vector>
#include <time.h>

class Tetromino;

class Board : public Rect
{
private:
	std::vector<char> nextTetromino;
	int randomizeCounter;
public:
	Board(int x,int y);
	void DrawBoard(GConsole& screen, const Tetromino& tetromino);
	void PlaceBlock(Tetromino& tetromino);
	void MoveNextList();
};