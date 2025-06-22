#pragma once
#ifndef ILOGGER
#define ILOGGER

#include <string>
using std::string;

class ILogger {
public:
	virtual ~ILogger() = default;
	virtual ILogger* clone() const = 0;

	virtual void log(const string& msg) = 0;
	virtual void warn(const string& msg) = 0;
	virtual void error(const string& msg) = 0;
};


#endif // !ILOGGER