#pragma once

class Vec2
{
public:
	int x, y;

	Vec2(int x, int y);
	Vec2(const Vec2& other);
	~Vec2();
	Vec2 Add(const Vec2& other) const;
	Vec2 operator+(const Vec2& other) const;
	Vec2 Subtract(const Vec2& other) const;
	Vec2 operator-(const Vec2& other) const;
	bool operator==(const Vec2& other) const;
	bool operator!=(const Vec2& other) const;
};
