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
		// Constructor
	}
	
	Logger(Logger const&);              // Don't Implement
	void operator=(Logger const&); // Don't implement

	std::ofstream logfile;
};