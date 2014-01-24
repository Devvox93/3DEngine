/*
	3D Engine
	Logger.h
	Purpose: Used to log info, warnings and errors to the command line and the log-file.

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

	/*
		Returns the singleton logger.
	*/
	static Logger& getInstance()
	{
		static Logger instance;
		return instance;
	}

	/*
		Method that logs a type and message.
	*/
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