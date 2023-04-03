#pragma once

#include <vector>
#include <Windows.h>

enum class State
{
	Null = 0, Enter, Stay, Exit
};

struct KeyState
{
	bool present;
	bool past;
};

class Input
{
private:
	std::vector<KeyState> keyState;
	std::vector<char> keyList;

	Input() {}
	void SetKeysImpl(std::vector<char> keyList);
	void CheckInputImpl();
	KeyState GetKeyImpl(char keyCode);
	State GetStateImpl(char keyCode);

public:
	Input(const Input&) = delete;
	void operator=(Input const&) = delete;
	static Input& Get();
	static KeyState GetKey(char keyCode);
	static State GetState(char keyCode);
	static void CheckInput();
	static void SetKeys(std::vector<char> keyList);
};