#pragma once
#ifndef EXIT_COMMAND_H
#define EXIT_COMMAND_H

#include <vector>
#include <string>

#include "../ICommand.h"

class IUserInterface;

class ExitCmd : public ICommand {
public:
	ExitCmd(IUserInterface& ui);
	virtual bool isThisMe(const std::vector<std::string>& args) const override;
	virtual void execute(const std::vector<std::string>& args) const override;
	virtual ICommand* clone() const override;
private:
	static constexpr const char* myName = "Exit";
	IUserInterface& ui;
};



#endif // !EXIT_COMMAND_H
