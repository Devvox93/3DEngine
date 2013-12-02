#include "logger.h"
#include <iostream>

void Logger::log(std::string message)
{
	if (!logfile.is_open())
	{
		logfile.open(__DATE__".txt", std::ios_base::app);
		if (!logfile.is_open())
		{
			throw(std::runtime_error("LOGGER: kan logbestand niet openen!"));
		}
	}
	logfile << __TIME__ << ":";
	logfile << message.c_str() << std::endl;

	std::cout << __TIME__ << ":";
	std::cout << message.c_str() << std::endl;
}