#include "Rect.hpp"
#include "vec.hpp"

//TO DO: Check if it really works

Rect::Rect(int x, int y, int width, int height)
{
	position = new Vec2(x,y);
	dimension = new Vec2(width, height);
	buffer = new CHAR_INFO[width * height];
	memset(buffer, 0, sizeof(CHAR_INFO) * width * height);
}

Rect::Rect(const Rect& other)
{
	position = new Vec2(other.position->x, other.position->y);
	dimension = new Vec2(other.dimension->x, other.dimension->y);
	buffer = new CHAR_INFO[other.dimension->x * other.dimension->y];
	memcpy(buffer, other.buffer, sizeof(CHAR_INFO) * other.dimension->x * other.dimension->y);
}

Rect::~Rect()
{
	delete position;
	delete dimension;
	delete[] buffer;
}

Vec2 Rect::GetPosition()
{
	return *position;
}

void Rect::SetPosition(int x, int y)
{
	position->x = x;
	position->y = y;
}

void Rect::SetPosition(Vec2 pos)
{
	*position = pos;
}

Vec2 Rect::GetDimension()
{
	return *dimension;
}

CHAR_INFO* Rect::GetBuffer()
{
	return buffer;
}

void Rect::ClearBuffer()
{
	memset(buffer, 0, sizeof(CHAR_INFO) * dimension->x * dimension->y);
}

void Rect::Draw(int x, int y)
{
	if (x < dimension->x && x >= 0 && y < dimension->y && y >= 0)
	{
		buffer[y * short(dimension->x) + x].Char.UnicodeChar = CHARACTER_FULL;
		buffer[y * short(dimension->x) + x].Attributes = FG_COLOR_WHITE;
	}
}

void Rect::Draw(int x, int y, unsigned short character)
{
	if (x < dimension->x && x >= 0 && y < dimension->y && y >= 0)
	{
		buffer[y * short(dimension->x) + x].Char.UnicodeChar = character;
		buffer[y * short(dimension->x) + x].Attributes = FG_COLOR_WHITE;
	}
}

void Rect::Draw(int x, int y, unsigned short character, unsigned short color)
{
	if (x < dimension->x && x >= 0 && y < dimension->y && y >= 0)
	{
		buffer[y * short(dimension->x) + x].Char.UnicodeChar = character;
		buffer[y * short(dimension->x) + x].Attributes = color;
	}
}

void Rect::Fill(unsigned short character, unsigned short color)
{
	for (int j = 0; j < dimension->y; j++)
	{
		for (int i = 0; i < dimension->x; i++)
		{
			Rect::UsnecureDraw(i, j, character, color);
		}
	}
}

//TO DO: Refactor
void Rect::DrawRect(int x, int y, CHAR_INFO* data, int width, int height)
{
	if (x < dimension->x && x + width >= 0 && y < dimension->y && y + height >= 0)
	{
		// Bound checking if can draw
		int Xbegin = 0, Xend = 0;
		int Ybegin = 0, Yend = 0;
		if (x < 0)
			Xbegin = x * -1;
		if (dimension->x < x + width)
			Xend = width - (dimension->x - x);
		if (y < 0)
			Ybegin = y * -1;
		if (dimension->y < y + height)
			Yend = height - (dimension->y - y); // <--wasn't that supposted to be dimension->y

		for (int i = 0 + Ybegin; i < height - Yend; i++)
		{
			for (int j = 0 + Xbegin; j < width - Xend; j++)
			{
				UsnecureDraw(j + x, i + y, data[i * width + j].Char.UnicodeChar, data[i * width + j].Attributes);
			}
		}

	}
}

//TO DO:
void Rect::DrawRect(const Rect& rect)
{
}

void Rect::UsnecureDraw(int x, int y, unsigned short character, unsigned short color)
{
	buffer[y * short(dimension->x) + x].Char.UnicodeChar = character;
	buffer[y * short(dimension->x) + x].Attributes = color;
}
