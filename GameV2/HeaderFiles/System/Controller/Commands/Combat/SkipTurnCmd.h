#pragma once
#ifndef SKIP_TURN_COMMAND_H
#define SKIP_TURN_COMMAND_H

#include <vector>
#include <string>

#include "../ICommand.h"

class IUserInterface;

class SkipTurnCmd : public ICommand {
public:
    SkipTurnCmd(IUserInterface& ui);
    virtual bool isThisMe(const std::vector<std::string>& args) const override;
    virtual void execute(const std::vector<std::string>& args) const override;
    virtual ICommand* clone() const override;
private:
    static constexpr const char* myName = "skip";
    IUserInterface& ui;
};

#endif // !SKIP_TURN_COMMAND_H
