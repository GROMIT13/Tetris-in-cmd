#include <iostream>
#include "Engine/DataStructures/vec.hpp"
#include "Log.hpp"

int main()
{
	Log log("log.txt");
	log.Info("test Info");
	log.Warn("test Warn");
	log.Error("test Error");
	return 0;
}