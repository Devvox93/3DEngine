#include <iostream>
#include <string>
#include <sstream>
#include "Logger.h"

int main()
{
	Logger::getInstance().log(INFO, "Hello World!");
	for (int i = 0; i < 10; i++)
	{
		std::ostringstream oss;
		oss << "Problem: " << i << "!";
		Logger::getInstance().log(WARNING, oss.str());
	}
	Logger::getInstance().log(CRITICAL, "Application end!");
	system("pause");

	return 0;
}