#include <iostream>
#include "Engine/DataStructures/vec.hpp"
#include "Log.hpp"

int main()
{
	Log log("log.txt");
	Log log2("log.txt");
	log.ClearFile();
	log.Info("1");
	log2.Info("2");
	log.Warn("3");
	log.Warn("4");
	log.Error("5");
	log2.Error("6");
	
	
	
	return 0;
}
