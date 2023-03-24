#include "Input.hpp"
#include <Windows.h>
#include "..\Log.hpp"

Input::Input(std::vector<char> keyList)
	:keyList(keyList)
{
	keyState = new KeyState[this->keyList.size()];
	memset(keyState, 0, sizeof(KeyState) * this->keyList.size());

}

Input::~Input()
{
	delete[] keyState;
}

void Input::CheckInput()
{
	for (unsigned int i = 0; i < keyList.size(); i++)
	{
		if (keyState[i].present)
			keyState[i].past = true;
		else
			keyState[i].past = false;


		if (GetAsyncKeyState(keyList[i]))
			keyState[i].present = true;
		else
			keyState[i].present = false;
	}
}

KeyState Input::GetKey(char keyCode)
{
	Log log("keyLog.txt");

	for (unsigned int i = 0; i < keyList.size(); i++)
	{
		if (keyCode == keyList[i])
		{
			log.Info("Foud key");
			return keyState[i];
		}
	}
	log.Info("failed");
	KeyState exeption = { false,false };
	return exeption;
	
}
