#include "logger.h"
#include <iostream>
#include <windows.h>

void Logger::log(LogLevel type, std::string message)
{
	if (!logfile.is_open())
	{
		logfile.open(__DATE__".txt", std::ios_base::app);
		if (!logfile.is_open())
		{
			throw(std::runtime_error("LOGGER: kan logbestand niet openen!"));
		}
	}

	SYSTEMTIME time;
	GetSystemTime(&time);
	WORD millis = time.wMilliseconds;

	logfile << __TIME__ << "." << millis << " ";
	std::cout << __TIME__ << "." << millis << " ";


	switch (type)
	{
	case INFO:
		logfile << "<INFO>: ";
		std::cout << "<INFO>: ";
		break;
	case WARNING:
		logfile << "<WARNING>: ";
		std::cout << "<WARNING>: ";
		break;
	case CRITICAL:
		logfile << "<CRITICAL>: ";
		std::cout << "<CRITICAL>: ";
		break;
	default:
		logfile << "<???>: ";
		std::cout << "<???>: ";
		break;
	}
	logfile << message.c_str() << std::endl;
	std::cout << message.c_str() << std::endl;
}
