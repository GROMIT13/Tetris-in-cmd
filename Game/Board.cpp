#include "Board.hpp"

Board::Board(int x, int y)
	:Rect(x, y, 10, 24),
	 score(0),
	 drawScore(0),
	 level(1),
	 linesToNextLevel(3),
	 linesOnThisLevel(0),
	 linesCleared(0),
	 hasLost(false),
	 holdTetromino((char)Tetromino::Type::NULL_BLOCK),
	 canHoldTetromino(true),
	 randomizeCounter(0)

{
	nextTetromino.reserve(14);
	for (unsigned int i = 0; i < nextTetromino.capacity(); i++)
		nextTetromino.push_back(i % 7 + 1);
	std::shuffle(nextTetromino.begin(), nextTetromino.begin() + 7, std::random_device());
	std::shuffle(nextTetromino.begin() + 7, nextTetromino.end(), std::random_device());
}

//Reset All stats, reroll the nextList, reset Hold block
void Board::ResetBoard()
{
	score = 0;
	drawScore = 0;
	level = 1;
	linesToNextLevel = 3;
	linesOnThisLevel = 0;
	linesCleared = 0;
	hasLost = false;
	holdTetromino = (char)Tetromino::Type::NULL_BLOCK;
	canHoldTetromino = true;
	while (randomizeCounter != 0)
		MoveNextList();
	
	ClearBuffer();

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

	//Draw Game Stats
	screen.DrawString(GetPosition().x + GetDimension().x + 10, GetPosition().y + 4, "SCORE");
	screen.DrawString(GetPosition().x + GetDimension().x + 10, GetPosition().y + 5, std::to_string(drawScore));
	screen.DrawString(GetPosition().x + GetDimension().x + 10, GetPosition().y + 7, "LEVEL");
	screen.DrawString(GetPosition().x + GetDimension().x + 10, GetPosition().y + 8, std::to_string(level));
	screen.DrawString(GetPosition().x + GetDimension().x + 10, GetPosition().y + 10, "NEXT LEVEL");
	screen.DrawString(GetPosition().x + GetDimension().x + 10, GetPosition().y + 11, std::to_string(linesOnThisLevel) + "/" + std::to_string(linesToNextLevel));

	//Draw lost screen
	if (hasLost)
	{
		screen.DrawString(GetPosition().x + GetDimension().x + 10, GetPosition().y + 13, "YOU LOST!",FG_COLOR_LIGHT_RED);
		screen.DrawString(GetPosition().x + GetDimension().x + 10, GetPosition().y + 14, "PRESS R TO RESTART",FG_COLOR_LIGHT_GREEN);
	}


}

void Board::PlaceBlock(Tetromino& tetromino)
{
	DrawRectTransparent(tetromino.GetPosition().x - GetPosition().x, tetromino.GetPosition().y - GetPosition().y, tetromino.GetBuffer(), tetromino.GetDimension().x, tetromino.GetDimension().y, FG_COLOR_BLACK);
}

bool Board::HasLost()
{
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < GetDimension().x; x++)
		{
			if (GetPixel(x, y).value().Attributes != FG_COLOR_BLACK)
			{
				hasLost = true;
				return true;
			}
		}
	}
	return false;
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

bool Board::GetHasLost()
{
	return hasLost;
}

void Board::SetHasLost(bool hasLost)
{
	this->hasLost = hasLost;
}

//Returns true when line is cleared
bool Board::ClearLine(int row)
{
	if (!GetPixel(0, row).has_value())
		return false;

	for (int i = 0; i < GetDimension().x; i++)
	{
		if (GetPixel(i, row).value().Attributes == FG_COLOR_BLACK)
			return false;
	}
	memset(GetBuffer() + row * GetDimension().x, 0, sizeof(CHAR_INFO) * GetDimension().x);
	memcpy(GetBuffer() + GetDimension().x, GetBuffer(), sizeof(CHAR_INFO) * GetDimension().x * GetDimension().y - (sizeof(CHAR_INFO) * GetDimension().x * (GetDimension().y - row)));
	return true;
}

int Board::ClearLines(int row, int amount)
{
	int linesCleared = 0;
	for (int i = 0; i < amount; i++)
	{
		if (ClearLine(row + i))
			linesCleared++;
	}
	return linesCleared;
}

void Board::CountScore(int linesCleared)
{
	switch (linesCleared)
	{
	case 1: score += 100 * (unsigned long long)(level); break;
	case 2: score += 300 * (unsigned long long)(level); break;
	case 3: score += 500 * (unsigned long long)(level); break;
	case 4: score += 800 * (unsigned long long)(level); break;
	default:
		break;
	}
}

void Board::Update(Tetromino& tetromino)
{
	//Update Visual score
	if (drawScore < score)
		drawScore++;

	if (Input::GetState('R') == State::Enter)
	{
		ResetBoard();
		tetromino.Reset();
		tetromino.ChangeBlock((Tetromino::Type)MoveNextList());
	}
}

