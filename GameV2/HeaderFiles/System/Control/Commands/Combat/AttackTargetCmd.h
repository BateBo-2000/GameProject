#pragma once
#ifndef ATTACK_TARGET_CMD_H
#define ATTACK_TARGET_CMD_H

#include "../ICommand.h"
#include <vector>
#include <string>

class IGameEngine;
class IUserInterface;

class AttackTargetCmd : public ICommand {
public:
    AttackTargetCmd(IGameEngine& engine, IUserInterface& ui);
    ~AttackTargetCmd() override = default;

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

#endif // ATTACK_TARGET_CMD_H