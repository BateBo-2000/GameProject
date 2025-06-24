#pragma once
#ifndef START_DUEL_CMD_H
#define START_DUEL_CMD_H

#include "../ICommand.h"
#include <string>
#include <vector>

class IGameEngine;
class IUserInterface;

class StartDuelCmd : public ICommand {
public:
    StartDuelCmd(IGameEngine& engine, IUserInterface& ui);
    ~StartDuelCmd() override = default;

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

#endif // START_DUEL_CMD_H
