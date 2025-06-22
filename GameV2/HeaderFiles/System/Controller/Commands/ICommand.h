#pragma once
#ifndef COMMAND_INTERFACE
#define COMMAND_INTERFACE

#include <string>
#include <vector>

class ICommand {
public:
	virtual ~ICommand() = default;
	virtual bool isThisMe(const std::vector<std::string>& args) const = 0;
	virtual void execute(const std::vector<std::string>& args) const = 0;
	virtual ICommand* clone() const =0;
};

#endif // COMMAND_INTERFACE
