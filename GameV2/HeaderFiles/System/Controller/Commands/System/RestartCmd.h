#pragma once
#ifndef RESTART_COMMAND_H
#define RESTART_COMMAND_H

#include <vector>
#include <string>

#include "../ICommand.h"

class IUserInterface;

class RestartCmd : public ICommand {
public:
	RestartCmd(IUserInterface& ui);
	virtual bool isThisMe(const std::vector<std::string>& args) const override;
	virtual void execute(const std::vector<std::string>& args) const override;
	virtual ICommand* clone() const override;
private:
	static constexpr const char* myName = "Restart";

	IUserInterface& ui;
};



#endif // !RESTART_COMMAND_H