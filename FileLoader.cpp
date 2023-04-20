#include "FileLoader.hpp"

void LoadScreenProperties(const std::string& filepath, ScreenProperties& outScreenProperties)
{
	//TO DO: FIX - ERROR MESSAGE DOES NOT SHOW UP
	Log log("ConsoleLog.txt");
	std::ifstream file(filepath);
	std::string line;

	if (!file)
	{
		log.Error("File " + filepath + " does not exist");
		return;
	}

	while (!file.eof())
	{
		file >> line;
		if (line == "Title") {
			file >> line;
			outScreenProperties.title = line;
		}

		if (line == "ScreenWidth") {
			file >> line;
			outScreenProperties.width = std::stoi(line);
		}

		if (line == "ScreenHeight") {
			file >> line;
			outScreenProperties.height = std::stoi(line);
		}

		if (line == "TextWidth") {
			file >> line;
			outScreenProperties.textWidth = std::stoi(line);
		}

		if (line == "TextHeight") {
			file >> line;
			outScreenProperties.textHeight = std::stoi(line);
		}
	}
}