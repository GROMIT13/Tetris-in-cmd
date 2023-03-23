#include "Input.hpp"
#include <Windows.h>

Input::Input()
{
	keyState = new KeyState[256];
	memset(keyState, 0, sizeof(KeyState) * 256);
}

Input::~Input()
{
	delete[] keyState;
}

void Input::CheckInput()
{
	for (int i = 0; i < 256; i++)
	{
		if (keyState[i].present)
			keyState[i].past = true;
		else
			keyState[i].past = false;


		if (GetAsyncKeyState(i))
			keyState[i].present = true;
		else
			keyState[i].present = false;
	}
}

KeyState Input::GetKey(char keyCode)
{
	return keyState[keyCode];
}
