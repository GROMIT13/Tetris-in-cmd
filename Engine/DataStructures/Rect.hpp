#pragma once
#include <Windows.h>

class Vec2;

class Rect
{
private:
	Vec2* position;
	Vec2* dimension;
	CHAR_INFO* buffer;

public:
	Rect(int x,int y,int width,int height);
	Rect(const Rect& other);
	Vec2 GetPos();
	void SetPos(int x,int y);
	void SetPos(Vec2 pos);
	Vec2 GetDimension();
	~Rect();
};
