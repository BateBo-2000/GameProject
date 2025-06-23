#pragma once
#ifndef SAVE_COMMAND_H
#define SAVE_COMMAND_H

#include <vector>
#include <string>

#include "../ICommand.h"

class IUserInterface;

class SaveCmd : public ICommand {
public:
	SaveCmd(IUserInterface& ui);
	virtual bool isThisMe(const std::vector<std::string>& args) const override;
	virtual void execute(const std::vector<std::string>& args) const override;
	virtual ICommand* clone() const override;
private:
	static constexpr const char* myName = "Save";
	IUserInterface& ui;
};



#endif // !SAVE_COMMAND_H