#include <iostream>
#include <string>
#include <sstream>
#include "Logger.h"

int main()
{
	Logger::getInstance().log("Hello World!");
	for (int i = 0; i < 10; i++)
	{
		std::ostringstream oss;
		oss << "Hello World! " << i;
		Logger::getInstance().log(oss.str());
	}
	system("pause");

	return 0;
}