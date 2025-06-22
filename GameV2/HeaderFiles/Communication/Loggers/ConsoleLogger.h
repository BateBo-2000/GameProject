#ifndef CONSOLE_LOGGER
#define CONSOLE_LOGGER

#include "ILogger.h"

#include <iostream>

class ConsoleLogger : public ILogger {
public:
	virtual ConsoleLogger* clone() const;

	virtual void log(const string& msg);
	virtual void warn(const string& msg);
	virtual void error(const string& msg);
};

#endif // !LOGGER
