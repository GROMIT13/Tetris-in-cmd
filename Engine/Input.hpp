#pragma once

#include <vector>

struct KeyState
{
	bool present;
	bool past;
};


//TO DO: Add more input states
class Input
{
private:
	static Input instance;
	std::vector<KeyState> keyState;
	std::vector<char> keyList;

	Input() {}
	void SetKeysImpl(std::vector<char> keyList);
	void CheckInputImpl();
	KeyState GetKeyImpl(char keyCode);

public:
	Input(const Input&) = delete;
	static Input& Get();
	static KeyState GetKey(char keyCode);
	static void CheckInput();
	static void SetKeys(std::vector<char> keyList);
};