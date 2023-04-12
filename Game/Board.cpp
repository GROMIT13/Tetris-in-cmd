#include "Board.hpp"

Board::Board(int x, int y)
	:Rect(x,y,10,24),
	 randomizeCounter(0),
	 hasLost(false),
	 holdTetromino((char)Tetromino::Type::NULL_BLOCK),
	 canHoldTetromino(true)
{
	nextTetromino.reserve(14);
	for (unsigned int i = 0; i < nextTetromino.capacity(); i++)
		nextTetromino.push_back(i % 7 + 1);
	std::shuffle(nextTetromino.begin(), nextTetromino.begin() + 7, std::random_device());
	std::shuffle(nextTetromino.begin() + 7, nextTetromino.end(), std::random_device());
}

void Board::DrawBoard(GConsole& screen,const Tetromino& tetromino)
{
	//Draw main Board
	screen.DrawRect(GetPosition().x,GetPosition().y,GetBuffer(),GetDimension().x,GetDimension().y);

	for (int i = 4; i < GetDimension().y; i++)
	{
		screen.Draw(GetPosition().x - 1, GetPosition().y + i, 9553);
		screen.Draw(GetPosition().x + GetDimension().x, GetPosition().y + i, 9553);
	}

	for (int i = 0; i < GetDimension().x; i++)
	{
		screen.Draw(GetPosition().x + i, GetPosition().y + GetDimension().y, 9552);
	}

	screen.Draw(GetPosition().x - 1, GetPosition().y + GetDimension().y, 9562);
	screen.Draw(GetPosition().x + GetDimension().x, GetPosition().y + GetDimension().y, 9565);
	
	//Draw "NEXT" and "CHANGE" windows
	for (int i = 0; i < 6; i++)
	{
		screen.Draw(GetPosition().x - 7 + i, GetPosition().y + 4, 9552);
		screen.Draw(GetPosition().x - 7 + i, GetPosition().y + 9, 9552);
		screen.Draw(GetPosition().x + GetDimension().x + 1 + i, GetPosition().y + 4, 9552);
		screen.Draw(GetPosition().x + GetDimension().x + 1 + i, GetPosition().y + 21, 9552);
	}

	for (int i = 0; i < 4; i++)
		screen.Draw(GetPosition().x - 8, GetPosition().y + 5 + i, 9553);
	for (int i = 0; i < 16; i++)
		screen.Draw(GetPosition().x + GetDimension().x + 7, GetPosition().y + 5 + i, 9553);

	screen.Draw(GetPosition().x - 8, GetPosition().y + 9, 9562);
	screen.Draw(GetPosition().x - 8, GetPosition().y + 4, 9556);
	screen.Draw(GetPosition().x + GetDimension().x + 7, GetPosition().y + 4, 9559);
	screen.Draw(GetPosition().x + GetDimension().x + 7, GetPosition().y + 21, 9565);
	screen.Draw(GetPosition().x - 1, GetPosition().y + 4, 9571);
	screen.Draw(GetPosition().x - 1, GetPosition().y + 9, 9571);
	screen.Draw(GetPosition().x + GetDimension().x,GetPosition().y + 4, 9568);
	screen.Draw(GetPosition().x + GetDimension().x, GetPosition().y + 21, 9568);

	screen.DrawString(GetPosition().x + GetDimension().x + 2, GetPosition().y + 4, "NEXT");
	screen.DrawString(GetPosition().x - 6, GetPosition().y + 4, "HOLD");

	//Draw Next blocks
	for (size_t i = 0; i < 5; i++)
	{
		int size = (Tetromino::Type)nextTetromino[i] == Tetromino::Type::I_BLOCK ? 4 : 3;
		screen.DrawRectTransparent(GetPosition().x + GetDimension().x + 2, GetPosition().y + 6 + i * 3, tetromino.GetSprite((Tetromino::Type)nextTetromino[i]), size, size, FG_COLOR_BLACK);
	}

	//Draw Hold block
	if ((Tetromino::Type)holdTetromino != Tetromino::Type::NULL_BLOCK)
	{
		int size = (Tetromino::Type)holdTetromino == Tetromino::Type::I_BLOCK ? 4 : 3;
		screen.DrawRectTransparent(GetPosition().x + -6, GetPosition().y + 6, tetromino.GetSprite((Tetromino::Type)holdTetromino), size, size, FG_COLOR_BLACK);
	}
}

void Board::PlaceBlock(Tetromino& tetromino)
{
	DrawRectTransparent(tetromino.GetPosition().x - GetPosition().x, tetromino.GetPosition().y - GetPosition().y, tetromino.GetBuffer(), tetromino.GetDimension().x, tetromino.GetDimension().y, FG_COLOR_BLACK);
	tetromino.Reset();
}

char Board::MoveNextList()
{
	char tetromino = nextTetromino.front();
	nextTetromino.erase(nextTetromino.begin());
	randomizeCounter = (randomizeCounter + 1) % 7;
	if (randomizeCounter == 0)
		for (unsigned int i = 0; i < 7; i++)
			nextTetromino.push_back(i % 7 + 1);

	std::shuffle(nextTetromino.begin() + 7, nextTetromino.end(), std::random_device());
	return tetromino;
}

char Board::GetHoldTetromino()
{
	return holdTetromino;
}

void Board::SetHoldTetromino(char blockType)
{
	holdTetromino = blockType;
}

bool Board::GetCanHoldTetromino()
{
	return canHoldTetromino;
}

void Board::SetCanHoldTetromino(bool canHold)
{
	canHoldTetromino = canHold;
}
