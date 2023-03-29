#include "Time.hpp"

Clock::Clock(unsigned int tickRateMs)
	:tickRate(tickRateMs * 100)
{
	coutBegin = std::chrono::high_resolution_clock::now();
	countEnd = std::chrono::high_resolution_clock::now();
}

Clock::~Clock()
{
}

unsigned int Clock::GetPassedTime()
{
	countEnd = std::chrono::high_resolution_clock::now();
	return (unsigned int)(std::chrono::duration_cast<std::chrono::microseconds>(countEnd - coutBegin).count());
}

unsigned int Clock::GetPassedTicks()
{
	countEnd = std::chrono::high_resolution_clock::now();
	return (unsigned int)(std::chrono::duration_cast<std::chrono::microseconds>(countEnd - coutBegin).count()) / tickRate;
}
