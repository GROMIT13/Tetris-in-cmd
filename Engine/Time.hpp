#pragma once

#include <chrono>
#include <Windows.h>

class Clock
{
private:
	std::chrono::steady_clock::time_point currentTime = std::chrono::high_resolution_clock::now();

	unsigned long long tickRate; // TickRate is converted to micro sedconds
	std::chrono::steady_clock::time_point coutBegin;

	unsigned int frameCounter;
	unsigned int currentFPS;
	std::chrono::steady_clock::time_point lastTimeMeasuredFPS = std::chrono::high_resolution_clock::now();

	std::chrono::steady_clock::time_point lastTimeHasPassed = std::chrono::high_resolution_clock::now();
public:
	static void Wait(unsigned long long ms);
	Clock(unsigned long long tickRateMs);
	~Clock();
	unsigned long long GetPassedTime();
	unsigned long long GetPassedTicks();
	unsigned int GetFPS(unsigned int UpdateRateMs);
	bool HasPassed(unsigned long long timeMs);
};