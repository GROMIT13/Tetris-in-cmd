#include "Log.hpp"

Log::Log(const std::string filename)
	:filename(filename),logLevel(Level::Info)
{
	logFile.open(filename);
}

Log::~Log()
{
	logFile.close();
}

void Log::SetLogLevel(Level log_Level)
{
	logLevel = log_Level;
}

void Log::Error(const std::string& message)
{
	if (logLevel >= Level::Error)
		logFile << "[ERROR]:" << message << std::endl;
}

void Log::Warn(const std::string& message)
{
	if (logLevel >= Level::Warn)
		logFile << "[WARN]: " << message << std::endl;
}

void Log::Info(const std::string& message)
{
	if (logLevel >= Level::Info)
		logFile << "[INFO]: " << message << std::endl;
}
