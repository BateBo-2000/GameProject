#pragma once
#ifndef SKIP_TURN_CMD_H
#define SKIP_TURN_CMD_H

#include "../ICommand.h"
#include <vector>
#include <string>

class IGameEngine;
class IUserInterface;

class SkipTurnCmd : public ICommand {
public:
    SkipTurnCmd(IGameEngine& engine);
    ~SkipTurnCmd() override = default;

    ICommand* clone() const override;

    bool isThisMe(const std::vector<std::string>& args) const override;
    bool execute(const std::vector<std::string>& args, IUserInterface& ui) const override;

    const std::string& getName() const override;
    const std::string& getDescription() const override;

private:
    static const std::string NAME;
    static const std::string DESCRIPTION;
        
    IGameEngine& engine;
};

#endif // SKIP_TURN_CMD_H