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
	//Score parameters
	unsigned long long score;
	unsigned long long drawScore;
	unsigned int level;
	unsigned int linesToNextLevel;
	unsigned int linesOnThisLevel;
	unsigned int linesCleared;

	bool hasLost;
	std::vector<char> nextTetromino;
	char holdTetromino;
	bool canHoldTetromino;
	int randomizeCounter;
public:
	Board(int x,int y);
	void ResetBoard();
	void DrawBoard(GConsole& screen, const Tetromino& tetromino);
	void PlaceBlock(Tetromino& tetromino);
	bool HasLost();
	char MoveNextList();
	char GetHoldTetromino();
	void SetHoldTetromino(char blockType);
	bool GetCanHoldTetromino();
	void SetCanHoldTetromino(bool canHold);
	bool GetHasLost();
	void SetHasLost(bool hasLost);
	bool ClearLine(int row);
	int  ClearLines(int row, int amount);
	void CountScore(int linesCleared);
	void Update(Tetromino& tetromino);
};
