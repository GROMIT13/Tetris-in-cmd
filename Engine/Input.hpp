#pragma once

#include <vector>

struct KeyState
{
	bool present;
	bool past;
};


//TO DO: Add more input states
//		 Move Input to singielton class
class Input
{
private:
	KeyState* keyState;

public:
	Input();
	~Input();
	void CheckInput();
	KeyState GetKey(char keyCode);
};