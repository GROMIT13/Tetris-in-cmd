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
	std::vector<char> keyList;

public:
	Input(std::vector<char> keyList);
	~Input();
	void CheckInput();
	KeyState GetKey(char keyCode);
};