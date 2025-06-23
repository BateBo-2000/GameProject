#pragma once
#ifndef LOAD_COMMAND_H
#define LOAD_COMMAND_H

#include <vector>
#include <string>

#include "../ICommand.h"

class IUserInterface;

class LoadCmd : public ICommand {
public:
	LoadCmd(IUserInterface& ui);
	virtual bool isThisMe(const std::vector<std::string>& args) const override;
	virtual void execute(const std::vector<std::string>& args) const override;
	virtual ICommand* clone() const override;
private:
	static constexpr const char* myName = "Load";
	IUserInterface& ui;
};



#endif // !LOAD_COMMAND_H