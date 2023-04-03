#pragma once

#include <chrono>
#include <Windows.h>

class Clock
{
private:
	unsigned long long tickRate; // TickRate is converted to micro sedconds
	std::chrono::steady_clock::time_point coutBegin;
	std::chrono::steady_clock::time_point countEnd;

	unsigned int frameCounter;
	unsigned int currentFPS;
	std::chrono::steady_clock::time_point lastTime = std::chrono::high_resolution_clock::now();
	std::chrono::steady_clock::time_point currentTime = std::chrono::high_resolution_clock::now();
public:
	static void Wait(unsigned long long ms);
	Clock(unsigned long long tickRateMs);
	~Clock();
	unsigned long long GetPassedTime();
	unsigned long long GetPassedTicks();
	unsigned int GetFPS(unsigned int UpdateRateMs);
};