#pragma once

#include <chrono>

class Clock
{
private:
	unsigned long long tickRate; // TickRate is converted to micro sedconds
	std::chrono::steady_clock::time_point coutBegin;
	std::chrono::steady_clock::time_point countEnd;
public:
	static void Wait(unsigned long long ms);
	Clock(unsigned long long tickRateMs);
	~Clock();
	unsigned long long GetPassedTime();
	unsigned long long GetPassedTicks();
	unsigned int GetFPS(unsigned int UpdateRateMs);
};