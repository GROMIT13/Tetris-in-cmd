#include "Time.hpp"
#include <Windows.h>

void Clock::Wait(unsigned long long ms)
{
	static std::chrono::steady_clock::time_point waitBegin;
	static std::chrono::steady_clock::time_point waitEnd;

	waitBegin = std::chrono::high_resolution_clock::now();
	
	do {
		waitEnd = std::chrono::high_resolution_clock::now();
	} while ((unsigned long long)(std::chrono::duration_cast<std::chrono::microseconds>(waitEnd - waitBegin).count()) < (ms * 1000));
}

Clock::Clock(unsigned long long tickRateMs)
	:tickRate(tickRateMs * 1000)
{
	coutBegin = std::chrono::high_resolution_clock::now();
	countEnd = std::chrono::high_resolution_clock::now();
}

Clock::~Clock()
{
}

unsigned long long Clock::GetPassedTime()
{
	countEnd = std::chrono::high_resolution_clock::now();
	return (unsigned long long)(std::chrono::duration_cast<std::chrono::microseconds>(countEnd - coutBegin).count());
}

unsigned long long Clock::GetPassedTicks()
{
	countEnd = std::chrono::high_resolution_clock::now();
	return (unsigned long long)(std::chrono::duration_cast<std::chrono::microseconds>(countEnd - coutBegin).count()) / tickRate;
}

//TO DO: implement update rate / remove static
unsigned int Clock::GetFPS(unsigned int UpdateRateMs)
{
	static unsigned int frameCounter = 0;
	static unsigned int currentFPS = 0;
	static std::chrono::steady_clock::time_point lastTime = std::chrono::high_resolution_clock::now();
	static std::chrono::steady_clock::time_point currentTime = std::chrono::high_resolution_clock::now();

	currentTime = std::chrono::high_resolution_clock::now();
	frameCounter++;
	if (std::chrono::duration_cast<std::chrono::microseconds>(currentTime - lastTime).count() >= 1000000)
	{
		lastTime = std::chrono::high_resolution_clock::now();
		currentFPS = frameCounter;
		frameCounter = 0;
	}

	return currentFPS;
}

//unsigned long long Clock::GetPassed(unsigned long long tickRateMs)
//{
//	static unsigned long long count = 0;
//	static std::chrono::steady_clock::time_point lastTime = std::chrono::high_resolution_clock::now();
//	static std::chrono::steady_clock::time_point currentTime = std::chrono::high_resolution_clock::now();
//
//	currentTime = std::chrono::high_resolution_clock::now();
//	if ((unsigned long long)(std::chrono::duration_cast<std::chrono::microseconds>(currentTime - lastTime).count()) > tickRateMs * 1000)
//	{
//		count++;
//		lastTime = std::chrono::high_resolution_clock::now();
//	}
//	
//	return count;
//}
