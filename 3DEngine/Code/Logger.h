/*
3D Engine
Xresource.h
Purpose: Loads X resources.

@author Patrick, Nick, Robert, Jordi
@version 1.0
*/

#ifndef _LOGGER_H_
#define _LOGGER_H_
#include <fstream>

enum LogLevel {INFO, WARNING, CRITICAL};

class Logger
{
public:
	static Logger& getInstance()
	{
		static Logger instance;
		return instance;
	}
	void log(LogLevel type, std::string message);
private:
	Logger()
	{
		//Constructor, don't implement
	}
	
	Logger(Logger const&); //Don't implement
	void operator=(Logger const&); //Don't implement

	std::ofstream logfile;
};
#endif