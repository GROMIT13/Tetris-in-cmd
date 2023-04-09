#include "Board.hpp"

Board::Board(int x, int y)
	:Rect(x,y,10,20),randomizeCounter(0)
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
	screen.DrawRect(GetPosition().x + 1,GetPosition().y,GetBuffer(),GetDimension().x,GetDimension().y);

	for (int i = 0; i < GetDimension().y; i++)
	{
		screen.Draw(GetPosition().x, GetPosition().y + i, 9553);
		screen.Draw(GetPosition().x + GetDimension().x + 1, GetPosition().y + i, 9553);
	}

	for (int i = 0; i < GetDimension().x; i++)
	{
		screen.Draw(GetPosition().x + i + 1, GetPosition().y + GetDimension().y, 9552);
	}

	screen.Draw(GetPosition().x, GetPosition().y + GetDimension().y, 9562);
	screen.Draw(GetPosition().x + GetDimension().x + 1, GetPosition().y + GetDimension().y, 9565);
	
	//Draw "NEXT" and "CHANGE" windows
	for (int i = 0; i < 6; i++)
	{
		screen.Draw(GetPosition().x - 6 + i, GetPosition().y, 9552);
		screen.Draw(GetPosition().x - 6 + i, GetPosition().y + 5, 9552);
		screen.Draw(GetPosition().x + GetDimension().x + 2 + i, GetPosition().y, 9552);
		screen.Draw(GetPosition().x + GetDimension().x + 2 + i, GetPosition().y + 17, 9552);
	}

	for (int i = 0; i < 4; i++)
		screen.Draw(GetPosition().x - 7, GetPosition().y + 1 + i, 9553);
	for (int i = 0; i < 16; i++)
		screen.Draw(GetPosition().x + GetDimension().x + 8, GetPosition().y + 1 + i, 9553);

	screen.Draw(GetPosition().x - 7, GetPosition().y + 5, 9562);
	screen.Draw(GetPosition().x - 7, GetPosition().y, 9556);
	screen.Draw(GetPosition().x + GetDimension().x + 8, GetPosition().y, 9559);
	screen.Draw(GetPosition().x + GetDimension().x + 8, GetPosition().y + 17, 9565);
	screen.Draw(GetPosition().x, GetPosition().y, 9571);
	screen.Draw(GetPosition().x, GetPosition().y + 5, 9571);
	screen.Draw(GetPosition().x + GetDimension().x + 1,GetPosition().y, 9568);
	screen.Draw(GetPosition().x + GetDimension().x + 1, GetPosition().y + 17, 9568);

	screen.DrawString(GetPosition().x + GetDimension().x + 3, GetPosition().y, "NEXT");
	screen.DrawString(GetPosition().x - 6, GetPosition().y, "CHANGE");

	//Draw Next blocks
	for (size_t i = 0; i < 5; i++)
	{
		int size = (Tetromino::Type)nextTetromino[i] == Tetromino::Type::I_BLOCK ? 4 : 3;
		screen.DrawRectTransparent(GetPosition().x + GetDimension().x + 3, GetPosition().y + 2 + i * 3, tetromino.GetSprite((Tetromino::Type)nextTetromino[i]), size, size, FG_COLOR_BLACK);
	}
}

void Board::PlaceBlock(Tetromino& tetromino)
{
	DrawRectTransparent(tetromino.GetPosition().x - GetPosition().x - 1, tetromino.GetPosition().y - GetPosition().y, tetromino.GetBuffer(), tetromino.GetDimension().x, tetromino.GetDimension().y, FG_COLOR_BLACK);
	tetromino.Reset(*this);
}

void Board::MoveNextList()
{
	//std::rotate(nextTetromino.begin(), nextTetromino.begin() + 1, nextTetromino.end());
	nextTetromino.erase(nextTetromino.begin());
	randomizeCounter = (randomizeCounter + 1) % 7;
	if (randomizeCounter == 0)
		for (unsigned int i = 0; i < 7; i++)
			nextTetromino.push_back(i % 7 + 1);

	std::shuffle(nextTetromino.begin() + 7, nextTetromino.end(), std::random_device());
}
