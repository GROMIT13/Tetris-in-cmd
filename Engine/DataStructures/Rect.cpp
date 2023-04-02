#include "Rect.hpp"
#include "vec.hpp"

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

Vec2 Rect::GetPosition() const
{
	return *position;
}

Vec2 Rect::GetDimension() const
{
	return *dimension;
}

CHAR_INFO* Rect::GetBuffer() const
{
	return buffer;
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

//TO DO : Add if checks preventing seg fault
void Rect::SetDimension(int x, int y)
{
	dimension->x = x;
	dimension->y = y;
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
			Rect::UnsecureDraw(i, j, character, color);
		}
	}
}

void Rect::FillWithText(const std::string& string, unsigned short color)
{
	for (int j = 0; j < dimension->y; j++)
	{
		for (int i = 0; i < dimension->x; i++)
		{
			Rect::UnsecureDraw(i, j, string[(i + j* dimension->x) % string.length()], color);
		}
	}
}

void Rect::DrawRect(int x, int y, CHAR_INFO* data, int width, int height)
{
		// Bound checking if can draw
		Vec2 begin(0, 0);
		Vec2 end(width, height);
		begin.x = (x < 0) ? (x * -1) : 0;
		end.x = (dimension->x < x + width) ? end.x = dimension->x - x : end.x;
		begin.y = (y < 0) ? (y * -1) : 0;
		end.y = (dimension->y < y + height) ? end.y = dimension->y - y : end.y;

		//Draw
		for (int i = begin.y; i < end.y; i++)
		{
			for (int j = begin.x; j < end.x; j++)
			{
				UnsecureDraw(j + x, i + y, data[i * width + j].Char.UnicodeChar, data[i * width + j].Attributes);
			}
		}
}

void Rect::DrawRect(const Rect& rect)
{
	// Bound checking if can draw
	Vec2 begin(0, 0);
	Vec2 end(rect.GetDimension().x, rect.GetDimension().y);
	begin.x = (rect.GetPosition().x < 0) ? (rect.GetPosition().x * -1) : 0;
	end.x = (dimension->x < rect.GetPosition().x + rect.GetDimension().x) ? end.x = dimension->x - rect.GetPosition().x : end.x;
	begin.y = (rect.GetDimension().y < 0) ? (rect.GetDimension().y * -1) : 0;
	end.y = (dimension->y < rect.GetPosition().y + rect.GetDimension().y) ? end.y = dimension->y - rect.GetPosition().y : end.y;

	//Draw
	for (int i = begin.y; i < end.y; i++)
	{
		for (int j = begin.x; j < end.x; j++)
		{
			UnsecureDraw(j + rect.GetPosition().x,
						 i + rect.GetPosition().y,
						 rect.GetBuffer()[i * rect.GetDimension().x + j].Char.UnicodeChar,
						 rect.GetBuffer()[i * rect.GetDimension().x + j].Attributes);
		}
	}
}

void Rect::DrawString(int x, int y, const std::string& string)
{
	if (y >= dimension->y || y < 0)
		return;

	int begin = (x < 0) ? (x * -1) : 0;
	int end = (dimension->x < x + (int)string.length()) ? end = dimension->x - x : string.length();

	for (int i = begin; i < end; i++)
	{
		UnsecureDraw(i + x, y, string[i], FG_COLOR_WHITE);
	}
}

void Rect::DrawString(int x, int y, const std::string& string, unsigned short color)
{
	if (y >= dimension->y || y < 0)
		return;

	int begin = (x < 0) ? (x * -1) : 0;
	int end = (dimension->x < x + (int)string.length()) ? end = dimension->x - x : string.length();

	for (int i = begin; i < end; i++)
	{
		UnsecureDraw(i + x, y, string[i], color);
	}
}

void Rect::DrawLine(int x0, int y0, int x1, int y1)
{
	if ((x0 < 0 && x1 < 0) || (y0 < 0 && y1 < 0) || (x0 >= dimension->x && x1 >= dimension->x) || (y0 >= dimension->y && y1 >= dimension->y))
		return;
	int dx = abs(x1 - x0);
	int sx = x0 < x1 ? 1 : -1;
	int dy = -abs(y1 - y0);
	int sy = y0 < y1 ? 1 : -1;
	int error = dx + dy;
    
    while (true)
	{
		Draw(x0, y0, CHARACTER_FULL, FG_COLOR_WHITE);
		if (x0 == x1 && y0 == y1) break;
		int e2 = 2 * error;
        if (e2 >= dy)
		{
			if (x0 == x1) break;
			error = error + dy;
			x0 = x0 + sx;
		}
        if (e2 <= dx)
		{
            if (y0 == y1) break;
            error = error + dx;
			y0 = y0 + sy;
        }
    }
}

void Rect::DrawLine(int x0, int y0, int x1, int y1, unsigned short character, unsigned short color)
{
	if ((x0 < 0 && x1 < 0) || (y0 < 0 && y1 < 0) || (x0 >= dimension->x && x1 >= dimension->x) || (y0 >= dimension->y && y1 >= dimension->y))
		return;
	int dx = abs(x1 - x0);
	int sx = x0 < x1 ? 1 : -1;
	int dy = -abs(y1 - y0);
	int sy = y0 < y1 ? 1 : -1;
	int error = dx + dy;
    
    while (true)
	{
		Draw(x0, y0, character, color);
		if (x0 == x1 && y0 == y1) break;
		int e2 = 2 * error;
        if (e2 >= dy)
		{
			if (x0 == x1) break;
			error = error + dy;
			x0 = x0 + sx;
		}
        if (e2 <= dx)
		{
            if (y0 == y1) break;
            error = error + dx;
			y0 = y0 + sy;
        }
    }
}

void Rect::UnsecureDraw(int x, int y, unsigned short character, unsigned short color)
{
	buffer[y * short(dimension->x) + x].Char.UnicodeChar = character;
	buffer[y * short(dimension->x) + x].Attributes = color;
}
