#include "Logger.h"
#include <iostream>
#include <windows.h>
#include <ctime>
#include <sstream>

void Logger::log(LogLevel type, std::string message)
{

	time_t t = time(0);   // get time now
	struct tm now;
	localtime_s(&now, &t); //convert timezone

	if (!logfile.is_open())
	{
		std::ostringstream oss;
		oss << "Log " << now.tm_mday << "-" << (now.tm_mon + 1) << "-" << (now.tm_year + 1900) << ".txt";
		logfile.open(oss.str(), std::ios_base::app);
		if (!logfile.is_open())
		{
			throw(std::runtime_error("LOGGER: kan logbestand niet openen!"));
		}
	}

	SYSTEMTIME time;
	GetSystemTime(&time);
	WORD millis = time.wMilliseconds;

	char timebuf[9];
	strftime(timebuf, 9, "%H:%M:%S", &now);
	logfile << timebuf << "." << millis << " ";
	std::cout << timebuf << "." << millis << " ";


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
