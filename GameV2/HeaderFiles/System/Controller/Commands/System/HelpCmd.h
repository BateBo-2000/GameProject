#pragma once
#ifndef HELP_COMMAND_H
#define HELP_COMMAND_H

#include <vector>
#include <string>

#include "../ICommand.h"

class IUserInterface;

class HelpCmd : public ICommand {
public:
    HelpCmd(IUserInterface& ui);
    virtual bool isThisMe(const std::vector<std::string>& args) const override;
    virtual void execute(const std::vector<std::string>& args) const override;
    virtual ICommand* clone() const override;
private:
    static constexpr const char* myName = "help";
    IUserInterface& ui;
};

#endif // !HELP_COMMAND_H
