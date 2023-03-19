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
