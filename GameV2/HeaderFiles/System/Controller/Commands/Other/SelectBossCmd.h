#pragma once
#ifndef SELECT_BOSS_COMMAND_H
#define SELECT_BOSS_COMMAND_H

#include <vector>
#include <string>

#include "../ICommand.h"

class IUserInterface;

class SelectBossCmd : public ICommand {
public:
    SelectBossCmd(IUserInterface& ui);
    virtual bool isThisMe(const std::vector<std::string>& args) const override;
    virtual void execute(const std::vector<std::string>& args) const override;
    virtual ICommand* clone() const override;
private:
    static constexpr const char* myName = "select boss";
    IUserInterface& ui;
};

#endif // !SELECT_BOSS_COMMAND_H
