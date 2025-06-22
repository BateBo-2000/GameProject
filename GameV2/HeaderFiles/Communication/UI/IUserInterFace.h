#pragma once

#ifndef I_USER_INTERFACE
#define I_USER_INTERFACE

#include <string>
using std::string;

class IUserInterface {
public:
	virtual ~IUserInterface() = default;
	virtual IUserInterface* clone() const = 0;

	virtual void inform(const std::string& msg) const = 0;
	virtual void warn(const std::string& msg) const = 0;
	virtual void printInvalidArg(const std::string& msg) const = 0;

	virtual bool confirm(const std::string& q) const = 0;
	virtual int askForNumber(const std::string& q) const = 0;
	virtual std::string askQuestion(const std::string& q) const = 0;
};

#endif // !I_USER_INTERFACE