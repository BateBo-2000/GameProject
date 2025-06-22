#pragma once
#ifndef START_COMMAND_H
#define START_COMMAND_H

#include <vector>
#include <string>

#include "../ICommand.h"

class IUserInterface;

class StartCmd : public ICommand {
public:
    StartCmd(IUserInterface& ui);
    virtual bool isThisMe(const std::vector<std::string>& args) const override;
    virtual void execute(const std::vector<std::string>& args) const override;
    virtual ICommand* clone() const override;
private:
    static constexpr const char* myName = "start";
    IUserInterface& ui;
};

#endif // !START_COMMAND_H
