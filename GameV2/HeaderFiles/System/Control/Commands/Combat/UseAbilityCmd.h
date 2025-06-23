#pragma once
#ifndef USE_ABILITY_COMMAND_H
#define USE_ABILITY_COMMAND_H

#include <vector>
#include <string>

#include "../ICommand.h"

class IUserInterface;

class UseAbilityCmd : public ICommand {
public:
    UseAbilityCmd(IUserInterface& ui);
    virtual bool isThisMe(const std::vector<std::string>& args) const override;
    virtual void execute(const std::vector<std::string>& args) const override;
    virtual ICommand* clone() const override;
private:
    static constexpr const char* myName = "use ability";
    IUserInterface& ui;
};

#endif // !USE_ABILITY_COMMAND_H
