#pragma once
#ifndef TARGET_COMMAND_H
#define TARGET_COMMAND_H

#include <vector>
#include <string>

#include "../ICommand.h"

class IUserInterface;

class TargetCmd : public ICommand {
public:
    TargetCmd(IUserInterface& ui);
    virtual bool isThisMe(const std::vector<std::string>& args) const override;
    virtual void execute(const std::vector<std::string>& args) const override;
    virtual ICommand* clone() const override;
private:
    static constexpr const char* myName = "target";
    IUserInterface& ui;
};

#endif // !TARGET_COMMAND_H
