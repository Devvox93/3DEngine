#include <fstream>
//#include <iostream>

enum LogLevel {INFO, WARNING, SEVERE};

class Logger
{
public:
	static Logger& getInstance()
	{
		static Logger    instance; // Guaranteed to be destroyed.
		// Instantiated on first use.
		return instance;
	}

	void log(LogLevel type, std::string message);

private:
	Logger()
	{
		// Constructor
	}
	// Dont forget to declare these two. You want to make sure they
	// are unaccessable otherwise you may accidently get copies of
	// your singleton appearing.
	Logger(Logger const&);              // Don't Implement
	void operator=(Logger const&); // Don't implement

	std::ofstream logfile;
};