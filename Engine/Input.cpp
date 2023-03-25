#include "Input.hpp"
#include <Windows.h>

Input Input::instance;

void Input::SetKeysImpl(std::vector<char> keyList)
{
	this->keyList = keyList;
	keyState.clear();
	keyState.reserve(this->keyList.size());
	for (unsigned int i = 0; i < this->keyList.size(); i++)
		keyState.push_back({ false,false });
}

void Input::CheckInputImpl()
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

KeyState Input::GetKeyImpl(char keyCode)
{

	for (unsigned int i = 0; i < keyList.size(); i++)
	{
		if (keyCode == keyList[i])
		{
			return keyState[i];
		}
	}

	__debugbreak(); //KeyCode not found, delcalre keyCode using "Input::SetKeys()"
	KeyState exeption = { false,false };
	return exeption;

}

Input& Input::Get()
{
	return instance;
}

KeyState Input::GetKey(char keyCode)
{
	return Get().GetKeyImpl(keyCode);
}

void Input::CheckInput()
{
	Get().CheckInputImpl();
}

void Input::SetKeys(std::vector<char> keyList)
{
	Get().SetKeysImpl(keyList);
}
