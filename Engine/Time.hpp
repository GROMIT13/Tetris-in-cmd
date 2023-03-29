#pragma once

#include <chrono>

class Clock
{
private:
	unsigned int tickRate; // TickRate is converted to micro sedconds
	std::chrono::steady_clock::time_point coutBegin;
	std::chrono::steady_clock::time_point countEnd;
public:
	Clock(unsigned int tickRateMs);
	~Clock();
	unsigned int GetPassedTime();
	unsigned int GetPassedTicks();
};