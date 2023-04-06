#include "Board.hpp"

Board::Board(int x, int y)
	:Rect(x,y,10,20)
{

}

void Board::DrawBoard(GConsole& screen)
{
	screen.DrawRect(GetPosition().x + 1,GetPosition().y - 1,GetBuffer(),GetDimension().x,GetDimension().y);

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
}

