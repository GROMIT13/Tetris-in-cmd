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
	char holdTetromino;
	bool canHoldTetromino;
	int randomizeCounter;
public:
	Board(int x,int y);
	void DrawBoard(GConsole& screen, const Tetromino& tetromino);
	void PlaceBlock(Tetromino& tetromino);
	char MoveNextList();
	char GetHoldTetromino();
	void SetHoldTetromino(char blockType);
	bool GetCanHoldTetromino();
	void SetCanHoldTetromino(bool canHold);
	bool ClearLine(int row);
	int ClearLines(int row, int amount);
};
