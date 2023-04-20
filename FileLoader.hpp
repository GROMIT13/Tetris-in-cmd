#pragma once
#include <string>
#include <fstream>
#include "Log.hpp"

struct ScreenProperties
{
	std::string title;
	short width;
	short height;
	short textWidth;
	short textHeight;
};

void LoadScreenProperties(const std::string& filepath, ScreenProperties& outScreenProperties);