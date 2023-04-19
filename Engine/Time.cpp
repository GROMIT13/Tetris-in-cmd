#include "Time.hpp"

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
	:tickRate(tickRateMs * 1000), frameCounter(0), currentFPS(0)
{
	coutBegin = std::chrono::high_resolution_clock::now();
	currentTime = std::chrono::high_resolution_clock::now();
	lastTimeHasPassed = std::chrono::high_resolution_clock::now();
}

Clock::~Clock()
{
}

unsigned long long Clock::GetPassedTime()
{
	currentTime = std::chrono::high_resolution_clock::now();
	return (unsigned long long)(std::chrono::duration_cast<std::chrono::microseconds>(currentTime - coutBegin).count());
}

unsigned long long Clock::GetPassedTicks()
{
	currentTime = std::chrono::high_resolution_clock::now();
	return (unsigned long long)(std::chrono::duration_cast<std::chrono::microseconds>(currentTime - coutBegin).count()) / tickRate;
}


unsigned int Clock::GetFPS(unsigned int UpdateRateMs)
{
	currentTime = std::chrono::high_resolution_clock::now();
	frameCounter++;
	if (std::chrono::duration_cast<std::chrono::microseconds>(currentTime - lastTimeMeasuredFPS).count() >= 1000000.0f * UpdateRateMs/1000.0f)
	{
		lastTimeMeasuredFPS = std::chrono::high_resolution_clock::now();
		currentFPS = frameCounter * (unsigned int)1000.0f/UpdateRateMs;
		frameCounter = 0;
	}

	return currentFPS;
}

//Retuns tickRate in miliseconds
unsigned long long Clock::GetTickRate()
{
	return tickRate / 1000;
}

//Uses tickRate as time required to return true
bool Clock::HasPassed()
{
	currentTime = std::chrono::high_resolution_clock::now();
	if ((unsigned long long)(std::chrono::duration_cast<std::chrono::microseconds>(currentTime - lastTimeHasPassed).count()) > tickRate)
	{
		lastTimeHasPassed = std::chrono::high_resolution_clock::now();
		return true;
	}
	return false;
}

bool Clock::HasPassed(unsigned long long timeMs)
{
	currentTime = std::chrono::high_resolution_clock::now();
	if ((unsigned long long)(std::chrono::duration_cast<std::chrono::microseconds>(currentTime - lastTimeHasPassed).count()) > timeMs * 1000)
	{
		lastTimeHasPassed = std::chrono::high_resolution_clock::now();
		return true;
	}
	return false;
}

void Clock::ResetHasPassed()
{
	lastTimeHasPassed = std::chrono::high_resolution_clock::now();
}
