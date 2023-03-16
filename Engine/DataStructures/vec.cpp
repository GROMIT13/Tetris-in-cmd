#include "vec.hpp"

Vec2::Vec2(int x, int y)
	:x(x),y(y) {}

Vec2::Vec2(const Vec2& other)
	:x(other.x),y(other.y) {}

Vec2 Vec2::Add(const Vec2& other) const
{
	return Vec2(x + other.x, y + other.y);
}

Vec2 Vec2::operator+(const Vec2& other) const
{
	return Add(other);
}

Vec2 Vec2::Subtract(const Vec2& other) const
{
	return Vec2(x - other.x, y - other.y);
}

Vec2 Vec2::operator-(const Vec2& other) const
{
	return Subtract(other);
}

bool Vec2::operator==(const Vec2& other) const
{
	return x == other.x && y == other.y;
}

bool Vec2::operator!=(const Vec2& other) const
{
	return !(*this == other);
}