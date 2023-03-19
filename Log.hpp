#pragma once
#include <string>
#include <fstream>

class Log
{
public:
	enum class Level
	{
		Error = 0, Warn, Info
	};

private:
	std::string filename;
	Level logLevel;
	std::ofstream logFile;

public:
	Log(const std::string filename);
	~Log();
	void SetLogLevel(Level logLevel);
	void Error(const std::string& message);
	void Warn(const std::string& message);
	void Info(const std::string& message);
	void ClearFile();
};
