#pragma once
#ifndef CONSOLE_USER_INTERFACE
#define CONSOLE_USER_INTERFACE

#include "IUserInterface.h"

#include <iostream>

class ConsoleUI : public IUserInterface {
public:
	virtual ConsoleUI* clone() const override;

	virtual void inform(const string& msg)const override;
	virtual void warn(const string& msg)const override;
	virtual void printInvalidArg(const string& msg)const override;
	virtual bool confirm(const string& q)const override;
	virtual int askForNumber(const string& q)const override;
	virtual string askQuestion(const string& q)const override;
};


#endif // !CONSOLE_USER_INTERFACE
