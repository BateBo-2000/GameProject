#pragma once
#ifndef I_INVOKER_H
#define I_INVOKER_H

#include <string>

class UserInterface;
class ICommand;


class IInvoker {
public:
	virtual ~IInvoker() = default;
	virtual void registerCommand(ICommand* c) = 0;
	virtual void executeCommandLine(std::string line) = 0;
};


#endif // !I_INVOKER_H
