#pragma once
#include "../Engine/DataStructures/Rect.hpp"
#include "../Engine/GConsole.hpp"
#include "Tetromino.hpp"
#include <algorithm>
#include <random>
#include <vector>

class Tetromino;

class Board : public Rect
{
private:
	bool hasLost;
	std::vector<char> nextTetromino;
	int randomizeCounter;
public:
	Board(int x,int y);
	void DrawBoard(GConsole& screen, const Tetromino& tetromino);
	void PlaceBlock(Tetromino& tetromino);
	void MoveNextList();
};
