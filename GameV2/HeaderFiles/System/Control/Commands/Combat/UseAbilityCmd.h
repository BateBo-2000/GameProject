#pragma once
#ifndef USE_ABILITY_CMD_H
#define USE_ABILITY_CMD_H

#include "../ICommand.h"
#include <vector>
#include <string>

class IGameEngine;
class IUserInterface;

class UseAbilityCmd : public ICommand {
public:
    UseAbilityCmd(IGameEngine& engine, IUserInterface& ui);
    ~UseAbilityCmd() override = default;

    ICommand* clone() const override;

    bool isThisMe(const std::vector<std::string>& args) const override;
    bool execute(const std::vector<std::string>& args) const override;

    const std::string& getName() const override;
    const std::string& getDescription() const override;

private:
    static const std::string NAME;
    static const std::string DESCRIPTION;

    IGameEngine& engine;
    IUserInterface& ui;
};

#endif // USE_ABILITY_CMD_H
